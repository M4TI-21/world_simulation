#include "animal.h"
#include "world.h"
#include "defines.h"

Animal::Animal(int strength, int initiative, int x, int y, World* world) : Organism(strength, initiative, x, y, world) {}

void Animal::draw() const {
    attron(COLOR_PAIR('R'));
    mvaddch(y, x, '#');
    attroff(COLOR_PAIR('R'));
}

void Animal::action() {
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
    
    if (neigbouring_positions.empty()) {
        world->addLog(getTypeName() + " has no place to move.");
        return;
    }
    
    int position = rand() % neigbouring_positions.size();

    mvaddch(y, x, ' ');
    int newX = neigbouring_positions[position][0];
    int newY = neigbouring_positions[position][1];

    setPosition(newX, newY);
    world->addLog(getTypeName() + " moved to (" + to_string(newX) + "," + to_string(newY) + ")");
}

void Animal::collision(Organism* opponent) {
    int animal_strength = Animal::getStrength();
    int opponent_strength = opponent->getStrength();

    if (animal_strength > opponent_strength) {
        world->removeOrganism(opponent);
        world->addLog(this->getTypeName() + " defeated " + opponent->getTypeName());
    }
    else if (animal_strength < opponent_strength) {
        world->removeOrganism(this);
        world->addLog(opponent->getTypeName() + " defeated " + this->getTypeName());
    }
    else {
        int success = rand() % 1;
        if (success == 0) {
            world->removeOrganism(opponent);
        }
        else {
            world->removeOrganism(this);
            world->addLog(opponent->getTypeName() + " defeated " + this->getTypeName());
        }
    }
}

Animal::~Animal() {}