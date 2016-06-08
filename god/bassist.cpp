#include "headers/bassist.hpp"
using namespace game;

Bassist::Bassist(std::string name_) : Musician(name_, "bassist") {
	fightMoves = {"Intolerable Bassline", "Funky Bassline", "Plectrum Strike"};
	actorBattleAction["intolerablebassline"] = [this] (Monster * target) -> void { std::cout << "intolerableBassline" << std::endl; };
	actorBattleAction["funkybassline"] = [this] (Monster * target) -> void { std::cout << "funkyBassline" << std::endl; };
	actorBattleAction["plectrumstrike"] = [this] (Monster * target) -> void { std::cout << "plectrumStrike" << std::endl; };
}

Bassist::~Bassist() {

}

std::vector<std::string> Bassist::getFightMoves() const {
	return fightMoves;
}