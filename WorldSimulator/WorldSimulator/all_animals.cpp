#include <string>
#include <vector>
#include "defines.h"
#include "world.h"
#include "animal.h"
#include "animal_classes.h"
using namespace std;

/*########## Wolf ##########*/

Wolf::Wolf(int strength, int initiative, int age, int x, int y, World* world) : Animal(9, 5, 0, x, y, world) {
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

Organism* Wolf::copy_organism(int x, int y) const {
    return new Wolf(9, 5, 0, x, y, world);
}

Wolf::~Wolf() {}

/*########## Sheep ##########*/

Sheep::Sheep(int strength, int initiative, int age, int x, int y, World* world) : Animal(4, 4, 0, x, y, world) {
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

Organism* Sheep::copy_organism(int x, int y) const {
    return new Sheep(4, 4, 0, x, y, world);
}

Sheep::~Sheep() {}

/*########## Fox ##########*/

Fox::Fox(int strength, int initiative, int age, int x, int y, World* world) : Animal(3, 7, 0, x, y, world) {
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

Organism* Fox::copy_organism(int x, int y) const {
    return new Fox(3, 7, 0, x, y, world);
}

void Fox::action() {
    vector<vector<int>> neigbouring_positions;
    savePrevPos();

    if (x > (BOARD_START_X + 1)) {
        Organism* opp = world->getOrganismAt(x - 1, y);
        if (!opp || opp->getStrength() <= this->getStrength()) {
            neigbouring_positions.push_back({ x - 1, y });
        }
    }
    if (x < (BOARD_END_X - 1)) {
        Organism* opp = world->getOrganismAt(x + 1, y);
        if (!opp || opp->getStrength() <= this->getStrength()) {
            neigbouring_positions.push_back({ x + 1, y });
        }
    }
    if (y > (BOARD_START_Y + 1)) {
        Organism* opp = world->getOrganismAt(x, y - 1);
        if (!opp || opp->getStrength() <= this->getStrength()) {
            neigbouring_positions.push_back({ x , y - 1 });
        }
    }
    if (y < (BOARD_END_Y - 1)) {
        Organism* opp = world->getOrganismAt(x, y + 1);
        if (!opp || opp->getStrength() <= this->getStrength()) {
            neigbouring_positions.push_back({ x, y + 1});
        }
    }

    if (neigbouring_positions.empty()) {
        world->addLog("Fox has no safe place to move.");
        return;
    }

    int position = rand() % neigbouring_positions.size();
    int newX = neigbouring_positions[position][0];
    int newY = neigbouring_positions[position][1];

    Organism* met_organism = world->getOrganismAt(newX, newY);
    if (met_organism && met_organism != this) {
        if (met_organism->getTypeName() == this->getTypeName()) {

            neigbouring_positions.erase(neigbouring_positions.begin() + position);

            if (neigbouring_positions.empty()) {
                world->addLog("No space for new animal");
                return;
            }
            else {
                position = rand() % neigbouring_positions.size();
                newX = neigbouring_positions[position][0];
                newY = neigbouring_positions[position][1];

                Organism* new_animal = this->copy_organism(newX, newY);
                world->pushOrganism(new_animal);

                return;
            }
        }
        else {
            Fox::collision(met_organism);
        }
    }

    if (!met_organism || met_organism->getTypeName() != this->getTypeName()) {
        mvaddch(y, x, ' ');
        setPosition(newX, newY);
    }
}

Fox::~Fox() {}

/*########## Turtle ##########*/

Turtle::Turtle(int strength, int initiative, int age, int x, int y, World* world) : Animal(2, 1, 0, x, y, world) {
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

Organism* Turtle::copy_organism(int x, int y) const {
    return new Turtle(2, 1, 0, x, y, world);
}

void Turtle::action() {
    vector<vector<int>> neigbouring_positions = findNeighbouringPos(x, y);
    savePrevPos();

    int position = rand() % neigbouring_positions.size();
    int success = rand() % 4;

    if (success == 0) {
        int newX = neigbouring_positions[position][0];
        int newY = neigbouring_positions[position][1];

        Organism* met_organism = world->getOrganismAt(newX, newY);
        if (met_organism && met_organism != this) {
            if (met_organism->getTypeName() == this->getTypeName()) {
                neigbouring_positions.erase(neigbouring_positions.begin() + position);

                if (neigbouring_positions.empty()) {
                    world->addLog("No space for new animal");
                    return;
                }
                else {
                    position = rand() % neigbouring_positions.size();
                    newX = neigbouring_positions[position][0];
                    newY = neigbouring_positions[position][1];

                    Organism* new_animal = this->copy_organism(newX, newY);
                    world->pushOrganism(new_animal);

                    return;
                }
            }
            else {
                Turtle::collision(met_organism);
            }
        }

        if (!met_organism || met_organism->getTypeName() != this->getTypeName()) {
            mvaddch(y, x, ' ');
            setPosition(newX, newY);
        }
    }
}

void Turtle::collision(Organism* opponent) {
    bool isOppAnimal = dynamic_cast<Animal*>(opponent);
    if (isOppAnimal) {
        int opponent_strength = opponent->getStrength();
        if (opponent_strength < 5) {
            world->addLog(opponent->getTypeName() + " was reflected by Turtle.");
            opponent->setPosition(opponent->getPrevX(), opponent->getPrevY());
            return;
        }
        else {
            int turtle_strength = Turtle::getStrength();

            if (turtle_strength > opponent_strength) {
                world->removeOrganism(opponent);
                world->addLog(Turtle::getTypeName() + " defeated " + opponent->getTypeName());
            }
            else if (turtle_strength < opponent_strength) {
                world->removeOrganism(this);
                world->addLog(opponent->getTypeName() + " defeated " + Turtle::getTypeName());
            }
            else {
                world->removeOrganism(opponent);
                world->addLog(this->getTypeName() + " defeated " + opponent->getTypeName());
            }
        }
    }
}

Turtle::~Turtle() {}

/*########## Antelope ##########*/

Antelope::Antelope(int strength, int initiative, int age, int x, int y, World* world) : Animal(4, 4, 0, x, y, world) {
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

Organism* Antelope::copy_organism(int x, int y) const {
    return new Antelope(4, 4, 0, x, y, world);
}

void Antelope::action() {
    vector<vector<int>> neigbouring_positions;
    savePrevPos();

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
    int newX = neigbouring_positions[position][0];
    int newY = neigbouring_positions[position][1];

    Organism* met_organism = world->getOrganismAt(newX, newY);
    if (met_organism && met_organism != this) {
        if (met_organism->getTypeName() == this->getTypeName()) {
            vector<vector<int>> neigbouring_positions = findNeighbouringPos(x, y);

            if (neigbouring_positions.empty()) {
                world->addLog("No space for new animal");
                return;
            }
            else {
                position = rand() % neigbouring_positions.size();
                newX = neigbouring_positions[position][0];
                newY = neigbouring_positions[position][1];

                Organism* new_animal = this->copy_organism(newX, newY);
                world->pushOrganism(new_animal);

                return;
            }
        }
        else {
            Antelope::collision(met_organism);
        }
    }

    if (!met_organism || met_organism->getTypeName() != this->getTypeName()) {
        mvaddch(y, x, ' ');
        setPosition(newX, newY);
    }
}

void Antelope::collision(Organism* opponent) {
    bool escape = rand() % 2 == 0;

    bool isOppAnimal = dynamic_cast<Animal*>(opponent);
    if (isOppAnimal) {
        if (escape) {
            world->addLog(Antelope::getTypeName() + " ran away from fight with " + opponent->getTypeName() + ".");
            
            vector<vector<int>> neigbouring_positions = findNeighbouringPos(x, y);
            int position = rand() % neigbouring_positions.size();
            int newX = neigbouring_positions[position][0];
            int newY = neigbouring_positions[position][1];
            setPosition(newX, newY);
            return;
        }
        else {

            if (opponent->getTypeName() == "Turtle") {
                Turtle* turtle = dynamic_cast<Turtle*>(opponent);
                turtle->collision(this);
                return;
            }

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
                world->removeOrganism(opponent);
                world->addLog(this->getTypeName() + " defeated " + opponent->getTypeName());
            }
        }
    }
    else {
        string oppType = opponent->getTypeName();
        if (oppType == "Belladonna" || oppType == "Hogweed") {
            world->removeOrganism(this);
            world->removeOrganism(opponent);
            world->addLog(this->getTypeName() + " was poisoned by " + opponent->getTypeName());
        }
        else {
            world->removeOrganism(opponent);
            world->addLog(this->getTypeName() + " ate " + opponent->getTypeName());
        }
    }
}

Antelope::~Antelope() {}