#include "headers/drummer.hpp"
#include "headers/monster.hpp"

using namespace game;

Drummer::Drummer(std::string name_) : Musician(name_, "drummer") {

	//deal massive damage to one enemy, chance to damage yourself
	actBattleAction["drumstickboomerang"] = [this] (Monster * target) -> bool {
		int damage = determineDamage(17 + this->getAttack());
		int calculatedDamage = damage - target->getDefense();
		if(this->hit()) {
			if(calculatedDamage > 0) {
				target->setHealth(target->getHealth() - calculatedDamage);
				this->announceDamage(calculatedDamage, target);
			} else {
				this->announceDamage(0, target);
			}
		} else {
			this->announceMiss(target);
		}

		if((rand() % 4) == 1) {
			if(calculatedDamage > 0) {
				this->setHealth(this->getHealth() - calculatedDamage);
				std::cout << "You caught the drumstick with your face. You dealt " << calculatedDamage << " to yourself. " << std::endl;
			}	
		}
		return true;
	};

	//put enemies to sleep
	simpleBattleAction["monotonebeat"] = [this] () -> bool {
		std::unordered_map<std::string, Monster*> monsters = this->getOpponents();
		for(std::unordered_map<std::string, Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
			if(this->hit()) {
				it->second->setStatus("asleep");
				it->second->announceStatus();
			} else {
				this->announceMiss(it->second);
			}
		}
		return true;
	};

	//target all enemies
	simpleBattleAction["drumfill"] = [this] () -> bool {
		std::unordered_map<std::string, Monster*> monsters = this->getOpponents();
		for(std::unordered_map<std::string, Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
			if(this->hit()) {
				int damage = determineDamage(10 + this->getAttack());
				int calculatedDamage = damage - it->second->getDefense();
				if(calculatedDamage > 0) {
					it->second->setHealth(it->second->getHealth() - (damage - it->second->getDefense()));
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
}

Drummer::~Drummer() {

}
