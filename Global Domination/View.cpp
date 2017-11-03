#include "View.h"

#include <memory>
#include <vector>

namespace global_domination
{
	View::View(IReciever *reciever, SDL_Window* parent, SDL_Rect client_area)
	{
		reciever_ = reciever;
		client_area_ = client_area;
		parent_ = parent;
	}

	void View::addControl(std::shared_ptr<SDLControl> control)
	{
		controls_.push_back(control);
	}

	void View::handleClick(int mouse_x, int mouse_y)
	{
		if (controls_.size())
		{
			for (std::vector<std::shared_ptr<SDLControl>>::iterator control = controls_.begin(); control != controls_.end(); control++)
			{
				(*control)->handleClick(mouse_x, mouse_y);
			}
		}
	}
	

	void View::render(SDL_Renderer* renderer)
	{
		if (controls_.size())
		{
			for (std::vector<std::shared_ptr<SDLControl>>::iterator control = controls_.begin(); control != controls_.end(); control++)
			{
				(*control)->render(renderer);
			}
		}
		
		SDL_UpdateWindowSurface(parent_);
	}
}
