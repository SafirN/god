#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>

namespace game {
	class Item {
	public:
		explicit Item(std::string id_);
		virtual ~Item();
		std::string getId() const;
		std::string getName() const;
		double getWeight() const;

		void setName(std::string name);
		void setWeight(double weight);
	protected:
		std::string id;
		std::string name;
		double weight;
	private:
	
	};
}

#endif