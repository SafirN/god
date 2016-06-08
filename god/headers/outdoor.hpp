#ifndef OUTDOOR_HPP
#define OUTDOOR_HPP
#include "environment.hpp"

namespace game {
	class Outdoor : public Environment {
	public:
		explicit Outdoor(std::string id_);
		virtual ~Outdoor();
	};
}

#endif