#include "Game.h"

int main(int argc, char* argv[])
{
	Game globalDominationGame;
	globalDominationGame.initialize();
	globalDominationGame.runGameLoop();
	return 0;
}