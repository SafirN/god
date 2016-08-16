#include "headers/equippable.hpp"

using namespace game;

Equippable::Equippable(std::string id_, std::string type_) : Item(id_, type_) {

}

Equippable::~Equippable() {
	
}

void Equippable::use(Actor * actor) {

}
