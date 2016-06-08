#include "headers/singer.hpp"

using namespace game;

Singer::Singer(std::string name_) : Musician(name_, "singer") {
	fightMoves = {"Microphone toss", "Wail", "Lullaby"};
	actorBattleAction["mictoss"] = [this] (Monster * target) -> void { std::cout << "micToss" << std::endl; };
	actorBattleAction["wail"] = [this] (Monster * target) -> void { std::cout << "wail" << std::endl; };
	actorBattleAction["lullaby"] = [this] (Monster * target) -> void { std::cout << "lullaby" << std::endl; };
}

Singer::~Singer() {

}

std::vector<std::string> Singer::getFightMoves() const {
	return fightMoves;
}