#include "headers/guitarist.hpp"

using namespace game;

Guitarist::Guitarist(std::string name_) : Musician(name_, "guitarist") {
	fightMoves = {"Backup Vocals", "Terrible Solo", "Tune Guitar"};
	actorBattleAction["backupvocals"] = [this] (Monster * target) -> void { std::cout << "backupVocals" << std::endl; };
	actorBattleAction["terriblesolo"] = [this] (Monster * target) -> void { std::cout << "terribleSolo" << std::endl; };
	actorBattleAction["tuneguitar"] = [this] (Monster * target) -> void { std::cout << "tuneGuitar" << std::endl; };
}

Guitarist::~Guitarist() {

}

std::vector<std::string> Guitarist::getFightMoves() const {
	return fightMoves;
}