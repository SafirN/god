#ifndef FOREST_HPP
#define FOREST_HPP
#include "outdoor.hpp"

namespace game {
	class Forest : public Outdoor {
	public:
		explicit Forest(std::string id_);
		virtual ~Forest();
	};
}

#endif