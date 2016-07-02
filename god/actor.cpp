#include "headers/actor.hpp"
#include <sstream>
#include <time.h>
#include "headers/monster.hpp"
#include "headers/environment.hpp"

using namespace game;

Actor::Actor(std::string id_, std::string type_) : id(id_), type(type_) {
	currentItems = std::unordered_map<std::string, Item*>();
}

Actor::~Actor() {

}

//getters

Item * Actor::getItem(std::string target) {
	std::unordered_map<std::string, Item*>::iterator it = currentItems.find(target);
	if(it != currentItems.end()) {
		return it->second;
	}
	return nullptr;
}

bool Actor::isAlive() {
	if(this->getHealth() > 0) {
		return true;
	}
	return false;
}

void Actor::addOpponent(Monster * monster) {
	currentOpponents[monster->getName()] = monster;
}

void Actor::setCombat(bool combat) {
	this->inCombat = combat;
	if(combat) {
		std::cout << this->getName() << " is now in combat." << std::endl;
	}
}

bool Actor::hit() const {
	if((rand() % 4) == 0) {
		return false;
	}
	return true;
}

void Actor::announceDamage(int damage) const {
	std::cout << "Dealt " << damage << " damage to " << this->getName() << " the " << this->getType() << "." << std::endl << std::endl; 
}

void Actor::announceHealing(int healing) const {
	std::cout << "Healed yourself for " << healing << " health." << std::endl;
}

void Actor::announceStatus() const {
	std::cout << this->getName() << " the " << this->getType() << " is " << this->getStatus() << "." << std::endl;
}

void Actor::miss(Actor * actor) const {
	std::cout << "Missed " << actor->getName() << " the " << actor->getType() << "." << std::endl;
}

//prints
void Actor::printDescription() const {
	std::cout << "You see " << name << " the " << type << ". It has " << health << " health." << std::endl;
}

int Actor::determineDamage(int mean) {
	time_t t;
	srand((unsigned) time(&t));

	return (rand() % mean + mean/2);
}

int Actor::determineHealing(int mean) {
	time_t t;
	srand((unsigned) time(&t));

	return (rand() % mean + mean);
}

//r?
void Actor::printItems() {
	for(std::unordered_map<std::string, Item*>::iterator it = currentItems.begin(); it!=currentItems.end();++it) {
		std::cout << name << ": " << it->first << std::endl;
	}
}
