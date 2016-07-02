#include "headers/guitarist.hpp"
#include "headers/monster.hpp"

using namespace game;

Guitarist::Guitarist(std::string name_) : Musician(name_, "guitarist") {
	fightMoves = {"BackupVocals", "TerribleSolo", "TuneGuitar"};

	simpleBattleAction["backupvocals"] = [this] () -> bool {
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
			} else {
				this->miss(it->second);
			}
		}
		return true;
	};

	//Single target attack, ignores defense
	actBattleAction["terriblesolo"] = [this] (Monster * target) -> bool {
		int damage = determineDamage(17 + this->getAttack());
		if(this->hit()) {
			target->setHealth(target->getHealth() - damage);
			target->announceDamage(damage - target->getDefense());
		} else {
			this->miss(target);
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

std::vector<std::string> Guitarist::getFightMoves() const {
	return fightMoves;
}
