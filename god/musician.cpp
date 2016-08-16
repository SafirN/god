#include "headers/musician.hpp"
#include "headers/troll.hpp"
#include "headers/room.hpp"
#include "headers/item.hpp"

using namespace game;

Musician::Musician(std::string name_, std::string type_) : Human(name_, type_) {
	//inspect current room
	simpleAction["inspect"] = [this] () -> bool {
		this->getLocation()->printDescription();
		return false;
	};

	//inspect actor
	actorAction["inspect"] = [this] (Actor * target) -> bool {
		target->printDescription();
		return false;
	};

	//talk to actor
	actorAction["talk"] = [this] (Actor * target) -> bool {
		std::cout << target->getGreeting() << std::endl;
		return true;
	};
	
	//attack an actor
	actorAction["attack"] = [this] (Monster * target) -> bool {
		std::cout << "You attack " << target->getName() << " the " << target->getType() << "!" << std::endl;
		this->setCombat(true);
		target->setCombat(true);
		this->addOpponent(target);
		this->location->checkParticipation(target);
		std::cout << std::endl;
		return false;
	};

	//go in a direction
	environmentAction["go"] = [this] (std::string direction) -> bool {
		Environment * env = location->getNeighbor(direction);
		if(this->getLocation()->containsMonsters()) {
			std::cout << "Hostile monsters are blocking the way! Kill them off first!" << std::endl << std::endl;
		} else if(location->isLocked(direction)) {
			std::cout << "The door is locked." << std::endl << std::endl;
		} else {
			std::cout << "You head " << direction << "." << std::endl << std::endl;
			getLocation()->leave();
			env->enter(this);
			this->setLocation(env);
		}
		return false;
	};

	//inspect item
	itemAction["inspect"] = [this] (Item * target) -> bool {
		std::cout << target->getDescription() << std::endl;
		return false;
	};

	//take item
	itemAction["take"] = [this] (Item * target) -> bool {
		if(target->getWeight() <= this->getCapacity()) {
			this->addItem(target->getId(), target);
			this->getLocation()->removeItem(target->getId());
			std::cout << "You picked up " << target->getName() << "." <<std::endl;
		} else {
			std::cout << target->getName() << " is too heavy." << std::endl;
		}
		return true;
	};
	
	//use item
	itemAction["use"] = [this] (Item * target) -> bool {
		if(target->getType().compare("usable") == 0) {
			target->use(this);	
			return true;
		}
		std::cout << "That item can not be used." << std::endl;
		return false;
	};
}

Musician::~Musician() {

}

bool Musician::action(std::vector<std::string> vec) {
	std::string move = vec[0];
	std::string conc = "";

	for(std::vector<std::string>::iterator it = vec.begin() + 1; it != vec.end(); ++it) {
		conc += *it;
		if((it + 1) != vec.end()) {
			conc += " ";
		}
	}

	Monster * monster = this->getLocation()->getMonster(conc);
	Environment * environment = location->getNeighbor(conc);
	Item * itemArea = location->getItem(conc);
	Item * itemActor = getItem(conc);
	bool roundPassed = false;
	if(monster != nullptr) {
 		try {
	   		roundPassed = actorAction[move](monster);
	 	} catch(std::bad_function_call& e) {
	   		std::cout << "The action you entered can not be performed on an actor or does not exist." << std::endl;
	   		return true;
	 	}
	} else if(environment != nullptr) {
	 	try {
	   		roundPassed = environmentAction[move](conc);
	 	} catch(std::bad_function_call& e) {
	   		std::cout << "The action you entered can not be performed on an environment or does not exist." << std::endl;
	   		return true;
	 	}
	} else if(itemArea != nullptr) {
		try{
	   		roundPassed = itemAction[move](itemArea);
	 	} catch(std::bad_function_call& e) {
	   		std::cout << "The action you entered can not be performed on an item or does not exist." << std::endl;
	   		return true;
		}
	} else if(itemActor != nullptr) {
		try{
	   		roundPassed = itemAction[move](itemActor);
	 	} catch(std::bad_function_call& e) {
	   		std::cout << "The action you entered can not be performed on an item or does not exist." << std::endl;
	   		return true;
		}
	} else {
		std::cout << "No such object is in your vicinity at this time." << std::endl;
		return true;
	}
	return !(roundPassed);
}

bool Musician::action(std::string move) {
	bool roundPassed = false;
	try {
		roundPassed = simpleAction[move]();
	} catch(std::bad_function_call& e) {
		std::cout << "That action does not exist." << std::endl;
		return true;
	}
	return !(roundPassed);
}

bool Musician::battleAction(std::vector<std::string> vec) {
	std::string move = vec[0];
	std::string conc = "";

	for(std::vector<std::string>::iterator it = vec.begin() + 1; it != vec.end(); ++it) {
		conc += *it;
		if((it + 1) != vec.end()) {
			conc += " ";
		}
	}
	Monster * monster = this->getLocation()->getMonster(conc);
	if(monster != nullptr) {
		try {
			actBattleAction[move](monster);	
		} catch(std::bad_function_call& e) {
			std::cout << "That action is not possible at this time, perhaps ever." << std::endl;
			return true;
		}
	} else {
		std::cout << "No such object is in your vicinity at this time." << std::endl;
		return true;
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
