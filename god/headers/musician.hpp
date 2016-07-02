#ifndef MUSICIAN_HPP
#define MUSICIAN_HPP
#include "human.hpp"

namespace game {
	class Monster;
	class Musician : public Human {
	public:
		explicit Musician(std::string name_, std::string type_);
		virtual ~Musician();

		bool action(std::string move);
		bool action(std::vector<std::string> vec);
		bool battleAction(std::string move);
		bool battleAction(std::vector<std::string> vec);

		void printDescription() const;
		void printGreeting();
		void stillBattle();
		
	protected:
		std::unordered_map<std::string, std::function<bool()>> simpleAction;
		std::unordered_map<std::string, std::function<bool(Monster * target)>> actorAction;
		std::unordered_map<std::string, std::function<bool(std::string direction)>> environmentAction;
		std::unordered_map<std::string, std::function<bool(Item * target)>> itemAction;
		std::unordered_map<std::string, std::function<bool(Monster * target)>> actBattleAction;
		std::unordered_map<std::string, std::function<bool()>> simpleBattleAction;
	private:
	};	
}

#endif
