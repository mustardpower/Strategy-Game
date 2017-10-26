#pragma once

#include <array>
#include <memory>
#include <string>

#include "SDL.h"

#include "MenuItem.h"
#include "Nation.h"
#include "SDLMenu.h"

namespace global_domination {

	class Game : public IReciever
	{
	private:
		TYPES::ACTION_LIST currentAction;
		SDL_Renderer *renderer;
		SDL_Window* window;
		static const int WINDOW_HEIGHT;
		static const int WINDOW_WIDTH;
		std::unique_ptr<SDLMenu<int>> aMenu;
		std::unique_ptr<SDLMenu<Nation>> nationSelectionMenu;
		std::vector<Nation> nations;
		std::unique_ptr<Nation> selectedNation;

	public:
		Game();
		~Game();
		SDL_Rect getClientArea() const;
		int getResult();
		void initialize();
		void initializeMainMenu();
		void initializeNationSelectionMenu();
		static const int getWindowWidth();
		static const int getWindowHeight();
		void handleGameEvent(SDL_Event anEvent);
		void handleMenuEvent(SDL_Event anEvent);
		void render();
		void renderGame();
		void runGameLoop();
		void setAction(TYPES::ACTION_LIST action);
		void update();
	};

}