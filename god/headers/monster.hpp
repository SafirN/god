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
	protected:
		int loyalty;
	};	
}

#endif
