#pragma once
#include <curses.h>
#include <vector>
#include <string>
#include "defines.h"
#include "organism.h"
using namespace std;

class Organism;
class Human;

class World {
private:
	vector<Organism*> organisms;
	Human* human = nullptr;
public:
	static vector<string> logs;
	static int round_number;
	bool isHumanAlive = false;

	World();

	void addNewOrganism(char type);
	void pushOrganism(Organism* organism);
	void drawWorld();
	static void addLog(string message);
	static void printLog();
	void makeTurn();
	Organism* getOrganismPos(int x, int y) const;
	void removeOrganism(Organism* organism);
	void removeDeadOrganism();

	void loadGame();
	void saveGame();

	~World();
};