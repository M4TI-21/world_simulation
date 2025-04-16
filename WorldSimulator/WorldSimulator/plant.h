#pragma once
#include <curses.h>
#include <stdlib.h>
#include "defines.h"
#include "world.h"

class Plant : public Organism {
public:
    Plant(int strength, int initiative, int x, int y, World* world);

    void draw() const override {
        attron(COLOR_PAIR('G'));
        mvaddch(y, x, '*');
        attroff(COLOR_PAIR('G'));
    }

    void action() override {}
    void collision(Organism* other) override {}

    ~Plant();
};