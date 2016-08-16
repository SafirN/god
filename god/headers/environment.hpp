#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include <string>
#include <unordered_map>

namespace game {
	class Item;
	class Actor;
	class Monster;
	class Musician;
	class Environment {
	public:
		explicit Environment(std::string id);
		virtual ~Environment();
		
		//getters
		void getDirections() const;
		std::string getId() const;
		Musician * getPlayer();
		Monster * getMonster(std::string target);
		Environment * getNeighbor(std::string target);
		Item * getItem(std::string target);
		bool containsMonsters() const;
		bool playerPresent() const;
		bool isLocked(std::string direction);
		
		//setters
		void setDescription(std::string description);
		void addEntrance(std::tuple<Environment*, std::string, std::string, std::string> info);
		void addMonster(Monster * monster);
		void removeMonster(std::string name);
		void enter(Musician * actor);
		void leave();
		void removeItem(std::string identifier);
		void addItem(std::string identifier, Item * item);
		
		//events
		void checkParticipation(Monster * monster);

		//prints
		void printItems();
		void printDescription();
		void printNeighbors();

		std::unordered_map<std::string, Monster*> & getMonsters();
		std::unordered_map<std::string, std::tuple<Environment*, std::string, std::string>> & getNeighbors();
		std::unordered_map<std::string, Item*> & getItems();
	protected:
		std::string id;
		std::string description;
		Musician * player;
		bool containsPlayer;

		std::unordered_map<std::string, Monster*> currentMonsters;
		std::unordered_map<std::string, std::tuple<Environment*, std::string, std::string>> currentNeighbors;
		std::unordered_map<std::string, Item*> currentItems;
	private:
	};
}

#endif
