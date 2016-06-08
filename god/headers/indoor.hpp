#ifndef INDOOR_HPP
#define INDOOR_HPP
#include "environment.hpp"

namespace game {
	class Indoor : public Environment {
	public:
		explicit Indoor(std::string id_);
		virtual ~Indoor();
	};	
}


#endif