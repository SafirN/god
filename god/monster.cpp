#include "headers/monster.hpp"
#include "headers/environment.hpp"
#include "headers/musician.hpp"

using namespace game;

Monster::Monster(std::string name_, std::string type_) : Actor(name_, type_) {
	actions = std::vector<std::function<bool()>>();
	battleActions = std::vector<std::function<bool()>>();
	
	std::function<bool()> a1 = [this] () -> bool {
		Environment * loc = this->getLocation();	
		std::cout << this->getName() << " the " << this->getType() << " attacks you!" << std::endl;
		this->getLocation()->getPlayer()->setCombat(true);
		this->getLocation()->getPlayer()->addOpponent(this);
		this->setCombat(true);
		loc->checkParticipation(this);
		return false;
	};

	std::function<bool()> a2 = [this] () -> bool {
		std::cout << this->getGreeting() << std::endl;
		return false;
	};

	actions.push_back(a1);
	actions.push_back(a2);
}

Monster::~Monster() {

}

int Monster::getLoyalty() const {
	return loyalty;
}

void Monster::setLoyalty(int loyalty) {
	this->loyalty = loyalty;
}

void Monster::action() {
	int move = rand() % (actions.size());
	//attack
	//talk
}

void Monster::battleAction() {
	int move = rand() % (battleActions.size());
	battleActions[move]();
}

void Monster::announceDamage(int damage, std::string move) const {
	std::cout << this->getName() << " the " << this->getType() << " performed a " << move << " and dealt " << damage << " damage to you." << std::endl << std::endl;
}

void Monster::announceHealing(int healing, std::string move) const {
	std::cout << this->getName() << " the " << this->getType() << " performed a " << move <<" and healed itself for " << healing << " health." << std::endl << std::endl;
}