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
		
		//getters
		std::string getId() const;
		std::string getName() const;
		std::string getType() const;
		Environment * getLocation() const;
		Item * getItem(std::string target);
		std::unordered_map<std::string, Monster*> & getOpponents();
		int getHealth() const;
		int getAttack() const;
		int getDefense() const;
		std::string getStatus() const;
		bool isInCombat() const;
		void isDead(Monster * monster);
		double getCapacity() const;
		std::string getGreeting() const;
		
		//virtual std::vector<std::string> getFightMoves() const;
		
		//setters
		void setName(std::string name);
		void setLocation(Environment * location_);
		void addItem(std::string iName, Item * item);
		void removeItem(std::string identifier);
		void addOpponent(Monster * monster);
		void setHealth(int health_);
		void setAttack(int attack_);
		void setDefense(int defense_);
		void setStatus(std::string status_);
		void setCombat(bool combat);
		void setCapacity(double cap);
		void setGreeting(std::string);

		//actions
		bool hit() const;
		void miss(Actor * actor) const;
		virtual int determineDamage(int mean);
		void stillBattle();

		//prints
		void printItems();
		virtual void printDescription() const;
		void announceDeath() const;
		void announceDamage(int damage) const;
		void announceStatus() const;

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
		double capacity;
		bool inCombat;
		Environment * location;
		Environment * previousLocation;
		std::vector<std::string> fightMoves;
		std::unordered_map<std::string, Item*> currentItems;
		std::unordered_map<std::string, Monster*> currentOpponents;
	private:
	};
}

#endif