#ifndef MONSTER_HPP
#define MONSTER_HPP
#include "actor.hpp"

namespace game {
	class Environment;
	class Monster : public Actor {
	public:
		explicit Monster(std::string name_, std::string type_);
		virtual ~Monster();

		void setLoyalty(int loyalty);
		int getLoyalty() const;

		virtual void action();
		virtual void battleAction();
		virtual void announceDamage(int damage, std::string move) const;
		virtual void announceHealing(int healing, std::string move) const;

	protected:
		int loyalty;

		std::vector<std::function<bool()>> actions;
		std::vector<std::function<bool()>> battleActions;
	};	
}

#endif
