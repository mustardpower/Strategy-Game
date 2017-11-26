#include "View.h"

#include <memory>
#include <vector>

#include "ColorPreferences.h"
#include "SDLStaticText.h"

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

	void View::addLabel(std::string text, int pos_x, int pos_y, ControlID id, int font_size)
	{
		std::shared_ptr<SDLStaticText> title_label = std::make_shared<SDLStaticText>(parent_, text, pos_x, pos_y);
		title_label->setId(id);
		title_label->setFontSize(font_size);
		addControl(title_label);
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

		throw std::exception("No control defined with the id:" + id);
	}

	SDL_Color View::getBackgroundColor()
	{
		return ColorPreferences::getPrimaryBackgroundColor();
	}

	bool View::handleClick(int mouse_x, int mouse_y)
	{
		if (isVisible_)
		{
			if (controls_.size())
			{
				for (std::vector<std::shared_ptr<SDLControl>>::iterator control = controls_.begin(); control != controls_.end(); control++)
				{
					bool clickHandled = (*control)->handleClick(mouse_x, mouse_y);
					if (clickHandled) { return true; }
				}
			}
		}

		return false;
	}	

	void View::setLabelText(ControlID id, std::string text)
	{
		std::shared_ptr<SDLStaticText> population_label = std::dynamic_pointer_cast<SDLStaticText>(getControl(id));
		population_label->setText(text);
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
