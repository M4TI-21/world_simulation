#include "animal.h"
#include "world.h"
#include "human.h"
#include "animal_classes.h"

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
    return new Human(5, 4, 0, x, y, world);
}

void Human::action() {
    vector<vector<int>> neigbouring_positions = findNeighbouringPos(x, y);
    savePrevPos();

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

    if (abilityActive == 0) {
        if (met_organism && met_organism != this) {
            Human::collision(met_organism);
        }
    }
    else if (abilityActive > 0 && met_organism != nullptr) {
        world->removeOrganism(met_organism);
        world->addLog("Human defeated " + met_organism->getTypeName());
    }

    if (abilityActive > 0) {
        abilityActive--;
    }
    else if (abilityInactive > 0) {
        abilityInactive--;
    }
}

//regular fight when opponent is met
void Human::collision(Organism* opponent) {
    bool isOppAnimal = dynamic_cast<Animal*>(opponent);
    if (isOppAnimal) {

        if (opponent->getTypeName() == "Turtle") {
            Turtle* turtle = dynamic_cast<Turtle*>(opponent);
            turtle->collision(this);
            return;
        }

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
            world->removeOrganism(opponent);
            world->addLog("Human defeated " + opponent->getTypeName());
        }
    }
    else {
        opponent->collision(this);
    }
}

//destroy organisms on neighbouring fields - purification ability
void Human::specialAbility(vector<vector<int>> positions) {

    bool isAbilityActive = abilityActive > 0;
    if (isAbilityActive) {
        for (vector<int> position : positions) {
            int newX = position[0];
            int newY = position[1];

            Organism* target = world->getOrganismAt(newX, newY);

            if (target && target != this) {
                string targetType = target->getTypeName();
                bool isAnimal = dynamic_cast<Animal*>(target);

                world->removeOrganism(target);
                if (isAnimal) {
                    world->addLog(targetType + " was killed by Human.");
                }
                else {
                    world->addLog(targetType + " was destroyed by Human.");
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

bool Human::isAbilityActive() const {
    return abilityActive > 0;
}


Human::~Human() {}