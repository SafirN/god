#include "headers/monster.hpp"

using namespace game;

Monster::Monster(std::string name_, std::string type_) : Actor(name_, type_) {


}

Monster::~Monster() {

}

int Monster::getLoyalty() const {
	return loyalty;
}

void Monster::setLoyalty(int loyalty) {
	this->loyalty = loyalty;
}