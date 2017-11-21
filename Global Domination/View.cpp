#include "View.h"

#include <memory>
#include <vector>

#include "ColorPreferences.h"

namespace global_domination
{
	View::View(Game* the_game, SDL_Window* parent, SDL_Rect client_area, bool isVisible)
	{
		the_game_ = the_game;
		client_area_ = client_area;
		parent_ = parent;
		isVisible_ = true;
	}

	View::~View()
	{
		parent_ = NULL;
	}

	void View::addControl(std::shared_ptr<SDLControl> control)
	{
		controls_.push_back(control);
	}

	std::shared_ptr<SDLControl> View::getControl(ControlID id)
	{
		if (controls_.size())
		{
			for (std::vector<std::shared_ptr<SDLControl>>::iterator control = controls_.begin(); control != controls_.end(); control++)
			{
				if((*control)->getId() == id)
				{
					return *control;
				}
			}
		}

		return nullptr;
	}

	SDL_Color View::getBackgroundColor()
	{
		return ColorPreferences::getPrimaryBackgroundColor();
	}

	void View::handleClick(int mouse_x, int mouse_y)
	{
		if (isVisible_)
		{
			if (controls_.size())
			{
				for (std::vector<std::shared_ptr<SDLControl>>::iterator control = controls_.begin(); control != controls_.end(); control++)
				{
					bool clickHandled = (*control)->handleClick(mouse_x, mouse_y);
					if (clickHandled) { return; }
				}
			}
		}
	}	

	void View::render(SDL_Renderer* renderer)
	{
		if (isVisible_)
		{
			SDL_Color background_color = getBackgroundColor();
			SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, 0xFF);
			SDL_RenderFillRect(renderer, &client_area_);

			if (controls_.size())
			{
				for (std::vector<std::shared_ptr<SDLControl>>::iterator control = controls_.begin(); control != controls_.end(); control++)
				{
					(*control)->render(renderer);
				}
			}
		}
	}

	void View::isVisible(bool isVisible)
	{
		isVisible_ = isVisible;
	}
}
