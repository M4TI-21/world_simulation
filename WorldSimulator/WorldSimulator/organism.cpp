#include "organism.h"
#include "world.h"

Organism::Organism(int strength, int initiative, int age, int x, int y, World* world) 
    : strength(strength), initiative(initiative), age(age), x(x), y(y), world(world) {}

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

int Organism::getAge() const {
    return age;
}

void Organism::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
    refresh();
}

void Organism::increaseStrength() {
    strength += 3;
}

void Organism::increaseAge() {
    age += 1;
}

Organism::~Organism() {}