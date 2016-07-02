#ifndef CONSUMABLE_HPP
#define CONSUMABLE_HPP
#include "item.hpp"

namespace game {
	class Consumable : public Item {
	public:
		explicit Consumable(std::string id_);
		virtual ~Consumable();

		void use(Actor * actor);
	protected:
	private:
	};
}

#endif
