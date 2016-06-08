#include "headers/actor.hpp"
#include <sstream>

using namespace game;

Actor::Actor(std::string name_, std::string type_) : id(name_), type(type_) {
	currentItems = std::unordered_map<std::string, Item*>();
}

Actor::~Actor() {

}

//getters
std::string Actor::getId() const {
	return id;
}

std::string Actor::getName() const {
	return name;
}

std::string Actor::getType() const {
	return type;
}

Environment * Actor::getLocation() const {
	return location;
}

Item * Actor::getItem(std::string target) {
	std::unordered_map<std::string, Item*>::iterator it = currentItems.find(target);
	if(it != currentItems.end()) {
		return it->second;
	}
	return nullptr;
}

int Actor::health() const {
	return health;
}

int Actor::getAttack() const {
	return attack;
}

int Actor::getDefense() const {
	return defense;
}

std::string Actor::getStatus() const {
	return status;
}

bool Actor::isInCombat() const {
	return inCombat;
}

//setters
void Actor::setLocation(Environment * location) {
	previousLocation = this->location;
	this->location = location;
}

void Actor::addItem(std::string iName, Item * item) {
	currentItems[iName] = item;
}

void Actor::setName(std::string name) {
	this->name = name;
}

void Actor::setHealth(int health) {
	this->health = health;
}

void Actor::setAttack(int attack) {
	this->attack = attack;
}

void Actor::setDefense(int defense) {
	this->defense = defense;
}

void Actor::setStatus(std::string status) {
	this->status = status;
}

void Actor::setCombat(bool combat) {
	inCombat = combat;
}

void Actor::setGreeting(std::string greeting) {
	this->greeting = greeting;
}

//prints
void Actor::printDescription() const {
	std::cout << "You see " << name << " the " << type << ". It has " << health << " health.";
}

//r?
void Actor::printItems() {
	for(std::unordered_map<std::string, Item*>::iterator it = currentItems.begin(); it!=currentItems.end();++it) {
		std::cout << name << ": " << it->first << std::endl;
	}
}