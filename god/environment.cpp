#include "headers/environment.hpp"
#include "headers/item.hpp"
#include "headers/monster.hpp"
#include "headers/musician.hpp"
#include <time.h>
#include <algorithm>
#include <iostream>

using namespace game;

Environment::Environment(std::string id_) : id(id_), containsPlayer(false) {
	currentMonsters = std::unordered_map<std::string, Monster*>();
	currentNeighbors = std::unordered_map<std::string, std::tuple<Environment*, std::string, std::string>>();
	currentItems = std::unordered_map<std::string, Item*>();
}

Environment::~Environment() {
	
}

void Environment::printDescription() {
	std::cout << description << std::endl;
	std::cout << std::endl;
	std::cout << "There are exits to the:" << std::endl;
	for(std::unordered_map<std::string, std::tuple<Environment*, std::string, std::string>>::iterator it = currentNeighbors.begin(); it != currentNeighbors.end(); ++it) {
		if(std::get<2>(it->second) == "visible") {
			std::cout << it->first << std::endl;
		}
	}

	std::cout << std::endl;

	std::cout << "Items in this room: " << std::endl;
	for(std::unordered_map<std::string, Item*>::iterator it = currentItems.begin(); it != currentItems.end(); ++it) {
		std::cout << it->second->getName() << std::endl;
	}

	std::cout << std::endl;

	std::cout << "Monsters in this room: " << std::endl;
	for(std::unordered_map<std::string, Monster*>::iterator it = currentMonsters.begin(); it != currentMonsters.end(); ++it) {
		std::cout << it->second->getType() << ": " << it->second->getName() << std::endl;
	}
	std::cout << std::endl;

	std::unordered_map<std::string, Monster*> monsters = this->getMonsters();
	for(std::unordered_map<std::string, Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
		std::cout << it->second->getName() << " says: " << it->second->getGreeting() << std::endl;
	}
	std::cout << std::endl;
}

void Environment::getDirections() const {

}

Musician * Environment::getPlayer() {
	return player;
}

Monster * Environment::getMonster(std::string target) {
	std::unordered_map<std::string, Monster*>::iterator it = currentMonsters.find(target);
	if(it == currentMonsters.end()) {
		return nullptr;	
	}
	return currentMonsters[target];
}

Item * Environment::getItem(std::string target) {
	if(currentItems.find(target) != currentItems.end()) {
		return currentItems[target];
	}
	return nullptr;
}

Environment * Environment::getNeighbor(std::string target) {
	if(currentNeighbors.find(target) != currentNeighbors.end()) {
		return std::get<0>(currentNeighbors[target]);
	}
	return nullptr;
}

void Environment::setDescription(std::string description) {
	this->description = description;
}

void Environment::addEntrance(std::tuple<Environment*, std::string, std::string, std::string> info) {
	currentNeighbors[std::get<1>(info)] = std::make_tuple(std::get<0>(info), std::get<2>(info), std::get<3>(info));
}

void Environment::addMonster(Monster * monster) {
	std::string name = monster->getName();
	transform(name.begin(), name.end(), name.begin(), ::tolower);
	currentMonsters[name] = monster;
}

void Environment::removeMonster(std::string name) {
	transform(name.begin(), name.end(), name.begin(), ::tolower);
	currentMonsters.erase(name);
}

std::string Environment::getId() const {
	return id;
}

void Environment::enter(Musician * actor) {
	containsPlayer = true;
	player = actor;
	printDescription();
}

void Environment::leave() {
	containsPlayer = false;
	player = nullptr;
}

std::unordered_map<std::string, Monster*> & Environment::getMonsters() {
	return currentMonsters;
}

std::unordered_map<std::string, std::tuple<Environment*, std::string, std::string>> & Environment::getNeighbors() {
	return currentNeighbors;
}

std::unordered_map<std::string, Item*> & Environment::getItems() {
	return currentItems;
}

void Environment::removeItem(std::string identifier) {
	currentItems.erase(identifier);
}

void Environment::addItem(std::string identifier, Item * item) {
	currentItems[identifier] = item;
}

void Environment::printItems() {
	for(std::unordered_map<std::string, Item*>::iterator it = currentItems.begin(); it!=currentItems.end();++it) {
		std::cout << id << ": " << it->first << std::endl;
	}
}

bool Environment::containsMonsters() const {
	if(currentMonsters.size() == 0) {
		return false;
	}
	return true;
}

bool Environment::playerPresent() const {
	if(player != nullptr) {
		return true;
	} else {
		return false;
	}
}

bool Environment::isLocked(std::string direction) {
	if(std::get<1>(currentNeighbors[direction]) == "locked") {
		return true;
	}
	return false;
}

void Environment::printNeighbors() {
	std::cout << id << " has neighbors:" << std::endl;
	for(std::unordered_map<std::string, std::tuple<Environment*, std::string, std::string>>::iterator it = currentNeighbors.begin(); it != currentNeighbors.end(); ++it) {
		std::cout << std::get<0>(it->second)->getId() << " " << std::get<1>(it->second) << " " << std::get<2>(it->second) << it->first << std::endl;
	}
}

void Environment::checkParticipation(Monster * monster) {
	for(std::unordered_map<std::string, Monster*>::iterator it = currentMonsters.begin(); it != currentMonsters.end(); ++it) {
		if(rand() % 5 > it->second->getLoyalty() && it->second->getName() != monster->getName()) {
			std::cout << it->second->getName() << " the " << it->second->getType() << " joins the fray!" << std::endl;
			it->second->setCombat(true);
			player->addOpponent(it->second);
		}
	}
}
