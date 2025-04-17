#pragma once
#include <vector>
using namespace std;

#define WINDOW_W 120
#define WINDOW_H 29

#define CONSOLE_START_X 79
#define CONSOLE_END_X 119
#define CONSOLE_START_Y 3
#define CONSOLE_END_Y 25

// 70 x 25
#define BOARD_START_X 7
#define BOARD_END_X 75
#define BOARD_START_Y 3
#define BOARD_END_Y 26

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
void moveAnimal();
bool isPositionFree(int x, int y);