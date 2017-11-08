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

#include "bobject.h"

class BObjectPivate
{
public:
    int myType;
    QString myCustomImage;
    int myX;
    int myY;
    int myFontFlags;
};

BObject::BObject(int aX, int aY, int aType, const QString & aCustomImage, int aFontFlags)
    : d(new BObjectPivate)
{
    d->myType = aType;
    d->myCustomImage = aCustomImage;
    d->myX = aX;
    d->myY = aY;
    d->myFontFlags = aFontFlags;
}

BObject::~ BObject()
{
    delete d;
}

int BObject::type()
{
    return d->myType;
}

QString BObject::image()
{
    return d->myCustomImage;
}

int BObject::x()
{
    return d->myX;
}

int BObject::y()
{
    return d->myY;
}

void BObject::x(int aX)
{
    d->myX = aX;
}

void BObject::y(int aY)
{
    d->myY = aY;
}

int BObject::fontflags()
{
    return d->myFontFlags;
}
