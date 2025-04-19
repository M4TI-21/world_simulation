#pragma once
#include <curses.h>
#include <vector>
#include <string>
#include "defines.h"
#include "organism.h"
using namespace std;

class Organism;

class World {
private:
	vector<Organism*> organisms;
public:
	static vector<string> logs;
	static int round_number;
	World();

	void addNewOrganism(char type);
	void pushOrganism(Organism* organism);
	void drawWorld();
	static void addLog(string message);
	static void printLog();
	void makeTurn();
	Organism* getOrganismAt(int x, int y) const;
	void removeOrganism(Organism* organism);

	~World();
};