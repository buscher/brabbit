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

#ifndef BWORLDMANAGER_H
#define BWORLDMANAGER_H

/**
 * The WorldManager, the main Idea is to handle 3 different layers
        - 1. The Background
            background
        - 2. The Current Layer
            main layer for normal action
        - 3. The Vorground
            used for special effects and stuff
        (in this order)

    Only the 2. Layer is effected by gravity and also there are
    static Objects that dont move
*/

#define BACKGROUND_LAYER 0
#define ACTION_LAYER 1
#define FOREGROUND_LAYER 2

#include <QList>

class BObject;
class BRabbit;
class QGLWidget;

class BWorldManager
{
public:
    explicit BWorldManager(QGLWidget *aTarget);
    ~BWorldManager();

    QList<BObject*> **layers();

    void update(int aX);
    void mouseClicked();

    BRabbit *getRabbit();
    int getZeroHeight();

    //shouldnt the worldmanager notice it itself?
    void gameover();

private:
    inline void reset();

    inline void init();
    inline void clear();

    inline void updateScore();
    inline QList<BObject*> *allObjects();
    inline BRabbit *rabbit();
    inline QGLWidget* target();
    inline bool jumpable();
    inline int zeroHeight();
    inline int lastCloudHight();
    inline void lastCloudHight(int aHeight);
    inline void generateCoulds(int aCoulds);
    inline bool collisionWithCould();
    inline void removeObjectFromList( BObject* aObject );

    class BWorldManagerPrivate* const d;
};

#endif //BWORLDMANAGER_H
