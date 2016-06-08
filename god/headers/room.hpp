#ifndef ROOM_HPP
#define ROOM_HPP
#include "indoor.hpp"

namespace game {
	class Room : public Indoor {
	public:
		explicit Room(std::string id_);
		virtual ~Room();
	};
}

#endif