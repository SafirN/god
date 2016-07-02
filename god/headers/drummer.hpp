#ifndef DRUMMER_HPP
#define DRUMMER_HPP
#include "musician.hpp"

namespace game {
	class Drummer : public Musician {
	public:
		explicit Drummer(std::string name);
		virtual ~Drummer();

		virtual std::vector<std::string> getFightMoves() const;

	protected:
	private:
	};	
}

#endif
