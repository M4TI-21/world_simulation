#pragma once
#include "world.h"
#include "animal.h"

/*########## Wolf ##########*/

class Wolf : public Animal {
public:
    Wolf(int strength, int initiative, int x, int y, World* world);

    void draw() const override {
        attron(COLOR_PAIR('W'));
        mvaddch(y, x, '&');
        attroff(COLOR_PAIR('W'));
    }

    void action() override {}
    void collision(Organism* other) override {}

    ~Wolf();
};

/*########## Sheep ##########*/

class Sheep : public Animal {
public:
    Sheep(int strength, int initiative, int x, int y, World* world);

    void draw() const override {
        attron(COLOR_PAIR('W'));
        mvaddch(y, x, '#');
        attroff(COLOR_PAIR('W'));
    }

    void action() override {}
    void collision(Organism* other) override {}

    ~Sheep();
};

/*########## Fox ##########*/

class Fox : public Animal {
public:
    Fox(int strength, int initiative, int x, int y, World* world);

    void draw() const override {
        attron(COLOR_PAIR('R'));
        mvaddch(y, x, '$');
        attroff(COLOR_PAIR('R'));
    }

    void action() override {}
    void collision(Organism* other) override {}

    ~Fox();
};

/*########## Turtle ##########*/

class Turtle : public Animal {
public:
    Turtle(int strength, int initiative, int x, int y, World* world);

    void draw() const override {
        attron(COLOR_PAIR('G'));
        mvaddch(y, x, 'Q');
        attroff(COLOR_PAIR('G'));
    }

    void action() override {}
    void collision(Organism* other) override {}

    ~Turtle();
};

/*########## Antelope ##########*/

class Antelope : public Animal {
public:
    Antelope(int strength, int initiative, int x, int y, World* world);

    void draw() const override {
        attron(COLOR_PAIR('Y'));
        mvaddch(y, x, 'V');
        attroff(COLOR_PAIR('Y'));
    }

    void action() override {}
    void collision(Organism* other) override {}

    ~Antelope();
};