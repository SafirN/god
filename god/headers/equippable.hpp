#ifndef EQUIPPABLE_HPP
#define EQUIPPABLE_HPP
#include "item.hpp"

namespace game {
	class Equippable : public Item {
	public:
		explicit Equippable(std::string id_);
		virtual ~Equippable();

		void use(Actor * actor);
	};
}

#endif