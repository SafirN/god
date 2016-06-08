#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>

namespace game {
	class Actor;
	class Item {
	public:
		explicit Item(std::string id_);
		virtual ~Item();

		//getters
		std::string getId() const;
		std::string getName() const;
		double getWeight() const;
		std::string getDescription() const;

		//setters
		void setName(std::string name);
		void setWeight(double weight);
		void setDescription(std::string description);

		//actions
		virtual void use(Actor * actor) = 0;
	protected:

		//variables
		std::string id;
		std::string name;
		double weight;
		std::string description;
	private:
	
	};
}

#endif