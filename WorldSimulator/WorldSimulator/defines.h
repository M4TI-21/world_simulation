#pragma once
#include <vector>
#include "organism.h"
using namespace std;

#define WINDOW_W 120
#define WINDOW_H 29

#define CONSOLE_START_X 70
#define CONSOLE_END_X 118
#define CONSOLE_START_Y 5
#define CONSOLE_END_Y 24

// 70 x 25
#define BOARD_START_X 7
#define BOARD_END_X 60
#define BOARD_START_Y 5
#define BOARD_END_Y 24

class Organism;

enum OrganismsTypes {
	GRASS,
	SOW_THISTLE,
	GUARANA,
	BELLADONNA,
	HOGWEED,
	WOLF,
	SHEEP,
	FOX,
	TURTLE,
	ANTELOPE,
	HUMAN
};

void drawMenu();
int* selectPosition();
bool isPositionFree(int x, int y);
bool compareInitiative(Organism* org1, Organism* org2);
bool compareAge(Organism* org1, Organism* org2);