#include <string>
#include <vector>
#include "defines.h"
#include "world.h"
#include "animal.h"
#include "animal_classes.h"
using namespace std;

/*########## Wolf ##########*/

Wolf::Wolf(int strength, int initiative, int x, int y, World* world)
    : Animal(9, 5, x, y, world) {
    World::addLog("Wolf has appeared on the world.");
}

void Wolf::draw() const {
    attron(COLOR_PAIR('W'));
    mvaddch(y, x, '&');
    attroff(COLOR_PAIR('W'));
}

string Wolf::getTypeName() const {
    return "Wolf";
}

Wolf::~Wolf() {
    World::addLog("Wolf was removed.");
}

/*########## Sheep ##########*/

Sheep::Sheep(int strength, int initiative, int x, int y, World* world) : Animal(4, 4, x, y, world) {
    World::addLog("Sheep has appeared on the world.");
}

void Sheep::draw() const {
    attron(COLOR_PAIR('W'));
    mvaddch(y, x, '#');
    attroff(COLOR_PAIR('W'));
}

string Sheep::getTypeName() const {
    return "Sheep";
}

Sheep::~Sheep() {
    World::addLog("Sheep was removed.");
}

/*########## Fox ##########*/

Fox::Fox(int strength, int initiative, int x, int y, World* world) : Animal(3, 7, x, y, world) {
    World::addLog("Fox has appeared on the world.");
}

void Fox::draw() const {
    attron(COLOR_PAIR('R'));
    mvaddch(y, x, '$');
    attroff(COLOR_PAIR('R'));
}

string Fox::getTypeName() const {
    return "Fox";
}

Fox::~Fox() {
    World::addLog("Fox was removed.");
}

/*########## Turtle ##########*/

Turtle::Turtle(int strength, int initiative, int x, int y, World* world) : Animal(2, 1, x, y, world) {
    World::addLog("Turtle has appeared on the world.");
}

void Turtle::draw() const {
    attron(COLOR_PAIR('G'));
    mvaddch(y, x, 'Q');
    attroff(COLOR_PAIR('G'));
}

string Turtle::getTypeName() const {
    return "Turtle";
}

void Turtle::action() {
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

    int position = rand() % neigbouring_positions.size();
    int success = rand() % 3;

    mvaddch(y, x, ' ');
    if (success == 0) {
        int newX = neigbouring_positions[position][0];
        int newY = neigbouring_positions[position][1];

        setPosition(newX, newY);
        world->addLog(getTypeName() + " moved to (" + to_string(newX) + "," + to_string(newY) + ")");
    }
    else {
        world->addLog(getTypeName() + " didn't move.");
    }
}

void Turtle::collision(Organism* other) {}

Turtle::~Turtle() {
    World::addLog("Turtle was removed.");
}

/*########## Antelope ##########*/

Antelope::Antelope(int strength, int initiative, int x, int y, World* world) : Animal(4, 4, x, y, world) {
    World::addLog("Antelope has appeared on the world.");
}

void Antelope::draw() const {
    attron(COLOR_PAIR('Y'));
    mvaddch(y, x, 'V');
    attroff(COLOR_PAIR('Y'));
}

string Antelope::getTypeName() const {
    return "Antelope";
}

void Antelope::action() {
    vector<vector<int>> neigbouring_positions;

    if (x > (BOARD_START_X + 2)) {
        neigbouring_positions.push_back({ x - 2, y });
    }
    if (x < (BOARD_END_X - 2)) {
        neigbouring_positions.push_back({ x + 2, y });
    }
    if (y > (BOARD_START_Y + 2)) {
        neigbouring_positions.push_back({ x, y - 2 });
    }
    if (y < (BOARD_END_Y - 2)) {
        neigbouring_positions.push_back({ x, y + 2 });
    }

    int position = rand() % neigbouring_positions.size();

    mvaddch(y, x, ' ');

    int newX = neigbouring_positions[position][0];
    int newY = neigbouring_positions[position][1];

    setPosition(newX, newY);
    world->addLog(getTypeName() + " moved to (" + to_string(newX) + "," + to_string(newY) + ")");
    
}

void Antelope::collision(Organism* opponent) {

    int escape = rand() % 1;

    if (escape == 0) {
        world->addLog(Antelope::getTypeName() + " ran away from fight with " + opponent->getTypeName() + ".");
        Antelope::action();
        return;
    }
    else {
        int antelope_strength = Antelope::getStrength();
        int opponent_strength = opponent->getStrength();

        if (antelope_strength > opponent_strength) {
            world->removeOrganism(opponent);
            world->addLog(Antelope::getTypeName() + " defeated " + opponent->getTypeName());
        }
        else if (antelope_strength < opponent_strength) {
            world->removeOrganism(this);
            world->addLog(opponent->getTypeName() + " defeated " + Antelope::getTypeName());
        }
        else {
            int success = rand() % 1;
            if (success == 0) {
                world->removeOrganism(opponent);
                world->addLog(Antelope::getTypeName() + " defeated " + opponent->getTypeName());
            }
            else {
                world->removeOrganism(this);
                world->addLog(opponent->getTypeName() + " defeated " + Antelope::getTypeName());
            }
        }
    }
}

Antelope::~Antelope() {
    World::addLog("Antelope was removed.");
}