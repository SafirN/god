#include "headers/item.hpp"
#include "headers/item.hpp"

using namespace game;

Item::Item(std::string id_) : id(id_) {

}

Item::~Item() {

}

std::string Item::getId() const {
	return id;
}

std::string Item::getName() const {
	return name;
}

double Item::getWeight() const {
	return weight;
}

std::string Item::getDescription() const {
	return description;
}

void Item::setName(std::string name) {
	this->name = name;
}

void Item::setWeight(double weight) {
	this->weight = weight;
}

void Item::setDescription(std::string description) {
	this->description = description;
}
