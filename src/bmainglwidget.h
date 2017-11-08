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

#ifndef BMAINGLWIDGET_H
#define BMAINGLWIDGET_H

#include <QGLWidget>

class BRender;
class QBasicTimer;
class BWorldManager;

class BMainGLWidget : public QGLWidget
{
public:
    explicit BMainGLWidget(QWidget* aParent = NULL);
    ~BMainGLWidget();

protected:
    virtual void paintEvent ( QPaintEvent * event );
    virtual void timerEvent ( QTimerEvent *event );
    virtual void mouseMoveEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );

private:
    inline void updateView();

    inline QPainter* painter();
    inline BRender* render();
    inline QBasicTimer* timer();
    inline BWorldManager* manager();
    inline int mousePosX();
    inline void mousePosX(int aValue);

    class BMainGLWidgetPrivate* const d;
};

#endif //BMAINGLWIDGET_H
