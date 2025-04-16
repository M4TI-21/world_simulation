#include <string>
#include "defines.h"
#include "world.h"
#include "animal.h"
#include "animal_classes.h"

/*########## Wolf ##########*/

Wolf::Wolf(int strength, int initiative, int x, int y, World* world) : Animal(9, 5, x, y, world) {
    World::addLog("Wolf has appeared on the world.");
}

Wolf::~Wolf() {
    World::addLog("Wolf was removed.");
}

/*########## Sheep ##########*/

Sheep::Sheep(int strength, int initiative, int x, int y, World* world) : Animal(4, 4, x, y, world) {
    World::addLog("Sheep has appeared on the world.");
}

Sheep::~Sheep() {
    World::addLog("Sheep was removed.");
}

/*########## Fox ##########*/

Fox::Fox(int strength, int initiative, int x, int y, World* world) : Animal(3, 7, x, y, world) {
    World::addLog("Fox has appeared on the world.");
}

Fox::~Fox() {
    World::addLog("Fox was removed.");
}

/*########## Turtle ##########*/

Turtle::Turtle(int strength, int initiative, int x, int y, World* world) : Animal(2, 1, x, y, world) {
    World::addLog("Turtle has appeared on the world.");
}

Turtle::~Turtle() {
    World::addLog("Turtle was removed.");
}

/*########## Antelope ##########*/

Antelope::Antelope(int strength, int initiative, int x, int y, World* world) : Animal(4, 4, x, y, world) {
    World::addLog("Antelope has appeared on the world.");
}

Antelope::~Antelope() {
    World::addLog("Antelope was removed.");
}