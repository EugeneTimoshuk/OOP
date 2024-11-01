all: main.o GameBoard.o ShipManager.o Ship.o BoardRenderer.o
	g++ -std=c++11 main.o GameBoard.o ShipManager.o Ship.o BoardRenderer.o -o game

main.o: main.cpp GameBoard.h ShipManager.h Ship.h BoardRenderer.h
	g++ -std=c++11 -c main.cpp

GameBoard.o: GameBoard.cpp GameBoard.h ShipManager.h Ship.h
	g++ -std=c++11 -c GameBoard.cpp

ShipManager.o: ShipManager.cpp ShipManager.h Ship.h
	g++ -std=c++11 -c ShipManager.cpp

Ship.o: Ship.cpp Ship.h
	g++ -std=c++11 -c Ship.cpp

BoardRenderer.o: BoardRenderer.cpp BoardRenderer.h GameBoard.h
	g++ -std=c++11 -c BoardRenderer.cpp

clean:
	rm -f *.o
	rm -f game
