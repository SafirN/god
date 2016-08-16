#include "headers/game.hpp"

using namespace game;

Game::Game() : active(true) {
	std::string command;
	while(active) {
		std::cout << std::endl << "Game of Doom - all rights reserved etc. 2016." << std::endl << std::endl;
		std::cout << "Type play to play!" << std::endl << std::endl;
		command = nextCommand();
		if(command.compare("play") == 0) {
			launch();
		}
	}
}

Game::~Game() {

}

/*
 * Receives and trims commands to lower case strings.
 */
std::string Game::nextCommand() {
	std::string cmd;
	getline(std::cin, cmd);
	for(uint i = 0; i < cmd.length(); ++i) {
		cmd[i] = tolower(cmd[i]);
	}
	std::cout << std::endl;
	return cmd;
}

std::vector<std::string> Game::chopInput(std::string command) {
	std::string word = "";
	std::vector<std::string> commandWords = std::vector<std::string>();
	for(std::string::iterator it = command.begin(); it != command.end(); ++it) {
		if(*it == ' ' && !word.empty()) {
			commandWords.push_back(word);
			word.clear();
		} else {
			word += *it;
		}
	}
	commandWords.push_back(word);
	return commandWords;
}

/*
 *	
 */
void Game::launch() {
	intro();
	loadGameInfo();
	std::string command;
	while(active) {
		round = true;
		while(round) {
			command = nextCommand();
			std::vector<std::string> commandWords = chopInput(command);
			std::cout << "------------------------------------------------------------------------------" << std::endl << std::endl;
			if(player->isInCombat()) {
				if(commandWords.size() == 1) {
					round = player->battleAction(command);
				} else {
					round = player->battleAction(commandWords);
				}
			} else {
				if(commandWords.size() == 1) {
					round = player->action(command);
				} else {
					round = player->action(commandWords);
				}
			}
		}
		
		std::unordered_map<std::string, Monster*> opponents = player->getOpponents();
		
		for(std::unordered_map<std::string, Monster*>::iterator it = opponents.begin(); it != opponents.end(); ++it) {
			if(!(it->second->isAlive())) {
				announceMonsterDeath(it->second);
				it->second->getLocation()->removeMonster(it->first);
				player->removeOpponent(it->first);
				delete it->second;
			}
		}

		std::unordered_map<std::string, Monster*> monsters = player->getLocation()->getMonsters();

		for(std::unordered_map<std::string, Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
			if(it->second->isInCombat()) {
				it->second->battleAction();
			} else {
				it->second->action();
			}
		}

		announceBattleState();

		std::cout << "------------------------------------------------------------------------------" << std::endl << std::endl;

		if(!stillBattle()) {
			player->setCombat(false);
			player->getLocation()->printDescription();
		}
		
		if(player->isComplete()) {
			active = false;
			announceGameCompletion();
		} else if(!player->isAlive()) {
			active = false;
			announcePlayerDeath();
		}
	}
}

bool Game::stillBattle() {
	if(player->getOpponents().size() == 0) {
		return false;
	}
	return true;
}

void Game::announceBattleState() {
	std::unordered_map<std::string, Monster*> monsters = player->getOpponents();
	for(std::unordered_map<std::string, Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {
		std::cout << it->second->getName() << " the " << it->second->getType() << ": " << it->second->getHealth() << "/" << it->second->getMaxHealth() << " health." << std::endl; 
	}
	std::cout << player->getName() << " the " << player->getType() << ": " << player->getHealth() << "/" << player->getMaxHealth() << " health." << std::endl << std::endl;
}

/*
 *	Load game info from the default file.
 */
void Game::loadGameInfo() {
	std::unordered_map<std::string, Environment *> envRefMap = std::unordered_map<std::string, Environment*>();
	std::unordered_map<std::string, Monster*> actRefMap = std::unordered_map<std::string, Monster*>();
	std::unordered_map<std::string, std::vector<std::tuple<Environment *, std::string, std::string, std::string>>> neighborRefMap = std::unordered_map<std::string, std::vector<std::tuple<Environment *, std::string, std::string, std::string>>>();;
	std::string tmpid;
	std::string extracts [6]; //five strings to describe the Environment
	std::string object;
	char c;
	std::ifstream loadFile;
  	loadFile.open("gamestate/scratch.txt");
  	while(!loadFile.eof()) {
		std::getline(loadFile, object, ':');
		
		if(object.substr(0, 3).compare("ENV") == 0) {
			//Handle the information directly associated with the Environment
			std::getline(loadFile, extracts[0], ':');
			Environment * environment = decideEnv(object, extracts[0]);
			
			std::getline(loadFile, extracts[1]);
			environment->setDescription(extracts[1]);

			envMap[object] = environment;
			//Now handle the references associated with the Environment
			loadFile.get(c);
			if(c == ':') {
				while(true) {
					std::getline(loadFile, extracts[2], ':');
					if(extracts[2].substr(0, 3).compare("ENV") == 0) {
						std::getline(loadFile, extracts[3], ':');//direction
						std::getline(loadFile, extracts[4], ':');//accessibility
						std::getline(loadFile, extracts[5], ':');//visibility
						if(neighborRefMap.find(extracts[2]) == neighborRefMap.end()) {
							std::vector<std::tuple<Environment *, std::string, std::string, std::string>> vec = { std::make_tuple(environment, extracts[3], extracts[4], extracts[5]) };
							neighborRefMap[extracts[2]] = vec;
						} else {
							neighborRefMap[extracts[2]].push_back(std::make_tuple(environment, extracts[3], extracts[4], extracts[5]));
						}
					} else {
						envRefMap[extracts[2]] = environment;
					}
					loadFile.get(c);
					if(c == '\n') {
						break;
					} else {
						loadFile.putback(c);
					}
				}
			} else {
				loadFile.putback(c);
			}
		} else if(object.substr(0, 3).compare("ACT") == 0) {
			//Handle the information directly associated to the Actor
			std::getline(loadFile, extracts[0], ':');
			Monster * monster = decideAct(object, extracts[0]);
			std::getline(loadFile, extracts[1], ':');
			monster->setName(extracts[1]);
			std::getline(loadFile, extracts[2], ':');
			monster->setMaxHealth(std::stoi(extracts[2]));
			std::getline(loadFile, extracts[2], ':');
			monster->setHealth(std::stoi(extracts[2]));
			std::getline(loadFile, extracts[2], ':');
			monster->setAttack(std::stoi(extracts[2]));
			std::getline(loadFile, extracts[2], ':');
			monster->setDefense(std::stoi(extracts[2]));
			std::getline(loadFile, extracts[2], ':');
			monster->setLoyalty(std::stoi(extracts[2]));
			std::getline(loadFile, extracts[2], ':');
			monster->setCapacity(std::stoi(extracts[2]));
			std::getline(loadFile, extracts[2], ':');
			monster->setStatus(extracts[2]);
			std::getline(loadFile, extracts[2], ':');
			if(extracts[2] == "yes") {
				monster->setCombat(true);
			} else {
				monster->setCombat(false);
			}
			std::getline(loadFile, extracts[2]);
			monster->setGreeting(extracts[2]);
			
			monMap[object] = monster;
			//Now handle the references associated to the Actor
			loadFile.get(c);
			if(c == ':') {
				while(true) {
					std::getline(loadFile, extracts[2], ':');
					actRefMap[extracts[2]] = monster;
					loadFile.get(c);
					if(c == '\n') {
						break;
					} else {
						loadFile.putback(c);
					}
				}
			} else {
				loadFile.putback(c);
			}
		} else if(object.substr(0, 3).compare("ITE") == 0) {
			std::getline(loadFile, extracts[0], ':');
			Item * item = decideItem(object, extracts[0]);
			std::getline(loadFile, extracts[0], ':');
			item->setName(extracts[0]);
			std::getline(loadFile, extracts[0], ':');
			item->setWeight(std::stoi(extracts[0]));
			std::getline(loadFile, extracts[0]);
			item->setDescription(extracts[0]);
			itemMap[item->getName()] = item;
		} else if(object.compare("PLA") == 0) {
			std::getline(loadFile, extracts[0], ':');
			player->setMaxHealth(std::stoi(extracts[0]));
			std::getline(loadFile, extracts[0], ':');
			player->setHealth(std::stoi(extracts[0]));
			std::getline(loadFile, extracts[0], ':');
			player->setAttack(std::stoi(extracts[0]));
			std::getline(loadFile, extracts[0], ':');
			player->setDefense(std::stoi(extracts[0]));
			std::getline(loadFile, extracts[0], ':');
			player->setCapacity(std::stod(extracts[0]));
			std::getline(loadFile, extracts[0], ':');
			player->setStatus(extracts[0]);
			std::getline(loadFile, extracts[0]);
			if(extracts[0].compare("yes") == 0) {
				player->setCombat(true);
			} else {
				player->setCombat(false);
			}
		} else {
			std::cout << object << std::endl;
			std::cout.flush();
			std::cerr << "Invalid file format. Exiting program. Contact the moron who wrote the game in order to resolve this issue." << std::endl;
			std::terminate();
		}
  	}

  	//för load game
  	/*
  	std::unordered_map<std::string, Monster*> monsters = player->getLocation()->getMonsters();
  	for(std::unordered_map<std::string, Monster*>::iterator it = monsters.begin(); it != monsters.end(); ++it) {

  	}
  	*/

  	//Set the proper neighbors for every environment.
  	for(std::unordered_map<std::string, Environment*>::iterator it = envMap.begin(); it != envMap.end(); ++it) {
		if(neighborRefMap.find(it->first) != neighborRefMap.end()) {
			for(std::vector<std::tuple<Environment *, std::string, std::string, std::string>>::iterator it2 = neighborRefMap[it->first].begin(); it2 != neighborRefMap[it->first].end(); ++it2) {
				std::get<0>(*it2)->addEntrance(std::make_tuple(it->second, std::get<1>(*it2), std::get<2>(*it2), std::get<3>(*it2)));
			}
		}
  	}

  	//Set the proper room for every actor.
  	for(std::unordered_map<std::string, Monster*>::iterator it = monMap.begin(); it != monMap.end(); ++it) {
  		if(envRefMap.find(it->second->getId()) != envRefMap.end()) {
			it->second->setLocation(envRefMap[it->second->getId()]);
			envMap[envRefMap[it->second->getId()]->getId()]->addMonster(it->second);
		}
  	}

  	//Set the proper items for every actor and environment
  	for(std::unordered_map<std::string, Item*>::iterator it = itemMap.begin(); it != itemMap.end(); ++it) {
  		if(actRefMap.find(it->first) != actRefMap.end()) {
  			monMap[actRefMap[it->first]->getId()]->addItem(it->second->getId(), it->second);
  		}
  		if(envRefMap.find(it->first) != envRefMap.end()) {
  			std::string test = it->second->getName();
  			std::transform(test.begin(), test.end(), test.begin(), ::tolower);
  			envMap[envRefMap[it->first]->getId()]->addItem(it->second->getName(), it->second);
  		}
  	}
  	player->setLocation(envRefMap["PLA"]);
  	Environment * envi = player->getLocation();
  	envi->enter(player);
}

Monster * Game::decideAct(std::string name, std::string type) {
	if(type.compare("troll") == 0) {
		return new Troll(name);
	} else if(type.compare("orc") == 0) {
		return new Orc(name);
	} else if(type.compare("lizard") == 0) {
		return new Lizard(name);
	}
	return nullptr;
}

Environment * Game::decideEnv(std::string id, std::string type) {
	if(type.compare("room") == 0) {
		return new Room(id);
	} else if(type.compare("clearing") == 0) {
		return new Clearing(id);
	} else if(type.compare("forest") == 0) {
		return new Forest(id);
	}
	return nullptr;
}

Item * Game::decideItem(std::string id, std::string type) {
	if(type.compare("container") == 0) {
		return new Container(id, "container");
	} else if(type.compare("consumable") == 0) {
		return new Consumable(id, "consumable");
	} else if(type.compare("equippable") == 0) {
		return new Equippable(id, "equippable");
	} else if(type.compare("stationary") == 0) {
		return new Stationary(id, "stationary");
	}
	return nullptr;
}


/*
 *	Load game info from a specified file.
 */
void Game::loadGameInfo(std::string filename) {

}

/*
 *	Prints the available actions depending on the state of the game.
 */
void Game::printActions() const {
	if(!player->isInCombat()) {
		std::cout << "Actions:" << std::endl;
		std::cout << "'Observe' - Take a look around you." << std::endl;
		std::cout << "'Inspect' <actor/environment/item> - Inspect object." << std::endl;
		std::cout << "'Attack' <actor> - Initiate battle with something." << std::endl;
		std::cout << "'Talk' <actor> - Talk to something." << std::endl;
		std::cout << "'Take' <item> - Pick up something" << std::endl;
		std::cout << "'Use' <item> - Use something." << std::endl;
		std::cout << "Battle commands are listed when battle is initiated." << std::endl;
	} else {
		//std::vector<std::string> moves = player->getFightMoves();
		std::cout << "Actions:" << std::endl;
		/*for(uint i = 0; i < moves.size(); ++i) {
			std::cout << moves[i] << std::endl;
		}
		*/
	}
}

/*
 *	Presents the introduction of the game and handles the choice of the vocation.
 */
void Game::intro() {
	std::string vocation;
	slowPrint("You are a musician from Sweden.");
	//usleep(800000);
	slowPrint("You want nothing more than to kick your feet up in front of the America's Funniest Home Videos TV-show.");
	//usleep(800000);
	slowPrint("However, this fine Tuesday a horde of monsters has decided to lay claim on a forest, which happens to be the forest your house is located in.");
	//usleep(800000);
	slowPrint("What's worse, they threaten to dig up your fiber line, which may severelly affect tonight's cloth grinding in World of Warcraft.");
	//usleep(800000);
	slowPrint("You refuse to let this happen and pick up your instrument, ready to fight the forces of evil.");
	slowPrint("");
	//usleep(800000);
	slowPrint("What is your name?\n");
	std::string name;
	getline(std::cin, name);
	do {
		std::cout << std::endl;
		slowPrint("Are you a singer, guitarist, bassist or drummer?");
		std::cout << std::endl;
		vocation = nextCommand();
	} while(vocation.compare("singer") != 0 && vocation.compare("guitarist") != 0 && vocation.compare("bassist") != 0 && vocation.compare("drummer") != 0);
	if(vocation.compare("singer") == 0) {
		player = new Singer("PLA");
	} else if(vocation.compare("guitarist") == 0) {
		player = new Guitarist("PLA");
	} else if(vocation.compare("bassist") == 0) {
		player = new Bassist("PLA");
	} else if(vocation.compare("drummer") == 0) {
		player = new Drummer("PLA");
	}
	player->setName(name);
	std::cout << "You are " << name << " the " << vocation << "." << std::endl << std::endl;
	slowPrint("In order to print the list of actions, type: #Action");
	//usleep(3000000);
	std::cout << std::endl;
}

void Game::slowPrint(std::string input) const {
	for(uint i = 0; i < input.size(); ++i) {
		std::cout << input[i];
		std::cout.flush();
		//usleep(30000);
	}
	std::cout << std::endl;
}

void Game::announceMonsterDeath(Monster * monster) const {
	std::cout << monster->getName() << " the " << monster->getType() << " died." << std::endl << std::endl;
	std::cout << "------------------------------------------------------------------------------" << std::endl << std::endl;
}

void Game::announcePlayerDeath() const {
	std::cout << "You can't stand the heat of battle any longer, and all you ever wanted to do was reach the max-level on your World of warcraft character." << std::endl;
	std::cout << "As your body hits the soil you feel relaxed, realizing your life was not worth that much in the first place." << std::endl << std::endl;
	std::cout << "You bleed to death. It hardly matters though, your career as a musician weren't progressing very well anyway." << std::endl << std::endl;
}

void Game::announceGameCompletion() const {
	std::cout << "COMPLETED!" << std::endl;
}
