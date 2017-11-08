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

#ifndef BOBJECT_H
#define BOBJECT_H

#include <QString>

class BObject
{
public:

enum ObjectType {
    Cloud = 1<<0,
    Rabbit = 1<<1,
    Snow = 1<<2,

    Static = 1<<6,
    NonStatic = 1<<7,

    CustomImage = 1<<12,
    CustomText = 1<<13
};

enum FontFlags {
    Small = 1<<0,
    Normal = 1<<1,
    Huge = 1 <<2,

    Bold = 1<<4,
    Italic = 1<<5,
    Underlined = 1<<6,

    White = 1<<7,
    Black = 1<<8,
    Red = 1<<9,
    Green = 1<<10,
    Yellow = 1<<11,
    Blue = 1<<12
};

    explicit BObject(int aX, int aY, int aType, const QString& aCustomImage = QString(), int aFontFlags = 0);
    ~BObject();

    int type();
    QString image();
    int fontflags();

    int x();
    int y();

    void x(int aX);
    void y(int aY);

private:
    class BObjectPivate* const d;
};

#endif //BOBJECT_H
