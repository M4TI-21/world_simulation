#include <curses.h>
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

    if (logs.size() > 24) {
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

    for (Organism* organism : organisms) {

        organism->draw();
    }
    printLog();
    refresh();
}

void World::makeTurn() {

    vector<Organism*> currentOrganisms = organisms;
    sort(currentOrganisms.begin(), currentOrganisms.end(), compareInitiative);

    for (Organism* organism : currentOrganisms) {
        if (organism->getTypeName() == "Human") {
            addLog("Waiting for player's movement.");
            drawWorld();
        }
        if (organism->getTypeName() == "Sow thistle") {
            organism->action();
            organism->action();
            drawWorld();
        }

        organism->increaseAge();
        organism->action();
        drawWorld();
        napms(200);
    }
    addLog("----- Turn " + to_string(round_number++) + " has ended -----");
    addLog("Press space to continue");
    drawWorld();
    nodelay(stdscr, FALSE);
    int key = 0;
    while (key != ' ') {
        key = getch();
    }
    nodelay(stdscr, TRUE);
}

Organism* World::getOrganismAt(int x, int y) const {
    for (Organism* organism : organisms) {
        if (organism->getX() == x && organism->getY() == y) {
            return organism;
        }
    }
    return nullptr;
}

void World::removeOrganism(Organism* to_remove) {
    auto index = std::remove(organisms.begin(), organisms.end(), to_remove);
    organisms.erase(index, organisms.end());
}

World::~World() {
    for (Organism* organism : organisms) {
        delete organism;
    }
    organisms.clear();
};
