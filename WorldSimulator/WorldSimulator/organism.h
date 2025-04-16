#pragma once
#include <curses.h>
#include "defines.h"

class World;

class Organism {
protected:
    int strength, initiative, x ,y;
    World* world;

public:
    Organism(int strength, int initiative, int x, int y, World* world);

    int getStrength() const;
    int getInitiative() const;
    int getX() const;
    int getY() const;

    virtual void draw() const = 0;
    void setPosition(int newX, int newY);

    virtual void action() = 0;
    virtual void collision(Organism* other) = 0;

    virtual ~Organism();
};