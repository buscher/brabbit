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

#ifndef BRABBIT_H
#define BRABBIT_H

#include "bobject.h"

class BRabbit : public BObject
{
public:

enum RabbitState {
    Idle,
    Jump,
    Fall
};

    explicit BRabbit(int aX = 0, int aY = 0);
    ~BRabbit();

    int state();
    void state(int aState);

    int width();
    int height();

    void speed(double aSpeed);
    double speed();

private:
    class BRabbitPrivate * const d;
};


#endif //BRABBIT_H
