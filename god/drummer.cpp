#include "headers/drummer.hpp"

using namespace game;

Drummer::Drummer(std::string name_) : Musician(name_, "drummer") {
	fightMoves = {"Drumstick boomerang", "Monotone beat", "Drumfill"};

	actorBattleAction["drumstickboomerang"] = [this] (Monster * target) -> void { std::cout << "drumStickBoomerang" << std::endl; };
	actorBattleAction["monotonebeat"] = [this] (Monster * target) -> void { std::cout << "monotoneBeat" << std::endl; };
	actorBattleAction["drumfill"] = [this] (Monster * target) -> void { std::cout << "drumFill" << std::endl; };

	
}

Drummer::~Drummer() {

}

std::vector<std::string> Drummer::getFightMoves() const {
	return fightMoves;
}