#include "Game.h"

int main(int argc, char* argv[])
{
	global_domination::Game global_domination_game;
	global_domination_game.initialize();
	global_domination_game.runGameLoop();
	return 0;
}