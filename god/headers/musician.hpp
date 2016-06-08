#ifndef MUSICIAN_HPP
#define MUSICIAN_HPP
#include "human.hpp"

namespace game {
	class Monster;
	class Musician : public Human {
	public:
		explicit Musician(std::string name_, std::string type_);
		virtual ~Musician();

		bool action(std::string);
		bool action(std::string move, std::string target);

		void printDescription() const;
		void printGreeting();
		
	protected:
		std::unordered_map<std::string, std::function<void()>> simpleAction;
		std::unordered_map<std::string, std::function<void(Monster * target)>> actorAction;
		std::unordered_map<std::string, std::function<void(std::string direction)>> environmentAction;
		std::unordered_map<std::string, std::function<void(Item * target)>> itemAction;
		std::unordered_map<std::string, std::function<void(Monster * target)>> actorBattleAction;
		std::unordered_map<std::string, std::function<void()>> simpleBattleAction;
	private:
	};	
}

#endif