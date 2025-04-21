#include <string>
#include <vector>
#include "defines.h"
#include "plant.h"
#include "world.h"
using namespace std;

Plant::Plant(int strength, int initiative, int age, int x, int y, World* world) : Organism(strength, 0, 0, x, y, world) {}

void Plant::action() {
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
}

void Plant::collision(Organism* animal) {
    world->removeOrganism(this);
    world->addLog(animal->getTypeName() + " ate " + this->getTypeName());
}

Plant::~Plant() {}