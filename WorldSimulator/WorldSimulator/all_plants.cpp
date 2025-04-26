#include <string>
#include "defines.h"
#include "world.h"
#include "plant.h"
#include "plant_classes.h"
#include "animal.h"

/*########## Grass ##########*/

Grass::Grass(int strength, int initiative, int age, int x, int y, World* world) : Plant(0, 0, 0, x, y, world) {
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

Organism* Grass::copy_organism(int x, int y) const {
    return new Grass(0, 0, 0, x, y, world);
}

Grass::~Grass() {}

/*########## Sow Thistle ##########*/

SowThistle::SowThistle(int strength, int initiative, int age, int x, int y, World* world) : Plant(0, 0, 0, x, y, world) {
    World::addLog("Sow thistle has grown.");
}


void SowThistle::draw() const {
    attron(COLOR_PAIR('Y'));
    mvaddch(y, x, '*');
    attroff(COLOR_PAIR('Y'));
}

string SowThistle::getTypeName() const {
    return "Sow_thistle";
}

Organism* SowThistle::copy_organism(int x, int y) const {
    return new SowThistle(0, 0, 0, x, y, world);
}

SowThistle::~SowThistle() {}

/*########## Guarana ##########*/

Guarana::Guarana(int strength, int initiative, int age, int x, int y, World* world) : Plant(0, 0, 0, x, y, world) {
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

Organism* Guarana::copy_organism(int x, int y) const {
    return new Guarana(0, 0, 0, x, y, world);
}

void Guarana::collision(Organism* animal) {
    Guarana::increaseStrength();
    world->addLog(animal->getTypeName() + " ate " + this->getTypeName());
    world->addLog(animal->getTypeName() + "'s strength was increased.");
    world->removeOrganism(this);
}

Guarana::~Guarana() {}

/*########## Belladonna ##########*/

Belladonna::Belladonna(int strength, int initiative, int age, int x, int y, World* world) : Plant(99, 0, 0, x, y, world) {
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

Organism* Belladonna::copy_organism(int x, int y) const {
    return new Belladonna(99, 0, 0, x, y, world);
}

void Belladonna::collision(Organism* other) {
    world->removeOrganism(this);
    world->removeOrganism(other);
    world->addLog(other->getTypeName() + " was killed by Belladonna.");
}

Belladonna::~Belladonna() {}

/*########## Sosowsky's Hogweed ##########*/

Hogweed::Hogweed(int strength, int initiative, int age, int x, int y, World* world) : Plant(10, 0, 0, x, y, world) {
    World::addLog("Sosnowsky's hogweed has grown.");
}

void Hogweed::draw() const {
    attron(COLOR_PAIR('W'));
    mvaddch(y, x, 'Y');
    attroff(COLOR_PAIR('W'));
}

string Hogweed::getTypeName() const {
    return "Hogweed";
}

Organism* Hogweed::copy_organism(int x, int y) const {
    return new Hogweed(10, 0, 0, x, y, world);
}

void Hogweed::action() {
    vector<vector<int>> neigbouring_positions = findNeighbouringPos(x, y);

    if (neigbouring_positions.empty()) {
        world->addLog("No place to sow for " + this->getTypeName() + ".");
        return;
    }

    bool success = rand() % 5 == 0; //20% chance for sowing
    int newX = x;
    int newY = y;

    if (success && isAlive) {
        int position = rand() % neigbouring_positions.size();
        newX = neigbouring_positions[position][0];
        newY = neigbouring_positions[position][1];

        if (world->getOrganismAt(newX, newY) == nullptr) {
            Organism* sowed_plant = this->copy_organism(newX, newY);
            world->pushOrganism(sowed_plant);
        }
    }

    for (vector<int> position : neigbouring_positions) {
        newX = position[0];
        newY = position[1];

        Organism* target = world->getOrganismAt(newX, newY);
        bool isAnimal = dynamic_cast<Animal*>(target);

        if (target && isAnimal) {
            world->removeOrganism(target);
            world->addLog(target->getTypeName() + " was killed by Hogweed.");
        }
    }
}

void Hogweed::collision(Organism* other) {
    world->removeOrganism(this);
    world->removeOrganism(other);
    world->addLog(other->getTypeName() + " was killed by Hogweed.");
}

Hogweed::~Hogweed() {}