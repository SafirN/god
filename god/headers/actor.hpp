#ifndef ACTOR_HPP
#define ACTOR_HPP
#include <functional>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

namespace game {
	class Item;
	class Environment;
	class Actor {
	public:
		explicit Actor(std::string name_, std::string type_);
		virtual ~Actor();
		
		//getters
		std::string getId() const;
		int getHealth() const;
		int getAttack() const;
		int getDefense() const;
		std::string getStatus() const;
		std::string getType() const;
		std::string getName() const;
		Environment * getLocation() const;
		Item * getItem(std::string target);
		bool isInCombat() const;
		virtual std::string getAlignment() const;
		//virtual std::vector<std::string> getFightMoves() const;
		
		//setters
		void setName(std::string name);
		void setHealth(int health_);
		void setAttack(int attack_);
		void setDefense(int defense_);
		void setStatus(std::string status_);
		void setLocation(Environment * location_);
		void addItem(std::string iName, Item * item);
		void setCombat(bool combat);
		void setGreeting(std::string);
		void setAlignment(std::string alignment);
		//debug funct
		void printItems();
		virtual void printDescription() const;
		void greeting() const;
	protected:
		std::string id;
		std::string name;
		std::string type;
		std::string status;
		std::string greeting;
		std::string alignment;
		int health;
		int attack;
		int defense;
		bool inCombat;
		Environment * location;
		Environment * previousLocation;
		std::vector<std::string> fightMoves;
		std::unordered_map<std::string, Item*> currentItems;
	private:
	};
}

#endif