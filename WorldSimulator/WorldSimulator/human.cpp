#include "animal.h"
#include "world.h"
#include "human.h"

Human::Human(int strength, int initiative, int x, int y, World* world) : Animal(5, 4, x, y, world) {
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
    return new Human(4, 4, x, y, world);
}

void Human::action() {
    vector<vector<int>> neigbouring_positions;

    if (x > (BOARD_START_X + 1)) {
        neigbouring_positions.push_back({ x - 1, y });
    }
    if (x < (BOARD_END_X - 1)) {
        neigbouring_positions.push_back({ x + 1, y });
    }
    if (y > (BOARD_START_Y + 1)) {
        neigbouring_positions.push_back({ x, y - 1 });
    }
    if (y < (BOARD_END_Y - 1)) {
        neigbouring_positions.push_back({ x, y + 1 });
    }

    //waiting mode for key press
    nodelay(stdscr, FALSE);
    int key = getch();
    nodelay(stdscr, TRUE);
    int newX = Human::getX();
    int newY = Human::getY();

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
    }

    Organism* met_organism = world->getOrganismAt(newX, newY);
    if (met_organism && met_organism != this) {
        Human::collision(met_organism);
    }

    mvaddch(y, x, ' ');
    setPosition(newX, newY);
    world->addLog("Player moved to (" + to_string(newX) + "," + to_string(newY) + ")");
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

Human::~Human() {}