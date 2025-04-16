#include <string>
#include "defines.h"
#include "world.h"
#include "plant.h"
#include "plant_classes.h"

/*########## Grass ##########*/

Grass::Grass(int strength, int initiative, int x, int y, World* world) : Plant(0, 0, x, y, world) {
    World::addLog("Grass has grown.");
}

Grass::~Grass() {
    World::addLog("Grass was removed.");
}

/*########## Sow Thistle ##########*/

SowThistle::SowThistle(int strength, int initiative, int x, int y, World* world) : Plant(0, 0, x, y, world) {
    World::addLog("Sow thistle has grown.");
}

SowThistle::~SowThistle() {
    World::addLog("Sow thistle was removed.");
}

/*########## Guarana ##########*/

Guarana::Guarana(int strength, int initiative, int x, int y, World* world) : Plant(0, 0, x, y, world) {
    World::addLog("Guarana has grown.");
}

Guarana::~Guarana() {
    World::addLog("Guarana was removed.");
}

/*########## Belladonna ##########*/

Belladonna::Belladonna(int strength, int initiative, int x, int y, World* world) : Plant(99, 0, x, y, world) {
    World::addLog("Belladonna has grown.");
}

Belladonna::~Belladonna() {
    World::addLog("Belladonna was removed.");
}

/*########## Sosowsky's Hogweed ##########*/

Hogweed::Hogweed(int strength, int initiative, int x, int y, World* world) : Plant(10, 0, x, y, world) {
    World::addLog("Sosnowsky's hogweed has grown.");
}

Hogweed::~Hogweed() {
    World::addLog("Sosnowsky's hogweed was removed.");
}