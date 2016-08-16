#ifndef SINGER_HPP
#define SINGER_HPP
#include "musician.hpp"

namespace game {
	class Singer : public Musician {
	public:
		explicit Singer(std::string name_);
		virtual ~Singer();

	protected:
	private:
	};	
}

#endif
