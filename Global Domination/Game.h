#pragma once

#include <array>
#include <memory>
#include <string>

#include "SDL.h"

#include "MenuItem.h"
#include "Nation.h"
#include "SDLButton.h"
#include "SDLMenu.h"
#include "View.h"

namespace global_domination {

	class Game : public IReciever
	{
	public:
		Game();
		~Game();
		SDL_Rect getClientArea() const;
		int getResult();
		void initialize();
		void initializeMainMenu();
		void initializeNationSelectionMenu();
		const int getWindowWidth();
		const int getWindowHeight();
		void handleInboxEvent(SDL_Event an_event);
		void handleNationSelectionEvent(SDL_Event an_event);
		void handleMenuEvent(SDL_Event an_event);
		void render();
		void renderInbox();
		void runGameLoop();
		void setAction(TYPES::ACTION_LIST action);
		void update();

	private:

		const int kWindowWidth = 640;
		const int kWindowHeight = 480;

		std::unique_ptr<View> active_view_;
		TYPES::ACTION_LIST current_action_;
		std::unique_ptr<SDLMenu<int>> main_menu_;
		std::unique_ptr<SDLMenu<Nation>> nation_selection_menu_;
		std::vector<Nation> nations_;
		SDL_Renderer *renderer_;
		std::unique_ptr<Nation> selected_nation_;
		SDL_Window* window_;
	};

}