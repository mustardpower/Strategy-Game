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
		void addLabel(std::string text, int pos_x, int pos_y, ControlID id, int font_size = 30, bool use_secondary_color_scheme = false);
		std::shared_ptr<SDLControl> getControl(ControlID id);
		virtual SDL_Color getBackgroundColor();
		bool handleClick(int mouse_x, int mouse_y);
		virtual void initialize() = 0;
		void isVisible(bool isVisible);
		virtual void respondToAction(TYPES::ACTION_LIST action) = 0;
		void setLabelText(ControlID id, std::string text);
		void render(SDL_Renderer* renderer);

	protected:
		SDL_Rect client_area_;
		bool isVisible_;
		Game* the_game_;
		SDL_Window* parent_;
	private:
		std::vector<std::shared_ptr<SDLControl>> controls_;
	};
}