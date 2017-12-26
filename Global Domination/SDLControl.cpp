#include "SDLControl.h"

#include <assert.h>
#include<memory>

#include "ColorPreferences.h"

namespace global_domination
{
	SDLControl::SDLControl(SDL_Window * parent, SDL_Rect client_area)
	{
		client_area_ = client_area;
		id_ = UNDEFINED_CONTROL_ID;
		is_selected_ = false;
		is_visible_ = true;
		parent_ = parent;
		use_secondary_color_scheme_ = false;
		font_size_ = 30;
	}

	void SDLControl::addChildControl(std::shared_ptr<SDLControl> control)
	{
		children_.push_back(control);
	}

	std::shared_ptr<SDLControl> SDLControl::getChildControl(ControlID id)
	{
		if (children_.size())
		{
			for (std::vector<std::shared_ptr<SDLControl>>::iterator control = children_.begin(); control != children_.end(); control++)
			{
				if ((*control)->getId() == id)
				{
					return *control;
				}
			}
		}

		throw std::exception("No control defined with the id:" + id);
	}

	unsigned int SDLControl::getId()
	{
		return id_;
	}

	SDL_Color SDLControl::getBackgroundColor()
	{
		if (use_secondary_color_scheme_)
		{
			return ColorPreferences::getSecondaryBackgroundColor();
		}
		return ColorPreferences::getPrimaryBackgroundColor();
	}

	SDL_Color SDLControl::getTextColor()
	{
		if (use_secondary_color_scheme_)
		{
			return ColorPreferences::getSecondaryTextColor();
		}
		return ColorPreferences::getPrimaryTextColor();
	}

	bool SDLControl::handleClick(int mouse_x, int mouse_y)
	{
		if (is_visible_)
		{
			for (std::vector<std::shared_ptr<SDLControl>>::iterator control = children_.begin(); control != children_.end(); control++)
			{
				(*control)->setSelection(false);
			}

			if (children_.size())
			{
				for (std::vector<std::shared_ptr<SDLControl>>::iterator control = children_.begin(); control != children_.end(); control++)
				{
					bool clickHandled = (*control)->handleClick(mouse_x, mouse_y);
					if (clickHandled) { return true; }
				}
			}
		}

		return false;
	}

	void SDLControl::render(SDL_Renderer * renderer)
	{
		if (is_visible_)
		{
			SDL_Color background_color = getBackgroundColor();
			SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, 0xFF);
			SDL_RenderFillRect(renderer, &client_area_);

			if (children_.size())
			{
				for (std::vector<std::shared_ptr<SDLControl>>::iterator control = children_.begin(); control != children_.end(); control++)
				{
					(*control)->render(renderer);
				}
			}
		}
	}

	void SDLControl::respondToAction(TYPES::ACTION_LIST action)
	{
	}

	void SDLControl::setFontSize(int font_size)
	{
		font_size_ = font_size;
	}

	void SDLControl::setId(ControlID id)
	{
		assert(id_ == UNDEFINED_CONTROL_ID);
		id_ = id;
	}

	void SDLControl::setSelection(bool selected)
	{
		is_selected_ = selected;
	}

	void SDLControl::setVisibility(bool visibility)
	{
		is_visible_ = visibility;
	}

	void SDLControl::useSecondaryColorScheme()
	{
		use_secondary_color_scheme_ = true;
	}
}

