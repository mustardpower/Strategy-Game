#include "Game.h"

int main(int argc, char* argv[])
{
	std::shared_ptr<global_domination::Game> global_domination_game = std::make_shared<global_domination::Game>();
	global_domination_game->initialize();
	global_domination_game->runGameLoop();
	return 0;
}