#include "animal.h"
#include "world.h"
#include "defines.h"
#include "animal_classes.h"


Animal::Animal(int strength, int initiative, int age, int x, int y, World* world) : Organism(strength, initiative, age, x, y, world) {}


void Animal::action() {
    vector<vector<int>> neigbouring_positions = findNeighbouringPos(x, y);
    savePrevPos();

    if (neigbouring_positions.empty()) {
        world->addLog(getTypeName() + " has no place to move.");
        return;
    }
    
    int position = rand() % neigbouring_positions.size();
    int newX = neigbouring_positions[position][0];
    int newY = neigbouring_positions[position][1];

    Organism* met_organism = world->getOrganismAt(newX, newY);
    if (met_organism && met_organism != this) {
        //breeding when same species meet
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
            Animal::collision(met_organism);
        }
    }

    if (!met_organism || met_organism->getTypeName() != this->getTypeName()) {
        mvaddch(y, x, ' ');
        setPosition(newX, newY);
    }
}

void Animal::collision(Organism* opponent) {
    bool isOppAnimal = dynamic_cast<Animal*>(opponent);

    if (isOppAnimal) {

        if (dynamic_cast<Turtle*>(opponent)) {
            Turtle* turtle = dynamic_cast<Turtle*>(opponent);
            turtle->collision(this);
            return;
        }

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
            world->removeOrganism(opponent);
            world->addLog(this->getTypeName() + " defeated " + opponent->getTypeName());
        }
    }
    else {
        //instant death when eating poisonous plants
        string oppType = opponent->getTypeName();
        if (oppType == "Belladonna" || oppType == "Hogweed") {
            world->removeOrganism(this);
            world->removeOrganism(opponent);
            world->addLog(this->getTypeName() + " was killed by " + opponent->getTypeName());
        }
        else {
            world->removeOrganism(opponent);
            world->addLog(this->getTypeName() + " ate " + opponent->getTypeName());
        }
    }
}

Animal::~Animal() {}