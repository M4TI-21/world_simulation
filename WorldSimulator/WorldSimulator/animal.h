#pragma once
#include <curses.h>
#include <stdlib.h>
#include "defines.h"
#include "world.h"

class Animal : public Organism {
public:
    Animal(int strength, int initiative, int x, int y, World* world);

    void draw() const override {
        attron(COLOR_PAIR('R'));
        mvaddch(y, x, '#');
        attroff(COLOR_PAIR('R'));
    }

    void action() override {}
    void collision(Organism* other) override {}

    ~Animal();
};