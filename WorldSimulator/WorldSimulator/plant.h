#pragma once
#include <curses.h>
#include "defines.h"
#include "world.h"

class Organism {
protected:
    int strength;
    int initiative;
    int x, y;
    World* world;

public:
    Organism(int strength, int initiative, int x, int y, World* world);

    int getStrength() const;
    int getInitiative() const;
    int getX() const;
    int getY() const;

    void setPosition(int newX, int newY);

    virtual void action();
    virtual void collision(Organism* other);
    virtual void draw() const;

    virtual ~Organism();
};