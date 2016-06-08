#ifndef CONTAINER_HPP
#define CONTAINER_HPP
#include "item.hpp"

namespace game {
	class Container : public Item {
	public:
		explicit Container(std::string id_);
		virtual ~Container();

		void use(Actor * actor);
	};
}

#endif