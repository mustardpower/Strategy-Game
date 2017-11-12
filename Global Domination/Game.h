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

	class Game : public IReciever, public std::enable_shared_from_this<Game>
	{
	public:
		Game();
		~Game();
		SDL_Rect getClientArea() const;
		int getResult();
		void initialize();
		const int getWindowWidth();
		const int getWindowHeight();
		void render();
		void runGameLoop();
		void setAction(TYPES::ACTION_LIST action);
		void switchActiveView(std::shared_ptr<View> view);
		void update();

	private:

		const int kWindowWidth = 640;
		const int kWindowHeight = 480;

		std::shared_ptr<IReciever> viewReciever_;
		std::shared_ptr<View> active_view_;
		TYPES::ACTION_LIST current_action_;
		SDL_Renderer *renderer_;
		std::unique_ptr<Nation> selected_nation_;
		SDL_Window* window_;
	};

}