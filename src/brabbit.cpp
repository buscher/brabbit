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

#include "brabbit.h"

#include <QPixmap>

#include "bimagecache.h"

class BRabbitPrivate
{
public:
    int myState;
    int myWidth;
    int myHeight;
    double mySpeed;
};

BRabbit::BRabbit(int aX, int aY)
    : BObject(aX,aY,BObject::Rabbit|BObject::NonStatic), d (new BRabbitPrivate)
{
    d->myState = Idle;
    QPixmap* tPix = BImageCache::getInstance()->getPixmapByName("rabbit");
    d->myWidth = tPix->width();
    d->myHeight = tPix->height();
    d->mySpeed = 0;
}

BRabbit::~ BRabbit()
{
    delete d;
}

int BRabbit::state()
{
    return d->myState;
}

int BRabbit::width()
{
    return d->myWidth;
}

void BRabbit::state(int aState)
{
    d->myState = aState;
}

int BRabbit::height()
{
    return d->myHeight;
}

void BRabbit::speed(double aSpeed)
{
    d->mySpeed = aSpeed;
}

double BRabbit::speed()
{
    return d->mySpeed;
}
