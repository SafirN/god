#ifndef LIZARD_HPP
#define LIZARD_HPP

#include "monster.hpp"

namespace game {
	class Lizard : public Monster {
	public:
		explicit Lizard(std::string name_);
		virtual ~Lizard();

	};
}

#endif