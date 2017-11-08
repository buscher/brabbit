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

#include "bmainglwidget.h"

#include <QPainter>
#include <QTimerEvent>
#include <QBasicTimer>
#include <QMouseEvent>

#include "bimagecache.h"
#include "brender.h"
#include "bworldmanager.h"

class BMainGLWidgetPrivate
{
public:
    QPainter *myPainter;
    BRender* myRender;
    QBasicTimer* myTimer;
    BWorldManager *myManager;
    int myMousePosX;
};

BMainGLWidget::BMainGLWidget(QWidget * aParent)
    : QGLWidget(aParent), d(new BMainGLWidgetPrivate)
{
    setMouseTracking( true );

    setFixedWidth( 800 ); //For now...
    setFixedHeight( 700 );

    d->myManager = new BWorldManager(this);
    d->myPainter = new QPainter();
    d->myRender = new BRender( painter(), this, manager() );
    d->myTimer = new QBasicTimer();
    d->myMousePosX = 0;

    timer()->start(25, this);
}

BMainGLWidget::~ BMainGLWidget()
{
    d->myTimer->stop();
    delete d->myPainter;
    delete d->myManager;
    delete d->myRender;
    delete d->myTimer;
    delete d;
    delete BImageCache::getInstance();
}

void BMainGLWidget::paintEvent(QPaintEvent * /*event*/)
{
    render()->update();
}

QPainter * BMainGLWidget::painter()
{
    return d->myPainter;
}

BRender * BMainGLWidget::render()
{
    return d->myRender;
}

QBasicTimer * BMainGLWidget::timer()
{
    return d->myTimer;
}

void BMainGLWidget::updateView()
{
//reports the current mouse X position, relative to the window, to the WorldManager
    manager()->update( mousePosX() );
    repaint();
}

void BMainGLWidget::timerEvent(QTimerEvent * aEvent)
{
    if (aEvent->timerId() == timer()->timerId() )
    {
        updateView();
    } else {
        QGLWidget::timerEvent(aEvent);
    }
}

BWorldManager * BMainGLWidget::manager()
{
    return d->myManager;
}

int BMainGLWidget::mousePosX()
{
    return d->myMousePosX;
}

void BMainGLWidget::mouseMoveEvent(QMouseEvent * aEvent)
{
    if (mousePosX() != aEvent->pos().x())
        mousePosX( aEvent->pos().x() );
}

void BMainGLWidget::mousePosX(int aValue)
{
    d->myMousePosX = aValue;
}

void BMainGLWidget::mousePressEvent(QMouseEvent * aEvent)
{
    if (aEvent->button() == Qt::LeftButton)
        manager()->mouseClicked();
}
