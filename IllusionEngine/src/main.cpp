#include "pcHeaders.h"
#include "Game.h"

int main()
{
	Illusion::Game game;
	game.run();

	std::cout << "Wait";
	std::cin.get();

	return 0;
}