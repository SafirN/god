FLAGS = -std=c++11 -Wall -g

game.out: main.cpp game.o actor.o human.o musician.o monster.o drummer.o singer.o bassist.o guitarist.o troll.o orc.o lizard.o item.o consumable.o container.o equippable.o environment.o outdoor.o indoor.o room.o clearing.o forest.o
		g++ $(FLAGS) main.cpp game.o actor.o human.o musician.o monster.o drummer.o singer.o bassist.o guitarist.o troll.o orc.o lizard.o item.o consumable.o container.o equippable.o environment.o outdoor.o indoor.o room.o clearing.o forest.o -o game.out

game.o: game.cpp
		g++ $(FLAGS) -c game.cpp

environment.o: environment.cpp
		g++ $(FLAGS) -c environment.cpp
		
outdoor.o: outdoor.cpp
		g++ $(FLAGS) -c outdoor.cpp

indoor.o: indoor.cpp
		g++ $(FLAGS) -c indoor.cpp

clearing.o: clearing.cpp
		g++ $(FLAGS) -c clearing.cpp

forest.o: forest.cpp
		g++ $(FLAGS) -c forest.cpp

room.o: room.cpp
		g++ $(FLAGS) -c room.cpp

actor.o: actor.cpp
		g++ $(FLAGS) -c actor.cpp

human.o: human.cpp
		g++ $(FLAGS) -c human.cpp

musician.o: musician.cpp
		g++ $(FLAGS) -c musician.cpp

drummer.o: drummer.cpp
		g++ $(FLAGS) -c drummer.cpp

singer.o: singer.cpp
		g++ $(FLAGS) -c singer.cpp

bassist.o: bassist.cpp
		g++ $(FLAGS) -c bassist.cpp

guitarist.o: guitarist.cpp
		g++ $(FLAGS) -c guitarist.cpp

monster.o: monster.cpp
		g++ $(FLAGS) -c monster.cpp

troll.o: troll.cpp
		g++ $(FLAGS) -c troll.cpp

orc.o: orc.cpp
		g++ $(FLAGS) -c orc.cpp

lizard.o: lizard.cpp
		g++ $(FLAGS) -c lizard.cpp

item.o: item.cpp
		g++ $(FLAGS) -c item.cpp

consumable.o: consumable.cpp
		g++ $(FLAGS) -c consumable.cpp

container.o: container.cpp
		g++ $(FLAGS) -c container.cpp

equippable.o: equippable.cpp
		g++ $(FLAGS) -c equippable.cpp

clean:
	rm -f *.o *.out