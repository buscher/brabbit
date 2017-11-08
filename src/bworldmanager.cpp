/***************************************************************************
 *   Copyright (C) 2008 by Bernd Buschinski   *
 *   b.buschinski@web.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "bworldmanager.h"

#include <QGLWidget>
#include <QTime>

#include "brand.h"
#include "bdebug.h"

#include "bimagecache.h"
#include "bobject.h"
#include "brabbit.h"
#include "brender.h"

static const int sRabbitMaxSpeed = 255;

class BWorldManagerPrivate
{
public:
    QList<BObject*> myList;
    QList<BObject*> *myLayers[3];
    BRabbit* myRabbit;
    QGLWidget *myTarget;
    bool myJumpable;
    QTime myTime;
    int myZeroHeight;
    int myLastCloudHight;
    bool myResetClick;
    qint64 myHighScore;
    qint64 myScore;
    qint64 myScoreStep;
    BObject* myScoreItem;
};

BWorldManager::BWorldManager(QGLWidget *aTarget)
    : d(new BWorldManagerPrivate)
{
    d->myLayers[BACKGROUND_LAYER] = new QList<BObject*>();
    d->myLayers[ACTION_LAYER] = new QList<BObject*>();
    d->myLayers[FOREGROUND_LAYER] = new QList<BObject*>();

    d->myTarget = aTarget;
    d->myZeroHeight = target()->height()- target()->height()/7;
    d->myHighScore = 0;
    d->myScoreItem = NULL;

    init();
}

BWorldManager::~ BWorldManager()
{
    clear();

    delete d->myLayers[BACKGROUND_LAYER];
    delete d->myLayers[ACTION_LAYER];
    delete d->myLayers[FOREGROUND_LAYER];
    delete d;
}

QList< BObject * > * BWorldManager::allObjects()
{
    return &d->myList;
}

QList< BObject * > **BWorldManager::layers()
{
    return d->myLayers;
}

void BWorldManager::update(int aX)
{
    if (d->myResetClick) return;

//     qDebug() << "aX" << aX << "rabbit()->x()" << rabbit()->x();
    int xDiff = abs(rabbit()->x() - aX);
    int const maxXDiff = 29;
    if (xDiff > maxXDiff)
    {
        xDiff = maxXDiff;
    }
    if (rabbit()->x() >= aX)
    {
        xDiff *= -1;
    }
    
    int newX = rabbit()->x() + xDiff;
//     qDebug() << "newX" << newX;
//     if (xDiff == 0 || true) {
        rabbit()->x( qMax(rabbit()->width()/2 , qMin(newX , target()->width() - rabbit()->width()/2)) );
//     }

//     rabbit()->x( qMax(rabbit()->width()/2 , qMin(aX , target()->width() - rabbit()->width()/2)) );
    int tTimeDiff = d->myTime.msecsTo( QTime::currentTime() );
    double tFactor = double(tTimeDiff) / 20;
    double tHeight = zeroHeight();
    rabbit()->y(
        qMin(int(tHeight), int(rabbit()->y() - rabbit()->speed()/25*tFactor))
    );

    if (rabbit()->y() == tHeight)
    {
        d->myJumpable = true;
        rabbit()->speed( 0 );
        rabbit()->state( BRabbit::Idle );
    } else {
        if (collisionWithCould())
        {
            rabbit()->speed( sRabbitMaxSpeed );
            d->myScore += d->myScoreStep;
            d->myScoreStep += 10;
            updateScore();
        } else
            rabbit()->speed( (double)rabbit()->speed() - 10*tFactor );
    }
    d->myTime = QTime::currentTime();
}

BRabbit * BWorldManager::rabbit()
{
    return d->myRabbit;
}

QGLWidget * BWorldManager::target()
{
    return d->myTarget;
}

bool BWorldManager::jumpable()
{
    return d->myJumpable;
}

void BWorldManager::mouseClicked()
{
    if (jumpable())
    {
        d->myJumpable = false;
        rabbit()->state( BRabbit::Jump );
        rabbit()->speed( sRabbitMaxSpeed );
    }
    if (d->myResetClick)
    {
        reset();
    }
}

int BWorldManager::zeroHeight()
{
    return d->myZeroHeight;
}

void BWorldManager::generateCoulds(int aClouds)
{
    int tHeight = BImageCache::getInstance()->getPixmapByName("could")->height();
    for (int i = 0; i < aClouds; ++i)
    {
        int tRand = qMax((int)brand(130),tHeight);
        lastCloudHight( lastCloudHight() - tRand );
        int tX = qMax(
            0,(int)brand(target()->width()) - BImageCache::getInstance()->getPixmapByName("could")->width()
        );
        BObject* tObject = new BObject( tX, lastCloudHight(), BObject::Cloud|BObject::Static );
        allObjects()->append( tObject );
        layers()[ACTION_LAYER]->append( tObject );
    }
}

int BWorldManager::lastCloudHight()
{
    return d->myLastCloudHight;
}

void BWorldManager::lastCloudHight(int aHeight)
{
    d->myLastCloudHight = aHeight;
}

bool BWorldManager::collisionWithCould()
{
    QPixmap* tPix = BImageCache::getInstance()->getPixmapByName("could");
    int tWidth = tPix->width();
    int tHeight = tPix->height();
    int tRabbitX = rabbit()->x() - rabbit()->width()/2;
    QList<BObject*> *tList = layers()[ACTION_LAYER];
    bDebug("size: " + QString::number(tList->size()) );
    for (int i = 0; i < tList->size(); ++i)
    {
        BObject* tObj = tList->at( i );
        if (!(tObj->type() & BObject::Cloud)) continue;
        if (tRabbitX + rabbit()->width() < tObj->x()) continue;
        if (tRabbitX > tObj->x() + tWidth) continue;

        if (rabbit()->y()+rabbit()->height() < tObj->y()) continue;
        if (rabbit()->y()+rabbit()->height() > tObj->y()+tHeight) continue;
        bDebug("HERE JUMP!!!");

        removeObjectFromList( tObj );
        generateCoulds( 1 );

        return true;
    }

    return false;
}

void BWorldManager::removeObjectFromList(BObject * aObject)
{
    QList<BObject*> *tList = allObjects();
    for (int i = 0; i < tList->size(); ++i) {
        if (tList->at(i) == aObject)
        {
            delete tList->takeAt( i );
            break;
        }
    }

    for (int j = 0; j < 3; ++j )
    {
        tList = layers()[j];
        for (int i = 0; i < tList->size(); ++i)
        {
            if (tList->at(i) == aObject)
            {
                /*delete*/ tList->removeAt( i ); //FIXME its already deleted
                break;
            }
        }
    }
}

BRabbit * BWorldManager::getRabbit()
{
    return rabbit();
}

int BWorldManager::getZeroHeight()
{
    return zeroHeight();
}

void BWorldManager::gameover()
{
    BObject* tObj = new BObject( 60, target()->height()/2 - target()->height()/4, BObject::CustomText, "GAMEOVER!", BObject::Bold|BObject::Red|BObject::Huge);
    allObjects()->append( tObj );
    layers()[FOREGROUND_LAYER]->append( tObj );
    d->myResetClick = true;

    if (d->myScore > d->myHighScore)
    {
        BObject* tNewHighScore = new BObject(50,target()->height()/2,BObject::CustomText,"New Highscore: "+QString::number(d->myScore),
                        BObject::Normal|BObject::Green);
        allObjects()->append( tNewHighScore );
        layers()[FOREGROUND_LAYER]->append( tNewHighScore );
        d->myHighScore = d->myScore;
    }
}

void BWorldManager::reset()
{
    clear();
    BRender::getInstance()->reset();
    init();
}

void BWorldManager::init()
{
    d->myScore = 0;
    d->myScoreStep = 10;
    d->myJumpable = true;
    d->myRabbit = new BRabbit(0, zeroHeight());

    d->myLastCloudHight = rabbit()->y();
    d->myResetClick = false;

    d->myTime = QTime::currentTime();

    allObjects()->append( rabbit() );
    layers()[ACTION_LAYER]->append( rabbit() );


    BObject* tObj = new BObject( 0,rabbit()->y()+rabbit()->height(),BObject::Static|BObject::CustomImage,"ground");
    allObjects()->append( tObj );
    layers()[ACTION_LAYER]->append( tObj );

    generateCoulds(15);
    updateScore();
}

void BWorldManager::clear()
{
    while (!allObjects()->isEmpty())
        delete allObjects()->takeFirst();

    while (!d->myLayers[BACKGROUND_LAYER]->isEmpty())
        d->myLayers[BACKGROUND_LAYER]->takeFirst();
    while (!d->myLayers[ACTION_LAYER]->isEmpty())
        d->myLayers[ACTION_LAYER]->takeFirst();
    while (!d->myLayers[FOREGROUND_LAYER]->isEmpty())
        d->myLayers[FOREGROUND_LAYER]->takeFirst();
}

void BWorldManager::updateScore()
{
    if (d->myScoreItem)
    {
        removeObjectFromList(d->myScoreItem);
    }
    d->myScoreItem = new BObject(0,0,BObject::CustomText,"Score: "+QString::number(d->myScore),
                    BObject::Small|BObject::White);
    allObjects()->append( d->myScoreItem );
    layers()[FOREGROUND_LAYER]->append( d->myScoreItem );
}
