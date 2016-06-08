#include "headers/actor.hpp"
#include <sstream>
#include <time.h>
#include "headers/monster.hpp"
#include "headers/environment.hpp"

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

std::unordered_map<std::string, Monster*> & Actor::getOpponents() {
	return currentOpponents;
}

int Actor::getHealth() const {
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

void Actor::isDead(Monster * monster) {
	if(monster->getHealth() < 1) {
		monster->announceDeath();
		monster->getLocation()->removeMonster(monster->getName());
		currentOpponents.erase(monster->getName());
		delete monster;
	}
}

void Actor::stillBattle() {
	if(currentOpponents.size() == 0) {
		this->setCombat(false);
	}
}

double Actor::getCapacity() const {
	return capacity;
}

//setters
void Actor::setLocation(Environment * location) {
	previousLocation = this->location;
	this->location = location;
}

void Actor::addItem(std::string identifier, Item * item) {
	currentItems[identifier] = item;
}

void Actor::removeItem(std::string identifier) {
	currentItems.erase(identifier);
}

void Actor::addOpponent(Monster * monster) {
	currentOpponents[monster->getName()] = monster;
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
	this->inCombat = combat;
	if(combat) {
		std::cout << this->getName() << " is now in combat." << std::endl;
	}
}

bool Actor::hit() const {
	time_t t;
	srand((unsigned) time(&t));
	if((rand() % 2) == 0) {
		return false;
	}
	return true;
}

void Actor::announceDeath() const {
	if(this->getHealth() < 1) {
		std::cout << this->getName() << " the " << this->getType() << " died." << std::endl;
	}
}

void Actor::announceDamage(int damage) const {
	std::cout << "Dealt " << damage << " damage to " << this->getName() << " the " << this->getType() << "." << std::endl; 
}

void Actor::announceStatus() const {
	std::cout << this->getName() << " the " << this->getType() << " is " << this->getStatus() << "." << std::endl;
}

void Actor::miss(Actor * actor) const {
	std::cout << "Missed " << actor->getName() << " the " << actor->getType() << "." << std::endl;
}

void Actor::setCapacity(double capacity) {
	this->capacity = capacity;
}

void Actor::setGreeting(std::string greeting) {
	this->greeting = greeting;
}

//prints
void Actor::printDescription() const {
	std::cout << "You see " << name << " the " << type << ". It has " << health << " health.";
}

std::string Actor::getGreeting() const {
	return this->greeting;
}

int Actor::determineDamage(int mean) {
	time_t t;
	srand((unsigned) time(&t));

	return (rand() % mean + mean/2);
}

//r?
void Actor::printItems() {
	for(std::unordered_map<std::string, Item*>::iterator it = currentItems.begin(); it!=currentItems.end();++it) {
		std::cout << name << ": " << it->first << std::endl;
	}
}