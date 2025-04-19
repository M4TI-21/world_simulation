#pragma once
#include <curses.h>
#include <string>
#include "world.h"
#include "animal.h"
using namespace std;

class Human : public Animal {
public:
    Human(int strength, int initiative, int x, int y, World* world);

    void draw() const override;
    void action() override;
    void collision(Organism* other) override;
    string getTypeName() const override;
    Organism* copy_organism(int x, int y) const override;

    ~Human();
};