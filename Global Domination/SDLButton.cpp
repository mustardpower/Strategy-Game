#include "SDLButton.h"

#include "SDL_ttf.h"

#include "ColorPreferences.h"
#include "SDLButtonGroup.h"
#include "SDL_TextRenderer.h"

namespace global_domination
{
	SDLButton::SDLButton(SDL_Window * parent, std::string button_text, std::shared_ptr<Action> action, SDL_Rect client_area) : SDLControl(parent, client_area)
	{
		action_ = action;
		button_text_ = button_text;
		button_group_ = nullptr;
	}

	void SDLButton::addToGroup(SDLButtonGroup* group)
	{
		button_group_ = group;
	}

	bool SDLButton::containsPoint(int x, int y)
	{
		if ((x >= client_area_.x) && (x <= (client_area_.x + client_area_.w)))
		{
			if ((y >= client_area_.y) && (y <= (client_area_.y + client_area_.h)))
			{
				return true;
			}
		}

		return false;
	}

	bool SDLButton::handleClick(int x, int y)
	{
		if (containsPoint(x, y))
		{
			setSelection(true);
			invokeAction();
			return true;
		}

		return false;
	}

	void SDLButton::invokeAction() const
	{
		action_->execute();
	}

	void SDLButton::render(SDL_Renderer* renderer)
	{
		if (is_visible_)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
			int index = 0;

			if (is_selected_)
			{
				SDL_RenderDrawRect(renderer, &client_area_);
			}

			TTF_Font* font = text_renderer::getFont(font_size_);
			if (!font) { return; }

			text_renderer::renderText(parent_, button_text_, client_area_, getTextColor(), getBackgroundColor(), font_size_);
		}
	}

	void SDLButton::setSelection(bool selected)
	{
		if (button_group_)
		{
			if (selected)
			{
				button_group_->setSelection(this);
			}
			is_selected_ = selected;
		}
	}

	void SDLButton::trigger()
	{
		setSelection(true);
		invokeAction();
	}
}