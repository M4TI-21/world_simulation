#pragma once
#include "world.h"
#include "plant.h"

class Grass : public Plant {
public:
    Grass(int strength, int initiative, int x, int y, World* world);

    void draw() const override {
        attron(COLOR_PAIR('G'));
        mvaddch(y, x, 'W');
        attroff(COLOR_PAIR('G'));
    }

    void action() override {}
    void collision(Organism* other) override {}

    ~Grass();
};

class SowThistle : public Plant {
public:
    SowThistle(int strength, int initiative, int x, int y, World* world);

    void draw() const override {
        attron(COLOR_PAIR('Y'));
        mvaddch(y, x, '*');
        attroff(COLOR_PAIR('Y'));
    }

    void action() override {}
    void collision(Organism* other) override {}

    ~SowThistle();
};

class Guarana : public Plant {
public:
    Guarana(int strength, int initiative, int x, int y, World* world);

    void draw() const override {
        attron(COLOR_PAIR('R'));
        mvaddch(y, x, 'o');
        attroff(COLOR_PAIR('R'));
    }

    void action() override {}
    void collision(Organism* other) override {}

    ~Guarana();
};

class Belladonna : public Plant {
public:
    Belladonna(int strength, int initiative, int x, int y, World* world);

    void draw() const override {
        attron(COLOR_PAIR('C'));
        mvaddch(y, x, 'b');
        attroff(COLOR_PAIR('C'));
    }

    void action() override {}
    void collision(Organism* other) override {}

    ~Belladonna();
};

class Hogweed : public Plant {
public:
    Hogweed(int strength, int initiative, int x, int y, World* world);

    void draw() const override {
        attron(COLOR_PAIR('W'));
        mvaddch(y, x, 'Y');
        attroff(COLOR_PAIR('W'));
    }

    void action() override {}
    void collision(Organism* other) override {}

    ~Hogweed();
};