#ifndef ORC_HPP
#define ORC_HPP
#include "monster.hpp"

namespace game {
	class Orc : public Monster {
	public:
		explicit Orc(std::string name_);
		virtual ~Orc();

	};
}

#endif
