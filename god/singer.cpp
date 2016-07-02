#include "headers/singer.hpp"
#include "headers/monster.hpp"

using namespace game;

Singer::Singer(std::string name_) : Musician(name_, "singer") {
	fightMoves = {"MicrophoneToss", "Wail", "Lullaby"};

	actBattleAction["mictoss"] = [this] (Monster * target) -> bool {
		if(this->hit()) {
			int damage = determineDamage(13 + this->getAttack());
			if(damage > target->getDefense()) {
				target->setHealth(target->getHealth() - (damage - target->getDefense()));
				target->announceDamage(damage - target->getDefense());
			} else {
				target->announceDamage(0);
			}
		} else {
			this->miss(target);
		}
		return true;
	};

	simpleBattleAction["wail"] = [this] () -> bool {
		std::unordered_map<std::string, Monster*> monsters = this->getOpponents();
		for(std::unordered_map<std::string, Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
			if(this->hit()) {
				int damage = determineDamage(10 + this->getAttack());
				if(damage > it->second->getDefense()) {
					it->second->setHealth(it->second->getHealth() - (damage - it->second->getDefense()));
					it->second->announceDamage(damage - it->second->getDefense());
				} else {
					it->second->announceDamage(0);
				}	
			} else {
				miss(it->second);
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
				miss(it->second);
			}
		}
		return true;
	};
}

Singer::~Singer() {

}

std::vector<std::string> Singer::getFightMoves() const {
	return fightMoves;
}
