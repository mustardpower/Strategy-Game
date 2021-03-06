#include "SDLCompositePane.h"

#include "SDLButton.h"
#include "SDLButtonGroup.h"
#include "SDLStaticText.h"

namespace global_domination
{
	SDLCompositePane::SDLCompositePane(SDL_Window * parent, SDL_Rect client_area_) : SDLControl(parent, client_area_)
	{
	}

	SDLCompositePane::~SDLCompositePane()
	{
		for (std::vector<SDLButtonGroup*>::iterator group = button_groups_.begin(); group != button_groups_.end(); group++)
		{
			delete *group;
		}

		button_groups_.clear();
	}

	void SDLCompositePane::addButtonGroup(SDLButtonGroup* group)
	{
		button_groups_.push_back(group);
	}

	void SDLCompositePane::addButton(std::string text, TYPES::ACTION_LIST action, ControlID id, SDL_Rect client_area, int font_size)
	{
		std::shared_ptr<SDLButton> button = std::make_shared<SDLButton>(parent_, text, std::make_shared<Action>(action), client_area);
		button->setId(id);
		button->setFontSize(font_size);
		addChildControl(button);
	}
	void SDLCompositePane::addLabel(std::string text, int pos_x, int pos_y, ControlID id, int font_size, bool use_secondary_color_scheme)
	{
		std::shared_ptr<SDLStaticText> label = std::make_shared<SDLStaticText>(parent_, text, pos_x, pos_y);
		label->setId(id);
		label->setFontSize(font_size);

		if (use_secondary_color_scheme)
		{
			label->useSecondaryColorScheme();
		}
		addChildControl(label);
	}

	void SDLCompositePane::applyChanges()
	{
	}

	bool SDLCompositePane::handleClick(int mouse_x, int mouse_y)
	{
		if (is_visible_)
		{
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

	void SDLCompositePane::render(SDL_Renderer * renderer)
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

	void SDLCompositePane::respondToAction(Sint32 action)
	{
	}
	void SDLCompositePane::setLabelText(ControlID id, std::string text)
	{
		std::shared_ptr<SDLStaticText> label = std::dynamic_pointer_cast<SDLStaticText>(getChildControl(id));
		label->setText(text);
	}
}

