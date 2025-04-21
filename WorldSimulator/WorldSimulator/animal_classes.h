#pragma once
#include "world.h"
#include "animal.h"
using namespace std;

/*########## Wolf ##########*/

class Wolf : public Animal {
public:
    Wolf(int strength, int initiative, int age, int x, int y, World* world);

    void draw() const override;
    string getTypeName() const override;
    Organism* copy_organism(int x, int y) const override;

    ~Wolf();
};

/*########## Sheep ##########*/

class Sheep : public Animal {
public:
    Sheep(int strength, int initiative, int age, int x, int y, World* world);
    
    void draw() const override;
    string getTypeName() const override;
    Organism* copy_organism(int x, int y) const override;

    ~Sheep();
};

/*########## Fox ##########*/

class Fox : public Animal {
public:
    Fox(int strength, int initiative, int age, int x, int y, World* world);

    void draw() const override;
    void action() override;
    string getTypeName() const override;
    Organism* copy_organism(int x, int y) const override;

    ~Fox();
};

/*########## Turtle ##########*/

class Turtle : public Animal {
public:
    Turtle(int strength, int initiative, int age, int x, int y, World* world);

    void draw() const override;
    void action() override;
    void collision(Organism* opponent) override;
    string getTypeName() const override;
    Organism* copy_organism(int x, int y) const override;

    ~Turtle();
};

/*########## Antelope ##########*/

class Antelope : public Animal {
public:
    Antelope(int strength, int initiative, int age, int x, int y, World* world);

    void draw() const override;
    void action() override;
    void collision(Organism* opponent) override;
    string getTypeName() const override;
    Organism* copy_organism(int x, int y) const override;

    ~Antelope();
};