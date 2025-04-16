#include <string>
#include "plant.h"
#include "world.h"

Plant::Plant(int strength, int initiative, int x, int y, World* world) : Organism(strength, 0, x, y, world) {}

Plant::~Plant() {}