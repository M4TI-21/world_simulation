#pragma once
#include <string>
#include "defines.h"
#include "world.h"

class Animal : public Organism {
public:
    Animal(int strength, int initiative, int x, int y, World* world);

    void draw() const override;
    void action() override;
    void collision(Organism* other) override;
    virtual string getTypeName() const override = 0;

    ~Animal();
};