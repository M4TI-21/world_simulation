#pragma once
#include "world.h"
#include "plant.h"
using namespace std;

class Grass : public Plant {
public:
    Grass(int strength, int initiative, int x, int y, World* world);

    void draw() const override;
    string getTypeName() const override;
    Organism* copy_organism(int x, int y) const override;

    ~Grass();
};

class SowThistle : public Plant {
public:
    SowThistle(int strength, int initiative, int x, int y, World* world);

    void draw() const override;
    string getTypeName() const override;
    Organism* copy_organism(int x, int y) const override;

    ~SowThistle();
};

class Guarana : public Plant {
public:
    Guarana(int strength, int initiative, int x, int y, World* world);

    void draw() const override;
    void collision(Organism* animal) override;
    string getTypeName() const override;
    Organism* copy_organism(int x, int y) const override;

    ~Guarana();
};

class Belladonna : public Plant {
public:
    Belladonna(int strength, int initiative, int x, int y, World* world);

    void draw() const override;
    void collision(Organism* animal) override;
    string getTypeName() const override;
    Organism* copy_organism(int x, int y) const override;

    ~Belladonna();
};

class Hogweed : public Plant {
public:
    Hogweed(int strength, int initiative, int x, int y, World* world);

    void draw() const override;
    void action() override;
    void collision(Organism* animal) override;
    string getTypeName() const override;
    Organism* copy_organism(int x, int y) const override;

    ~Hogweed();
};