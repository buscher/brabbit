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

#include "brender.h"

#include <QGLWidget>
#include <QPainter>

#include "bobject.h"
#include "brabbit.h"
#include "bworldmanager.h"
#include "bimagecache.h"

BRender* BRender::instance = NULL;

class BRenderPrivate
{
public:
    QPainter *myPainter;
    QGLWidget *myWidget;
    BWorldManager* myWorldManager;
    int myLastDiffY;
};

BRender::BRender(QPainter * aPainter, QGLWidget * aTarget, BWorldManager* aManager)
    : d (new BRenderPrivate)
{
    d->myPainter = aPainter;
    d->myWidget = aTarget;
    d->myWorldManager = aManager;
    d->myLastDiffY = 0;
    instance = this;
}

BRender::~ BRender()
{
    delete d;
}

void BRender::update()
{
    painter()->begin( target() );
    painter()->fillRect(0, 0, target()->width(), target()->height(), Qt::black);

    int tDiffY = qMax (manager()->getZeroHeight() - manager()->getRabbit()->y() - target()->height()/4, lastDiff());
    d->myLastDiffY = tDiffY;

    {
        QList<BObject*> *tList = manager()->layers()[ACTION_LAYER];
        for (int j = 0; j < tList->size(); ++j)
        {
            BObject *tObject = tList->at(j);
            QPixmap* tPix = NULL;
            int tOffset = 0;
            if (tObject->type() & BObject::Rabbit)
            {
                tPix = BImageCache::getInstance()->getPixmapByName("rabbit");
                tOffset -= tPix->width()/2;
                if (tObject->y() + tDiffY > target()->height())
                    manager()->gameover();
            }
            if (tObject->type() & BObject::Cloud)
                tPix = BImageCache::getInstance()->getPixmapByName("cloud");
            if (tObject->type() & BObject::Snow)
                tPix = BImageCache::getInstance()->getPixmapByName("snow");
            if (tObject->type() & BObject::CustomImage )
                tPix = BImageCache::getInstance()->getPixmapByName( tObject->image() );

            painter()->drawPixmap( tObject->x() + tOffset,
                                   tObject->y() + tDiffY,
                                   *tPix );
        }
    }
    {
        QList<BObject*> *tList = manager()->layers()[FOREGROUND_LAYER];
        for (int j = 0; j < tList->size(); ++j)
        {
            BObject *tObject = tList->at(j);
            QPixmap* tPix = NULL;
            if (tObject->type() & BObject::Cloud)
                tPix = BImageCache::getInstance()->getPixmapByName("backcloud");
            if (tObject->type() & BObject::Snow)
                tPix = BImageCache::getInstance()->getPixmapByName("snow");
            if (tObject->type() & BObject::CustomImage )
                tPix = BImageCache::getInstance()->getPixmapByName( tObject->image() );
            if (tObject->type() & BObject::CustomText )
                tPix = BImageCache::getInstance()->getCustomText( tObject->image(), tObject->fontflags() );

            painter()->drawPixmap( tObject->x(),
                                   tObject->y(),
                                   *tPix );
        }
    }

    painter()->end();
}

QPainter * BRender::painter()
{
    return d->myPainter;
}

QGLWidget * BRender::target()
{
    return d->myWidget;
}

BWorldManager * BRender::manager()
{
    return d->myWorldManager;
}

int BRender::lastDiff()
{
    return d->myLastDiffY;
}

void BRender::reset()
{
    d->myLastDiffY = 0;
}

BRender * BRender::getInstance()
{
    return instance;
}
