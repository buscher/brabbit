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

#ifndef BRENDER_H
#define BRENDER_H

class QPainter;
class QGLWidget;
class BWorldManager;

class BRender
{
public:
    explicit BRender(QPainter *aPainter, QGLWidget *aTarget, BWorldManager *aManager);
    ~BRender();

    void update();

    void reset();

    static BRender* getInstance();

private:
    static BRender* instance;

    inline QPainter* painter();
    inline QGLWidget* target();
    inline BWorldManager* manager();
    inline int lastDiff();

    class BRenderPrivate* const d;
};

#endif //BRENDER_H
