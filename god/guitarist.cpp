#include "headers/guitarist.hpp"

using namespace game;

Guitarist::Guitarist(std::string name_) : Musician(name_, "guitarist") {
	fightMoves = {"BackupVocals", "TerribleSolo", "TuneGuitar"};
	actBattleAction["backupvocals"] = [this] (Monster * target) -> void { std::cout << "backupVocals" << std::endl; };
	actBattleAction["terriblesolo"] = [this] (Monster * target) -> void { std::cout << "terribleSolo" << std::endl; };
	actBattleAction["tuneguitar"] = [this] (Monster * target) -> void { std::cout << "tuneGuitar" << std::endl; };
}

Guitarist::~Guitarist() {

}

std::vector<std::string> Guitarist::getFightMoves() const {
	return fightMoves;
}