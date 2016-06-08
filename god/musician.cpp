#include "headers/musician.hpp"
#include "headers/troll.hpp"
#include "headers/room.hpp"
#include "headers/item.hpp"

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
		std::cout << target->getGreeting() << std::endl;
	};
	
	actorAction["attack"] = [this] (Monster * target) -> void {
		std::cout << "You attack " << target->getName() << " the " << target->getType() << "!" << std::endl;
		this->setCombat(true);
		target->setCombat(true);
		this->addOpponent(target);
		this->location->checkParticipation(target);
	};

	//go in a direction
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
			std::cout << std::endl;
			std::unordered_map<std::string, Monster*> monsters = env->getMonsters();
			for(std::unordered_map<std::string, Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
				std::cout << it->second->getName() << " says: " << it->second->getGreeting() << std::endl;
			}
		}
	};

	//inspect item
	itemAction["inspect"] = [this] (Item * target) -> void {
		std::cout << target->getDescription() << std::endl;
	};

	//take item
	itemAction["take"] = [this] (Item * target) -> void {
		if(target->getWeight() <= this->getCapacity()) {
			this->addItem(target->getId(), target);
			this->getLocation()->removeItem(target->getId());
			std::cout << "You picked up " << target->getName() << "." <<std::endl;
		} else {
			std::cout << target->getName() << " is too heavy." << std::endl;
		}	
	};
	
	//use item
	itemAction["use"] = [this] (Item * target) -> void {
		target->use(this);
	};
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
	} catch(std::bad_function_call& e) {
		std::cout << "That action does not exist." << std::endl;
		return true;
	}
	return false;
}

bool Musician::battleAction(std::string move, std::string target) {
	Monster * monster = this->getLocation()->getMonster(target);
	if(monster != nullptr) {
		try {
			actBattleAction[move](monster);	
		} catch(std::bad_function_call& e) {
			std::cout << "That action does not exist." << std::endl;
			return true;
		}
	}
	return false;
}

bool Musician::battleAction(std::string move) {
	try{
		simpleBattleAction[move]();
	} catch(std::bad_function_call& e) {
		std::cout << "That action does not exist." << std::endl;
		return true;
	}
	return false;
}

void Musician::printDescription() const {
	std::cout << "You see yourself. You are a " << type << ". You have " << health << " health and are " << status << "." << std::endl;
}

void Musician::printGreeting() {
	std::cout << greeting << std::endl;
}