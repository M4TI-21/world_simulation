#include "animal.h"
#include "world.h"

Animal::Animal(int strength, int initiative, int x, int y, World* world) : Organism(strength, initiative, x, y, world) {
	World::addLog("An animal has been added to the world.");
}

Animal::~Animal() {}