#include "headers/orc.hpp"
#include "headers/environment.hpp"
#include "headers/musician.hpp"

using namespace game;

Orc::Orc(std::string name_) : Monster(name_, "orc") {
	std::function<bool()> ba1 = [this] () -> bool {
		Environment * loc = this->getLocation();
		Musician * pla = loc->getPlayer();
		std::string move = "Shield bash";
		if(this->hit()) {
			int damage = this->determineDamage(4 + this->getAttack());
			int def = pla->getDefense();
			int pure = damage - def;
			if(pure > 0) {
				pla->setHealth(pla->getHealth() - pure);
				announceDamage(pure, move);
			} else {
				announceDamage(0, move);
			}
		} else {
			this->announceMiss(move);
		}
		return false;
	};

	std::function<bool()> ba2 = [this] () -> bool {
		Environment * loc = this->getLocation();
		Musician * pla = loc->getPlayer();
		std::string move = "Overhead chop";
		if(this->hit()) {
			int damage = this->determineDamage(9 + this->getAttack());
			int def = pla->getDefense();
			int pure = damage - def;
			if(pure > 0) {
				pla->setHealth(pla->getHealth() - pure);
				announceDamage(pure, move);
			} else {
				announceDamage(0, move);
			}
		} else {
			this->announceMiss(move);
		}
		return false;
	};

	battleActions.push_back(ba1);
	battleActions.push_back(ba2);
}

Orc::~Orc() {

}
