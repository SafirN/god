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
	class Monster;
	class Actor {
	public:
		explicit Actor(std::string name_, std::string type_);
		virtual ~Actor();
		
		//getter definition
		std::string getId() const { return id; }
		std::string getName() const { return name; }
		std::string getType() const { return type; }
		Environment * getLocation() const { return location; }
		int getHealth() const { return this->health; }
		int getMaxHealth() const { return this->maxHealth; }
		int getAttack() const { return attack; }
		int getDefense() const { return defense; }
		std::string getStatus() const { return status; }
		bool isInCombat() const { return inCombat; }
		double getCapacity() const { return capacity; }
		std::string getGreeting() const { return this->greeting; }
		std::unordered_map<std::string, Monster*> & getOpponents() { return currentOpponents; }
		bool isComplete() { return complete; }

		//getter declarations
		Item * getItem(std::string target);
		bool isAlive();

		//setter definitions
		void setName(std::string name) { this->name = name; }
		void setHealth(int health);
		void setMaxHealth(int maxHealth) { this->maxHealth = maxHealth; }
		void setAttack(int attack) { this->attack = attack; }
		void setDefense(int defense) { this->defense = defense; }
		void setStatus(std::string status) { this->status = status; }
		void setCapacity(double capacity) { this->capacity = capacity; }
		void setGreeting(std::string greeting) { this->greeting = greeting; }
		void setLocation(Environment * location) { this->location = location; }
		void addItem(std::string identifier, Item * item) { this->currentItems[identifier] = item; }
		void removeItem(std::string identifier) { this->currentItems.erase(identifier); }
		void removeOpponent(std::string target) { currentOpponents.erase(target); }
		void setComplete() { this->complete = true; }

		//setter declarations
		void addOpponent(Monster * monster);
		void setCombat(bool combat);

		//prints
		void printItems();
		virtual void printDescription() const;
		void announceDeath();
		virtual void announceDamage(int damage, Monster * monster) const;
		virtual void announceHealing(int healing) const;
		virtual void announceStatus() const;
		
		//virtual std::vector<std::string> getFightMoves() const;

		//actions
		bool hit() const;
		void announceMiss(std::string move) const;
		void announceMiss(Actor * actor) const;
		virtual int determineDamage(int mean);
		virtual int determineHealing(int mean);

	protected:
		std::string id;
		std::string name;
		std::string type;
		std::string status;
		std::string greeting;
		int health;
		int maxHealth;
		int attack;
		int defense;
		double capacity;
		bool inCombat;
		bool complete;
		Environment * location;
		std::unordered_map<std::string, Item*> currentItems;
		std::unordered_map<std::string, Monster*> currentOpponents;
	private:
	};
}

#endif
