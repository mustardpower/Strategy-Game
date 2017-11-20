#pragma once

#include <memory>
#include <vector>

#include "SDL.h"

#include "Action.h"
#include "ControlResources.h"
#include "SDLControl.h"

namespace global_domination
{
	class Game;

	class View
	{
	public:
		View(Game* the_game, SDL_Window* parent, SDL_Rect client_area, bool isVisible = true);
		virtual ~View();
		void addControl(std::shared_ptr<SDLControl> control);
		std::shared_ptr<SDLControl> getControl(ControlID id);
		void handleClick(int mouse_x, int mouse_y);
		virtual void initialize() = 0;
		virtual void respondToAction(TYPES::ACTION_LIST action) = 0;
		void render(SDL_Renderer* renderer);
		void setBackgroundColor(SDL_Color background_color);
		void isVisible(bool isVisible);

	protected:
		SDL_Color background_color_;
		SDL_Rect client_area_;
		bool isVisible_;
		Game* the_game_;
		SDL_Window* parent_;
	private:
		std::vector<std::shared_ptr<SDLControl>> controls_;
	};
}