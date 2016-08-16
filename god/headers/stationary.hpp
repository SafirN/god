#ifndef STATIONARY_HPP
#define STATIONARY_HPP
#include "item.hpp"

namespace game {
	class Stationary : public Item {
	public:
		explicit Stationary(std::string id_, std::string type);
		virtual ~Stationary();

		void use(Actor * actor);
	};
}

#endif