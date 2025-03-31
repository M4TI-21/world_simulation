#pragma once
#include <curses.h>
#include "defines.h"
#include "organism.h"

class World {
private:
	//lista organizmów

public:
	World() {
		mvaddstr(CONSOLE_H_A, CONSOLE_W_A, "World has been created.");
	};

	void makeTurn();

	void drawWorld();

	void addOrganism();


	~World() {
		mvaddstr(CONSOLE_H_A, CONSOLE_W_A, "World has been destroyed.");
	};
};