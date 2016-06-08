#include "headers/musician.hpp"
#include "headers/troll.hpp"
#include "headers/room.hpp"

using namespace game;

Musician::Musician(std::string name_, std::string type_) : Human(name_, type_) {
	//inspect current room
	simpleAction["inspect"] = [this] () -> void {
		location->printDescription();
	};

	//inspect actor
	actorAction["inspect"] = [this] (Actor * target) -> void {
		target->printDescription(); 
	};

	//talk to actor
	actorAction["talk"] = [this] (Actor * target) -> void {
		 	target->greeting();
	};
	
	actorAction["attack"] = [this] (Monster * target) -> void {
		this->setCombat(true);
		target->setCombat(true);
		this->location->checkParticipation(target);
	};

	environmentAction["go"] = [this] (std::string direction) -> void {
		Environment * env = location->getNeighbor(direction);
		if(env->containsMonsters()) {
			std::cout << "Hostile monsters are blocking the way! Kill them off first!" << std::endl;
		} else if(location->isLocked(direction)) {
			std::cout << "The door is locked." << std::endl;
		} else {
			getLocation()->leave();
			env->enter();
			this->setLocation(env);
		}
	};
	itemAction["inspect"] = [this] (Item * target) -> void {std::cout << "Inspect item stuff" << std::endl; };
	itemAction["take"] = [this] (Item * target) -> void {std::cout << "Take item" << std::endl; };
	itemAction["use"] = [this] (Item * target) -> void {std::cout << "Use item" << std::endl; };
}

Musician::~Musician() {

}

bool Musician::action(std::string move, std::string target) {
	Monster * monster = this->getLocation()->getMonster(target);
	Environment * environment = location->getNeighbor(target);
	Item * itemArea = location->getItem(target);
	Item * itemActor = getItem(target);
	if(monster != nullptr) {
 		try {
	   		actorAction[move](monster);
	 	} catch(std::bad_function_call& e) {
	   		std::cout << "The action you entered can not be performed on an actor or does not exist." << std::endl;
	   		return true;
	 	}
	} else if(environment != nullptr) {
	 	try {
	   		environmentAction[move](target);
	 	} catch(std::bad_function_call& e) {
	   		std::cout << "The action you entered can not be performed on an environment or does not exist." << std::endl;
	   		return true;
	 	}
	} else if(itemArea != nullptr) {
		try{
	   		itemAction[move](itemArea);
	 	} catch(std::bad_function_call& e) {
	   		std::cout << "The action you entered can not be performed on an item or does not exist." << std::endl;
	   		return true;
		}
	} else if(itemActor != nullptr) {
		try{
	   		itemAction[move](itemActor);
	 	} catch(std::bad_function_call& e) {
	   		std::cout << "The action you entered can not be performed on an item or does not exist." << std::endl;
	   		return true;
		}
	} else {
		std::cout << "No such object is in your vicinity at this time." << std::endl;
		return true;
	}
	return false;
}

bool Musician::action(std::string move) {
	try {
		simpleAction[move]();
	} catch(std::bad_function_call &e) {
		std::cout << "That action does not exist or is not available right now." << std::endl;
		return false;
	}
	return true;
}

void Musician::printDescription() const {
	std::cout << "You see yourself. You are a " << type << ". You have " << health << " health and are " << status << "." << std::endl;
}

void Musician::printGreeting() {
	std::cout << greeting << std::endl;
}