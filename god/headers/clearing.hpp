#ifndef CLEARING_HPP
#define CLEARING_HPP
#include "outdoor.hpp"

namespace game {
	class Clearing : public Outdoor {
	public:
		explicit Clearing(std::string id_);
		virtual ~Clearing();
	};
}

#endif