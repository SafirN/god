#include "headers/bassist.hpp"
#include "headers/environment.hpp"
#include "headers/monster.hpp"

using namespace game;

//
Bassist::Bassist(std::string name_) : Musician(name_, "bassist") {
	fightMoves = {"IntolerableBassline", "FunkyBassline", "PlectrumStrike"};

	//paralyze enemies
	simpleBattleAction["intolerablebassline"] = [this] () -> void {
		std::unordered_map<std::string, Monster*> monsters = this->getOpponents();
		for(std::unordered_map<std::string, Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
			if(this->hit()) {
				it->second->setStatus("paralyzed");
				it->second->announceStatus();
			} else {
				miss(it->second);
			}
		}
	};

	//damage all enemies
	simpleBattleAction["funkybassline"] = [this] () -> void { 
		std::unordered_map<std::string, Monster*> monsters = this->getOpponents();
		for(std::unordered_map<std::string, Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
			if(this->hit()) {
				int damage = determineDamage(8 + this->getAttack());
				if(damage > it->second->getDefense()) {
					it->second->setHealth(it->second->getHealth() - (damage - it->second->getDefense()));
					it->second->announceDamage(damage - it->second->getDefense());
				} else {
					it->second->announceDamage(0);
				}
				this->isDead(it->second);
			} else {
				this->miss(it->second);
			}
		}
		this->stillBattle();
	};

	//single target attack
	actBattleAction["plectrumstrike"] = [this] (Monster * target) -> void { 
		if(this->hit()) {
			int damage = determineDamage(14 + this->getAttack());
			if(damage > target->getDefense()) {
				target->setHealth(target->getHealth() - (damage - target->getDefense()));
				target->announceDamage(damage - target->getDefense());
			} else {
				target->announceDamage(0);
			}
			this->isDead(target);
		} else {
			this->miss(target);
		}
		this->stillBattle();
	};
}

Bassist::~Bassist() {

}

std::vector<std::string> Bassist::getFightMoves() const {
	return fightMoves;
}