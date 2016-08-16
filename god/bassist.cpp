#include "headers/bassist.hpp"
#include "headers/environment.hpp"
#include "headers/monster.hpp"

using namespace game;

//
Bassist::Bassist(std::string name_) : Musician(name_, "bassist") {

	//paralyze enemies
	simpleBattleAction["intolerablebassline"] = [this] () -> bool {
		std::unordered_map<std::string, Monster*> monsters = this->getOpponents();
		for(std::unordered_map<std::string, Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
			if(this->hit()) {
				it->second->setStatus("paralyzed");
				it->second->announceStatus();
			} else {
				announceMiss(it->second);
			}
		}
		return true;
	};

	//damage all enemies
	simpleBattleAction["funkybassline"] = [this] () -> bool { 
		std::unordered_map<std::string, Monster*> monsters = this->getOpponents();
		for(std::unordered_map<std::string, Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
			if(this->hit()) {
				int damage = determineDamage(8 + this->getAttack());
				int calculatedDamage = damage - it->second->getDefense();
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

	//single target attack
	actBattleAction["plectrumstrike"] = [this] (Monster * target) -> bool { 
		if(this->hit()) {
			int damage = determineDamage(14 + this->getAttack());
			int calculatedDamage = damage - target->getDefense();
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
}

Bassist::~Bassist() {

}
