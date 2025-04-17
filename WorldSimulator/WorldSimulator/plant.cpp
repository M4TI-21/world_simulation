#include <string>
#include <vector>
#include "defines.h"
#include "plant.h"
#include "world.h"
using namespace std;

Plant::Plant(int strength, int initiative, int x, int y, World* world) : Organism(strength, 0, x, y, world) {}

void Plant::draw() const {
    attron(COLOR_PAIR('G'));
    mvaddch(y, x, '*');
    attroff(COLOR_PAIR('G'));
}

void Plant::action() {
    world->addLog(getTypeName() + " does its action");
}

void Plant::collision(Organism* other) {}

Plant::~Plant() {}