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

#include "bimagecache.h"

#include <QString>
#include <QPixmap>
#include <QDir>
#include <QCoreApplication>
#include <QFont>
#include <QFontMetrics>
#include <QPainter>

#include "bobject.h"
#include "bdebug.h"

BImageCache* BImageCache::instance = NULL;

class BImageCachePrivate
{
public:
    QHash<QString,QPixmap*> myImageHash;
};

BImageCache::BImageCache()
    : d (new BImageCachePrivate)
{
}

BImageCache::~ BImageCache()
{
    foreach (QPixmap* tPix, *hash())
        delete tPix;
    delete d;
    instance = NULL;
}

QPixmap * BImageCache::getPixmapByName(const QString & aName)
{
    QHash<QString, QPixmap*>::const_iterator i = hash()->find(aName);
    if (i != hash()->end() && i.key() == aName)
    {
        return i.value();
    } else {
        return loadImageByName(aName);
    }
}

QHash< QString, QPixmap * > * BImageCache::hash()
{
    return &d->myImageHash;
}

QPixmap * BImageCache::loadImageByName(const QString & aName)
{
    QDir tDir(QCoreApplication::applicationDirPath () + "/img/");
    QStringList tList = tDir.entryList( QStringList(aName+"*"),QDir::Files, QDir::Name);

    for (int i = 0; i < tList.size(); ++i)
    {
        if (tList.at(i).startsWith(aName))
        {
            QPixmap* tPix = new QPixmap(QCoreApplication::applicationDirPath () + "/img/" + tList.at(i) );
            hash()->insert(aName,tPix);
            return tPix;
        }
    }

    QDir tDir2(QCoreApplication::applicationDirPath () + "/../img/");
    QStringList tList2 = tDir2.entryList( QStringList(aName+"*"),QDir::Files, QDir::Name);

    for (int i = 0; i < tList2.size(); ++i)
    {
        if (tList2.at(i).startsWith(aName))
        {
            QPixmap* tPix = new QPixmap(QCoreApplication::applicationDirPath () + "/../img/" + tList2.at(i) );
            hash()->insert(aName,tPix);
            return tPix;
        }
    }

    QPixmap *tPix = new QPixmap(80,80);
    tPix->fill( Qt::red );
    hash()->insert(aName,tPix);
    return tPix;
}

BImageCache * BImageCache::getInstance()
{
    if (BImageCache::instance)
        return BImageCache::instance;
    else
        BImageCache::instance = new BImageCache;
    return BImageCache::instance;
}

QPixmap * BImageCache::getCustomText(const QString & aText, int aFlags)
{
    QHash<QString, QPixmap*>::const_iterator i = hash()->find(aText+QString::number(aFlags));
    if (i != hash()->end() && i.key() == aText+QString::number(aFlags))
    {
        return i.value();
    } else {
        return createTextPixmap(aText,aFlags);
    }
}

QPixmap * BImageCache::createTextPixmap(const QString & aText, int aFlags)
{
    QFont tFont;
    tFont.setFamily("serif");
    if (aFlags & BObject::Small)
        tFont.setPointSize( 24 );
    if (aFlags & BObject::Normal)
        tFont.setPointSize( 44 );
    if (aFlags & BObject::Huge)
        tFont.setPointSize( 72 );

    if (aFlags & BObject::Bold)
        tFont.setBold( true );

    QColor tColor = Qt::white;
    if (aFlags & BObject::Red)
        tColor = Qt::red;
    if (aFlags & BObject::White)
        tColor = Qt::white;
    if (aFlags & BObject::Black)
        tColor = Qt::black;
    if (aFlags & BObject::Green)
        tColor = Qt::green;
    if (aFlags & BObject::Yellow)
        tColor = Qt::yellow;
    if (aFlags & BObject::Blue)
        tColor = Qt::blue;

    QFontMetrics tMetcris(tFont);
    int tWidth = tMetcris.width( aText );
    int tHeight = tMetcris.height();

    QPixmap *tPix = new QPixmap(tWidth,tHeight);
    tPix->fill( QColor(0,0,0,0) );

    QPainter tPainter(tPix);
    tPainter.setPen( tColor );
    tPainter.setBrush( tColor );
    QPainterPath tPath;
    tPath.addText(0,tHeight/2+tHeight/3,tFont,aText);
    tPainter.drawPath( tPath );
    tPainter.end();
    bDebug("Text: "+ aText + " created.");
    hash()->insert(aText+QString::number(aFlags),tPix);
    return tPix;
}
