#pragma once
#include <curses.h>
#include <string>
#include "world.h"
#include "animal.h"
using namespace std;

class Human : public Animal {
private:
    int abilityInactive = 0;
    int abilityActive = 0;
public:
    Human(int strength, int initiative, int age, int x, int y, World* world);

    void draw() const override;
    void action() override;
    void collision(Organism* other) override;
    string getTypeName() const override;
    Organism* copy_organism(int x, int y) const override;
    void specialAbility(vector<vector<int>> positions);
    string abilityStatus() const;

    ~Human();
};