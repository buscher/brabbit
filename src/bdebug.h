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

#ifndef BDEBUG_H
#define BDEBUG_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <QDebug>
#include <QString>

namespace BDebug
{
    static bool SBDebug = getenv("BDEBUG");

    static inline bool bDebug()
    {
        return SBDebug;
    }
};

#define bDebug(a) \
    { \
        if (BDebug::SBDebug) \
            qDebug() << __FILE__ << ":" \
                << __LINE__ << ":" \
                << __func__ << " " \
                << QString(a); \
    }

#endif //BDEBUG_H
