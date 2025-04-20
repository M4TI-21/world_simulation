#include "animal.h"
#include "world.h"
#include "human.h"

Human::Human(int strength, int initiative, int age, int x, int y, World* world) : Animal(5, 4, 0, x, y, world) {
	World::addLog("A human came to the world.");
}	

void Human::draw() const {
    attron(COLOR_PAIR('M'));
    mvaddch(y, x, '@');
    attroff(COLOR_PAIR('M'));
}

string Human::getTypeName() const {
    return "Human";
}

Organism* Human::copy_organism(int x, int y) const {
    return new Human(4, 4, 0, x, y, world);
}

void Human::action() {
    vector<vector<int>> neigbouring_positions = findNeighbouringPos(x, y);

    //waiting mode for key press
    nodelay(stdscr, FALSE);
    int key = getch();
    nodelay(stdscr, TRUE);

    int newX = x;
    int newY = y;

    //activate special ability - purification
    if (key == 'a') {
        if (abilityActive == 0 && abilityInactive == 0) {
            abilityActive = 5;
            abilityInactive = 5;
            world->addLog("Human special ability has been activated");
            specialAbility(neigbouring_positions);
            world->drawWorld();
        }
        nodelay(stdscr, FALSE);
        key = getch();
        nodelay(stdscr, TRUE);
    }
   
    //human movement
    switch (key) {
    case KEY_UP:
        newY--;
        break;
    case KEY_DOWN:
        newY++;
        break;
    case KEY_LEFT:
        newX--;
        break;
    case KEY_RIGHT:
        newX++;
        break;
    default:
        break;
    }

    specialAbility(findNeighbouringPos(newX, newY));

    Organism* met_organism = world->getOrganismAt(newX, newY);

    mvaddch(y, x, ' ');
    setPosition(newX, newY);
    world->addLog("Player moved to (" + to_string(newX) + "," + to_string(newY) + ")");

    if (abilityActive == 0) {
        if (met_organism && met_organism != this) {
            Human::collision(met_organism);
        }
    }

    if (abilityActive > 0) {
        abilityActive--;
    }
    else if (abilityInactive > 0) {
        abilityInactive--;
    }
}

void Human::collision(Organism* opponent) {

    bool isOppAnimal = dynamic_cast<Animal*>(opponent);
    if (isOppAnimal) {
        int human_strength = Human::getStrength();
        int opponent_strength = opponent->getStrength();

        if (human_strength > opponent_strength) {
            world->removeOrganism(opponent);
            world->addLog("Human defeated " + opponent->getTypeName());
        }
        else if (human_strength < opponent_strength) {
            world->removeOrganism(this);
            world->addLog(opponent->getTypeName() + " defeated Human.");
        }
        else {
            int success = rand() % 1;
            if (success == 0) {
                world->removeOrganism(opponent);
                world->addLog("Human defeated " + opponent->getTypeName());
            }
            else {
                world->removeOrganism(this);
                world->addLog(opponent->getTypeName() + " defeated Human.");
            }
        }
    }
    else {
        opponent->collision(this);
    }
}

void Human::specialAbility(vector<vector<int>> positions) {

    bool isAbilityActive = abilityActive > 0;
    if (isAbilityActive) {
        for (vector<int> position : positions) {
            int newX = position[0];
            int newY = position[1];

            Organism* target = world->getOrganismAt(newX, newY);
            bool isAnimal = dynamic_cast<Animal*>(target);

            if (target && target != this) {
                world->removeOrganism(target);
                if (isAnimal) {
                    world->addLog(target->getTypeName() + " was killed by Human.");
                }
                else {
                    world->addLog(target->getTypeName() + " was destroyed by Human.");
                }
            }
        }
        world->drawWorld();
    }
}

string Human::abilityStatus() const {
    if (abilityActive > 0) {
        return "Ability active for " + to_string(abilityActive) + " more rounds.";
    }
    else if (abilityInactive > 0) {
        return "Ability active in " + to_string(abilityInactive) + " rounds.";
    }
    else {
        return "Press 'a' to use special ability.";
    }
}


Human::~Human() {}