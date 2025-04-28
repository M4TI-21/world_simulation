#include <curses.h>
#include <time.h>

#include "defines.h"
#include "world.h"
#include "plant_classes.h"
#include "animal_classes.h"
#include "organism.h"
#include "human.h"
using namespace std;

void initialize_colors() {
    start_color();
    init_pair('W', COLOR_WHITE, COLOR_BLACK);
    init_pair('R', COLOR_RED, COLOR_BLACK);
    init_pair('G', COLOR_GREEN, COLOR_BLACK);
    init_pair('Y', COLOR_YELLOW, COLOR_BLACK);
    init_pair('C', COLOR_CYAN, COLOR_BLACK);
    init_pair('M', COLOR_MAGENTA, COLOR_BLACK);
}

void drawMenu() {
    mvaddstr(0, 0, "World Simulation by Mateusz Hann - 203308");

    for (int i = 0; i < WINDOW_W; i++) {
        mvaddch(4, i, '~');
        mvaddch(WINDOW_H - 4, i, '~');
    }
    for (int j = 4; j < WINDOW_H - 3; j++) {
        mvaddch(j, 5, '|');
        mvaddch(j, BOARD_END_X + 1, '|');
    }
}

bool isPositionFree(int x, int y) {
    char position = mvinch(y, x);

    if (position == ' ') {
        return true;
    }
    else {
        return false;
    }
}

int* selectPosition() {
    int x, y;
    bool isFree = false;

    while (!isFree) {
        x = rand() % (BOARD_END_X - BOARD_START_X) + BOARD_START_X;
        y = rand() % (BOARD_END_Y - BOARD_START_Y) + BOARD_START_Y;

        isFree = isPositionFree(x, y);
    }

    int* position = new int[2];
    position[0] = x;
    position[1] = y;

    return position;
}

bool compareInitiative(Organism* org1, Organism* org2) {
    return org1->getInitiative() > org2->getInitiative();
}

bool compareAge(Organism* org1, Organism* org2) {
    return org1->getAge() > org2->getAge();
}

int main() {
    
    initscr();
    noecho();                   //disable key printing
    curs_set(0);                //hide cursor
    keypad(stdscr, TRUE);       //special keys are enabled
    srand(time(0));

    initialize_colors();

    World* world = new World();
    world->addNewOrganism(GRASS);
    world->addNewOrganism(GRASS);
    world->addNewOrganism(GRASS);
    world->addNewOrganism(SOW_THISTLE);
    world->addNewOrganism(GUARANA);
    world->addNewOrganism(GUARANA);
    world->addNewOrganism(GUARANA);
    world->addNewOrganism(BELLADONNA);
    world->addNewOrganism(BELLADONNA);
    world->addNewOrganism(BELLADONNA);
    world->addNewOrganism(HOGWEED);
    world->addNewOrganism(HOGWEED);
    world->addNewOrganism(HOGWEED);

    world->addNewOrganism(WOLF);
    world->addNewOrganism(WOLF);
    world->addNewOrganism(WOLF);
    world->addNewOrganism(SHEEP);
    world->addNewOrganism(SHEEP);
    world->addNewOrganism(SHEEP);
    world->addNewOrganism(FOX);
    world->addNewOrganism(FOX);
    world->addNewOrganism(FOX);
    world->addNewOrganism(TURTLE);
    world->addNewOrganism(TURTLE);
    world->addNewOrganism(TURTLE);
    world->addNewOrganism(ANTELOPE);
    world->addNewOrganism(ANTELOPE);
    world->addNewOrganism(ANTELOPE);

    world->addNewOrganism(HUMAN);

    world->drawWorld();

    while (true) {
        world->makeTurn();
    }

    return 0;
}