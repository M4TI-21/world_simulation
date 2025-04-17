#pragma once
#include <curses.h>
#include <stdlib.h>
#include "defines.h"
#include "world.h"
using namespace std;

class Plant : public Organism {
public:
    Plant(int strength, int initiative, int x, int y, World* world);

    void draw() const override;
    void action() override;
    void collision(Organism* other) override;
    virtual string getTypeName() const override = 0;

    ~Plant();
};