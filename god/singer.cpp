#include "headers/singer.hpp"
#include "headers/monster.hpp"

using namespace game;

Singer::Singer(std::string name_) : Musician(name_, "singer") {

	actBattleAction["mictoss"] = [this] (Monster * target) -> bool {
		if(this->hit()) {
			int calculatedDamage = determineDamage(13 + this->getAttack()) - target->getDefense();
			if(calculatedDamage > 0) {
				target->setHealth(target->getHealth() - calculatedDamage);
				this->announceDamage(calculatedDamage, target);
			} else {
				this->announceDamage(0, target);
			}
		} else {
			this->announceMiss(target);
		}
		return true;
	};

	simpleBattleAction["wail"] = [this] () -> bool {
		std::unordered_map<std::string, Monster*> monsters = this->getOpponents();
		for(std::unordered_map<std::string, Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
			if(this->hit()) {
				int calculatedDamage = determineDamage(10 + this->getAttack()) - it->second->getDefense();
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
	simpleBattleAction["lullaby"] = [this] () -> bool {
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
}

Singer::~Singer() {

}
