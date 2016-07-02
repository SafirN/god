#include "headers/drummer.hpp"
#include "headers/monster.hpp"

using namespace game;

Drummer::Drummer(std::string name_) : Musician(name_, "drummer") {
	fightMoves = {"DrumstickBoomerang", "MonotoneBeat", "DrumFill"};

	//deal massive damage to one enemy, chance to damage yourself
	actBattleAction["drumstickboomerang"] = [this] (Monster * target) -> bool {
		int damage = determineDamage(17 + this->getAttack());
		if(this->hit()) {
			if(damage > target->getDefense()) {
				target->setHealth(target->getHealth() - (damage - target->getDefense()));
				target->announceDamage(damage - target->getDefense());
			} else {
				target->announceDamage(0);
			}
		} else {
			this->miss(target);
		}

		if((rand() % 4) == 1) {
			if(damage > this->getDefense()) {
				this->setHealth(this->getHealth() - (damage - this->getDefense()));
				std::cout << "You caught the drumstick with your face. You dealt " << (damage - this->getDefense()) << " to yourself. " << std::endl;
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
				miss(it->second);
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
}

Drummer::~Drummer() {

}

std::vector<std::string> Drummer::getFightMoves() const {
	return fightMoves;
}
