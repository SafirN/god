#ifndef HUMAN_HPP
#define HUMAN_HPP
#include "actor.hpp"

namespace game {
	class Human : public Actor {
	public:
		explicit Human(std::string name_, std::string type_);
		virtual ~Human();
	protected:
	private:
	};
}

#endif