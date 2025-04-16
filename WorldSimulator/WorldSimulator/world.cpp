#include <curses.h>
#include <string>
#include "world.h"
#include "plant_classes.h"
using namespace std;

vector<string> World::logs;

World::World() {
    World::addLog("World has been created.");
}

void World::addNewOrganism(char type) {
    Organism* new_organism = nullptr;

    switch (type) {
    case GRASS:
        new_organism = new Grass(0, 0, 0, 0, this);
        break;
    case SOW_THISTLE:
        new_organism = new SowThistle(0, 0, 0, 0, this);
        break;
    case GUARANA:
        new_organism = new Guarana(0, 0, 0, 0, this);
        break;
    case BELLADONNA:
        new_organism = new Belladonna(99, 0, 0, 0, this);
        break;
    case HOGWEED:
        new_organism = new Hogweed(10, 0, 0, 0, this);
        break;
    case WOLF:
        new_organism = new Grass(0, 0, 0, 0, this);
        break;
    case SHEEP:
        new_organism = new SowThistle(0, 0, 0, 0, this);
        break;
    case FOX:
        new_organism = new Guarana(0, 0, 0, 0, this);
        break;
    case TURTLE:
        new_organism = new Belladonna(99, 0, 0, 0, this);
        break;
    case ANTELOPE:
        new_organism = new Hogweed(10, 0, 0, 0, this);
        break;
    }

    if (new_organism != nullptr) {
        int* position = selectPosition();
        new_organism->setPosition(position[0], position[1]);
        organisms.push_back(new_organism);
    }
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
}

void World::drawWorld() {
    drawMenu();

    for (Organism* organism : organisms) {

        organism->draw();
    }
    printLog();
    refresh();
}

World::~World() {
    for (Organism* org : organisms) {
        delete org;
    }
    organisms.clear();
};