#include "headers/troll.hpp"
#include "headers/environment.hpp"
#include "headers/musician.hpp"

using namespace game;

Troll::Troll(std::string name_) : Monster(name_, "troll") {
	std::function<bool()> ba1 = [this] () -> bool {
		Environment * loc = this->getLocation();
		Musician * pla = loc->getPlayer();
		if(this->hit()) {
			int damage = this->determineDamage(5 + this->getAttack());
			int def = pla->getDefense();
			int pure = damage - def;
			if(pure > 0) {
				pla->setHealth(pla->getHealth() - pure);
				announceDamage(pure, "Stab");
			} else {
				announceDamage(0, "Stab");
			}
		} else {
			this->announceMiss("Stab");
		}
		return false;
	};

	std::function<bool()> ba2 = [this] () -> bool {
		int healing = determineHealing(10);
		this->setHealth(this->getHealth() + healing);
		announceHealing(healing, "Wicked restoration");
		return false;
	};

	battleActions.push_back(ba1);
	battleActions.push_back(ba2);
}

Troll::~Troll() {

}
