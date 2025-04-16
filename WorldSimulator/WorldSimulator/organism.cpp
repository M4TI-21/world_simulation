#include "organism.h"
#include "world.h"

Organism::Organism(int strength, int initiative, int x, int y, World* world) 
    : strength(strength), initiative(initiative), x(x), y(y), world(world) {}

int Organism::getStrength() const {
    return strength;
}

int Organism::getInitiative() const {
    return initiative;
}

int Organism::getX() const {
    return x;
}

int Organism::getY() const {
    return y;
}

void Organism::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

Organism::~Organism() {}