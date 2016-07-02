#ifndef GUITARIST_HPP
#define GUITARIST_HPP
#include "musician.hpp"

namespace game {
	class Guitarist : public Musician {
	public:
		explicit Guitarist(std::string name_);
		virtual ~Guitarist();
		
		virtual std::vector<std::string> getFightMoves() const;

	protected:
	private:
	};
}

#endif
