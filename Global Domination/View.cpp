#include "View.h"

#include <memory>
#include <vector>

namespace global_domination
{
	View::View(std::shared_ptr<IReciever> reciever, SDL_Window* parent, SDL_Rect client_area)
	{
		reciever_ = reciever;
		client_area_ = client_area;
		parent_ = parent;
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

	std::shared_ptr<IReciever> View::getReciever()
	{
		return reciever_;
	}

	void View::setReciever(std::shared_ptr<IReciever> reciever)
	{
		reciever_ = reciever;
	}

	void View::handleClick(int mouse_x, int mouse_y)
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

	void View::render(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(renderer);

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
