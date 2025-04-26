#include <curses.h>
#include <fstream>
#include <string>
#include <algorithm>
#include "world.h"
#include "plant_classes.h"
#include "animal_classes.h"
#include "human.h"
using namespace std;

vector<string> World::logs;
int World::round_number = 1;

World::World() {
    World::addLog("World has been created.");
}

void World::addNewOrganism(char type) {
    Organism* new_organism = nullptr;

    switch (type) {
    case GRASS:
        new_organism = new Grass(0, 0, 0, 0, 0, this);
        break;
    case SOW_THISTLE:
        new_organism = new SowThistle(0, 0, 0, 0, 0, this);
        break;
    case GUARANA:
        new_organism = new Guarana(0, 0, 0, 0, 0, this);
        break;
    case BELLADONNA:
        new_organism = new Belladonna(99, 0, 0, 0, 0, this);
        break;
    case HOGWEED:
        new_organism = new Hogweed(10, 0, 0, 0, 0, this);
        break;
    case WOLF:
        new_organism = new Wolf(0, 0, 0, 0, 0, this);
        break;
    case SHEEP:
        new_organism = new Sheep(0, 0, 0, 0, 0, this);
        break;
    case FOX:
        new_organism = new Fox(0, 0, 0, 0, 0, this);
        break;
    case TURTLE:
        new_organism = new Turtle(99, 0, 0, 0, 0, this);
        break;
    case ANTELOPE:
        new_organism = new Antelope(10, 0, 0, 0, 0, this);
        break;
    case HUMAN:
        new_organism = new Human(5, 4, 0, 0, 0, this);
        human = dynamic_cast<Human*>(new_organism);
        isHumanAlive = true;
        break;
    }

    if (new_organism != nullptr) {
        int* position = selectPosition();
        new_organism->setPosition(position[0], position[1]);
        organisms.push_back(new_organism);

        delete[] position;
    }
    refresh();
}

void World::pushOrganism(Organism* organism) {
    organisms.push_back(organism);
    refresh();
}

void World::addLog(string message) {
    logs.push_back(message);

    if (logs.size() > 20) {
        logs.erase(logs.begin());
    }
}

void World::printLog() {
    int i = 0;

    for (string log : logs) {
        mvprintw(CONSOLE_START_Y + i, CONSOLE_START_X, log.c_str());
        i++;
    }
    refresh();
}

void World::drawWorld() {
    clear();
    drawMenu();

    //print all organisms
    for (Organism* organism : organisms) {
        if (organism->checkIfAlive()) {
            organism->draw();
        }
    }

    //print ability availability status
    if (isHumanAlive) {
        attron(COLOR_PAIR('G'));
        mvprintw(BOARD_START_Y - 2, CONSOLE_START_X, human->abilityStatus().c_str());
        attroff(COLOR_PAIR('G'));
    }
    else {
        attron(COLOR_PAIR('R'));
        mvprintw(BOARD_START_Y - 2, CONSOLE_START_X, "Human is dead");
        attroff(COLOR_PAIR('R'));
    }

    printLog();
    refresh();
}

void World::makeTurn() {

    //find alive organisms only
    vector<Organism*> filteredOrganisms;
    for (Organism* organism : organisms) {
        if (organism->checkIfAlive()) {
            filteredOrganisms.push_back(organism);
        }
        
        if (organism->getTypeName() == "Human" && !organism->checkIfAlive()) {
            human = nullptr;
        }
    }
    
    //sort by initiative and age
    sort(filteredOrganisms.begin(), filteredOrganisms.end(), compareInitiative);

    for (Organism* organism : filteredOrganisms) {
        if (organism == nullptr || !organism->checkIfAlive()) {
            continue;
        }

        //check if organism still exists in vector 
        if (organism->getTypeName() == "Human") {
            addLog("Waiting for player's movement.");
            drawWorld();
        }

        //three turns for sow thistle sowing
        if (organism->getTypeName() == "Sow_thistle") {
            organism->action();
            if (!organism->checkIfAlive()) {
                continue;
            }
            organism->action();
        }

        organism->increaseAge();
        if (organism->checkIfAlive()) {
            organism->action();
        }
        drawWorld();
        napms(150);
    }
    removeDeadOrganism();

    addLog("----- Turn " + to_string(round_number++) + " has ended -----");
    addLog("Press space to continue");
    addLog("Press 's' to save and exit");
    addLog("Press 'l' to load saved state");
    drawWorld();
    nodelay(stdscr, FALSE);
    int key = 0;
    while (key != ' ' && key != 's' && key != 'l') {
        key = getch();
    }

    if (key == 's') {
        addLog("Game state has been saved");
        saveGame();
    }
    else if (key == 'l') {
        loadGame();
    }
    nodelay(stdscr, TRUE);
}

//get organism at selected position
Organism* World::getOrganismAt(int x, int y) const {
    for (Organism* organism : organisms) {
        if (organism->getX() == x && organism->getY() == y) {
            return organism;
        }
    }
    return nullptr;
}

//assign flag for dead organism
void World::removeOrganism(Organism* to_remove) {
    //prevent removing human with active ability
    if (to_remove->getTypeName() == "Human") {
        Human* human = dynamic_cast<Human*>(to_remove);
        if (human && human->isAbilityActive()) {
            return;
        }

        isHumanAlive = false;
    }
    
    to_remove->killOrganism();
}

//AI helped me with this function
void World::removeDeadOrganism() {
    //remove organisms with dead flag from vector
    organisms.erase(
        remove_if(organisms.begin(), organisms.end(), 
            [](Organism* organism) {
                if (!organism->checkIfAlive()) {
                    delete organism;
                    organism = nullptr;
                    return true;
                }
                return false;
            }),
        organisms.end()
    );
    drawWorld();
}

void World::saveGame() {
    ofstream file("save.txt");

    for (Organism* organism : organisms) {
        if (!organism->checkIfAlive()) {
            continue;
        }

        file << organism->getTypeName() << " "
            << organism->getStrength() << " "
            << organism->getInitiative() << " "
            << organism->getAge() << " "
            << organism->getX() << " "
            << organism->getY();

        file << endl;
    }
    file.close();
}

void World::loadGame() {
    ifstream file("save.txt");

    //remove present organisms from vector
    while (!organisms.empty()) {
        Organism* organism = organisms.back();
        removeOrganism(organism);
        organisms.pop_back();
        delete organism;
    }

    human = nullptr;

    string typeName;
    int strength, initiative, age, x, y;

    while (file >> typeName >> strength >> initiative >> age >> x >> y) {
        Organism* newOrg = nullptr;
        //assign saved values to class fields
        if (typeName == "Sheep") {
            newOrg = new Sheep(strength, initiative, age, x, y, this);
        }
        else if (typeName == "Wolf") {
            newOrg = new Wolf(strength, initiative, age, x, y, this);
        }
        else if (typeName == "Fox") {
            newOrg = new Fox(strength, initiative, age, x, y, this);
        }
        else if (typeName == "Turtle") {
            newOrg = new Turtle(strength, initiative, age, x, y, this);
        }
        else if (typeName == "Antelope") {
            newOrg = new Antelope(strength, initiative, age, x, y, this);
        }
        else if (typeName == "Grass") {
            newOrg = new Grass(strength, initiative, age, x, y, this);
        }
        else if (typeName == "Sow_thistle") {
            newOrg = new SowThistle(strength, initiative, age, x, y, this);
        }
        else if (typeName == "Guarana") {
            newOrg = new Guarana(strength, initiative, age, x, y, this);
        }
        else if (typeName == "Belladonna") {
            newOrg = new Belladonna(strength, initiative, age, x, y, this);
        }
        else if (typeName == "Hogweed") {
            newOrg = new Hogweed(strength, initiative, age, x, y, this);
        }
        else if (typeName == "Human") {
            newOrg = new Human(strength, initiative, age, x, y, this);
        }

        if (newOrg != nullptr) {
            pushOrganism(newOrg);
        }
    }
    addLog("Game state has beed restored");
    round_number = 1;
}

World::~World() {
    for (Organism* organism : organisms) {
        delete organism;
    }
    organisms.clear();
};
