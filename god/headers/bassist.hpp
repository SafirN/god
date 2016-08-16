#ifndef BASSIST_HPP
#define BASSIST_HPP
#include "musician.hpp"

namespace game {
	class Bassist : public Musician {
	public:
		explicit Bassist(std::string name_);
		virtual ~Bassist();
	
	protected:
	private:
	};
}

#endif
