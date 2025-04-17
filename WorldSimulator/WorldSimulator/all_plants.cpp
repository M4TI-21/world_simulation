#include <string>
#include "defines.h"
#include "world.h"
#include "plant.h"
#include "plant_classes.h"

/*########## Grass ##########*/

Grass::Grass(int strength, int initiative, int x, int y, World* world) : Plant(0, 0, x, y, world) {
    World::addLog("Grass has grown.");
}

void Grass::draw() const {
    attron(COLOR_PAIR('G'));
    mvaddch(y, x, 'W');
    attroff(COLOR_PAIR('G'));
}

string Grass::getTypeName() const {
    return "Grass";
}

void Grass::action() {}
void Grass::collision(Organism* other) {}

Grass::~Grass() {
    World::addLog("Grass was removed.");
}

/*########## Sow Thistle ##########*/

SowThistle::SowThistle(int strength, int initiative, int x, int y, World* world) : Plant(0, 0, x, y, world) {
    World::addLog("Sow thistle has grown.");
}


void SowThistle::draw() const {
    attron(COLOR_PAIR('Y'));
    mvaddch(y, x, '*');
    attroff(COLOR_PAIR('Y'));
}

string SowThistle::getTypeName() const {
    return "Sow thistle";
}

void SowThistle::action() {}
void SowThistle::collision(Organism* other) {}

SowThistle::~SowThistle() {
    World::addLog("Sow thistle was removed.");
}

/*########## Guarana ##########*/

Guarana::Guarana(int strength, int initiative, int x, int y, World* world) : Plant(0, 0, x, y, world) {
    World::addLog("Guarana has grown.");
}


void Guarana::draw() const {
    attron(COLOR_PAIR('R'));
    mvaddch(y, x, 'o');
    attroff(COLOR_PAIR('R'));
}

string Guarana::getTypeName() const {
    return "Guarana";
}

void Guarana::action() {}
void Guarana::collision(Organism* other) {}

Guarana::~Guarana() {
    World::addLog("Guarana was removed.");
}

/*########## Belladonna ##########*/

Belladonna::Belladonna(int strength, int initiative, int x, int y, World* world) : Plant(99, 0, x, y, world) {
    World::addLog("Belladonna has grown.");
}

void Belladonna::draw() const {
    attron(COLOR_PAIR('C'));
    mvaddch(y, x, 'b');
    attroff(COLOR_PAIR('C'));
}

string Belladonna::getTypeName() const {
    return "Belladonna";
}

void Belladonna::action() {}
void Belladonna::collision(Organism* other) {}

Belladonna::~Belladonna() {
    World::addLog("Belladonna was removed.");
}

/*########## Sosowsky's Hogweed ##########*/

Hogweed::Hogweed(int strength, int initiative, int x, int y, World* world) : Plant(10, 0, x, y, world) {
    World::addLog("Sosnowsky's hogweed has grown.");
}

void Hogweed::draw() const {
    attron(COLOR_PAIR('W'));
    mvaddch(y, x, 'Y');
    attroff(COLOR_PAIR('W'));
}

string Hogweed::getTypeName() const {
    return "Sosowsky's hogweed";
}

void Hogweed::action() {}
void Hogweed::collision(Organism* other) {}

Hogweed::~Hogweed() {
    World::addLog("Sosnowsky's hogweed was removed.");
}