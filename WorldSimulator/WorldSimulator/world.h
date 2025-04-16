#pragma once
#include <curses.h>
#include <vector>
#include <string>
#include "defines.h"
#include "organism.h"
using namespace std;

class Plant;
class Animal;

class World {
private:
	vector<Organism*> organisms;
	static vector<string> logs;
public:
	World();

	void addNewOrganism(char type);
	void drawWorld();

	static void addLog(string message);
	static void printLog();

	//void makeTurn();

	~World();
};