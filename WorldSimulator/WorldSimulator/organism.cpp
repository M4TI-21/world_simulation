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

void Organism::killOrganism() {
    isAlive = false;
}

bool Organism::checkIfAlive() const {
    return isAlive;
}

vector<vector<int>> Organism::findNeighbouringPos(int x, int y) {
    vector<vector<int>> neigbouring_positions;

    if (x > (BOARD_START_X + 1)) {
        neigbouring_positions.push_back({ x - 1, y });
    }
    if (x < (BOARD_END_X - 1)) {
        neigbouring_positions.push_back({ x + 1, y });
    }
    if (y > (BOARD_START_Y + 1)) {
        neigbouring_positions.push_back({ x, y - 1 });
    }
    if (y < (BOARD_END_Y - 1)) {
        neigbouring_positions.push_back({ x, y + 1 });
    }

    return neigbouring_positions;
}

Organism::~Organism() {}