#ifndef GUITARIST_HPP
#define GUITARIST_HPP
#include "musician.hpp"

namespace game {
	class Guitarist : public Musician {
	public:
		explicit Guitarist(std::string name_);
		virtual ~Guitarist();

	protected:
	private:
	};
}

#endif
