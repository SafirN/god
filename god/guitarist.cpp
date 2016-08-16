#include "headers/guitarist.hpp"
#include "headers/monster.hpp"

using namespace game;

Guitarist::Guitarist(std::string name_) : Musician(name_, "guitarist") {

	simpleBattleAction["backupvocals"] = [this] () -> bool {
		std::unordered_map<std::string, Monster*> monsters = this->getOpponents();
		for(std::unordered_map<std::string, Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
			if(this->hit()) {
				int calculatedDamage = determineDamage(8 + this->getAttack()) - it->second->getDefense();
				if(calculatedDamage > 0) {
					it->second->setHealth(it->second->getHealth() - calculatedDamage);
					this->announceDamage(calculatedDamage, it->second);
				} else {
					this->announceDamage(0, it->second);
				}
			} else {
				this->announceMiss(it->second);
			}
		}
		return true;
	};

	//Single target attack, ignores defense
	actBattleAction["terriblesolo"] = [this] (Monster * target) -> bool {
		int calculatedDamage = determineDamage(17 + this->getAttack());
		if(this->hit()) {
			target->setHealth(target->getHealth() - calculatedDamage);
			this->announceDamage(calculatedDamage, target);
		} else {
			this->announceMiss(target);
		}
		return true;
	};

	//heal self
	simpleBattleAction["tuneguitar"] = [this] () -> bool {
		int healing = determineHealing(30);
		this->setHealth(this->getHealth() + healing);
		this->announceHealing(healing);
		return true;
	};
}

Guitarist::~Guitarist() {

}
