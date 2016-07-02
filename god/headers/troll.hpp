#ifndef TROLL_HPP
#define TROLL_HPP
#include "monster.hpp"

namespace game {
	class Troll : public Monster {
	public:
		explicit Troll(std::string name_);
		virtual ~Troll();
	};	
}

#endif
