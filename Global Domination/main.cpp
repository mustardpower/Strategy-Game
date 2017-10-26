#include "Game.h"

int main(int argc, char* argv[])
{
	global_domination::Game globalDominationGame;
	globalDominationGame.initialize();
	globalDominationGame.runGameLoop();
	return 0;
}