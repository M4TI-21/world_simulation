#pragma once
#include <curses.h>
#include <string>
#include <stdlib.h>
#include "defines.h"
#include "world.h"
using namespace std;

class Plant : public Organism {
public:
    Plant(int strength, int initiative, int age, int x, int y, World* world);

    void draw() const override;
    void action() override;
    void collision(Organism* other) override;
    virtual string getTypeName() const override = 0;
    virtual Organism* copy_organism(int x, int y) const = 0;

    ~Plant();
};