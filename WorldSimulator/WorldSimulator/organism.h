#pragma once
#include <string>
#include <curses.h>
#include "defines.h"
#include "world.h"
using namespace std;

class World;

class Organism {
protected:
    int strength, initiative, age, x ,y;
    World* world;
public:
    Organism(int strength, int initiative, int age, int x, int y, World* world);

    int getStrength() const;
    int getInitiative() const;
    int getX() const;
    int getY() const;
    int getAge() const;

    virtual void draw() const = 0;
    void setPosition(int newX, int newY);
    virtual string getTypeName() const = 0;
    virtual void action() = 0;
    virtual void collision(Organism* other) = 0;
    virtual Organism* copy_organism(int x, int y) const = 0;
    void increaseStrength();
    void increaseAge();

    virtual ~Organism();
};