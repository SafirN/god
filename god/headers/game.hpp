#ifndef GAME_HPP
#define GAME_HPP
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <exception>
#include <string>
#include "singer.hpp"
#include "drummer.hpp"
#include "bassist.hpp"
#include "guitarist.hpp"
#include "troll.hpp"
#include "orc.hpp"
#include "lizard.hpp"
#include "room.hpp"
#include "clearing.hpp"
#include "forest.hpp"
#include "consumable.hpp"
#include "container.hpp"
#include "equippable.hpp"

namespace game {
	class Actor;
	class Musician;
	class Environment;
	class Item;
	class Game {
	public:
		explicit Game();
		virtual ~Game();
	protected:

	private:
		Musician * player;
		bool active;
		bool round;
		void printActions() const;
		void intro();
		void launch();
		std::string nextCommand();
		void loadGameInfo(); //startup game load
		void loadGameInfo(std::string filename); //load saved game
		void action(std::string command);
		void battleAction(std::string command, Musician * musician);
		void slowPrint(std::string input) const;

		//loadfile members
		Monster * decideAct(std::string type, std::string id);
		Environment * decideEnv(std::string type, std::string);
		Item * decideItem(std::string type, std::string id);

		std::unordered_map<std::string, Monster*> monMap;
		std::unordered_map<std::string, Environment*> envMap;
		std::unordered_map<std::string, Item*> itemMap;
	};	
}



#endif