#include "SDLButton.h"

#include "SDL_ttf.h"

#include "ColorPreferences.h"
#include "SDL_TextRenderer.h"

namespace global_domination
{
	SDLButton::SDLButton(SDL_Window * parent, std::string button_text, std::shared_ptr<Action> action, int pos_x, int pos_y, int width, int height) : SDLControl(parent),
		kButtonWidth(width), kButtonHeight(height), kPosX(pos_x), kPosY(pos_y)
	{
		action_ = action;
		button_text_ = button_text;
	}

	bool SDLButton::containsPoint(int x, int y)
	{
		if ((x >= kPosX) && (x <= (kPosX + kButtonWidth)))
		{
			if ((y >= kPosY) && (y <= (kPosY + kButtonHeight)))
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
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);

		int index = 0;

		TTF_Font* font = text_renderer::getFont(font_size_);
		if (!font) { return; }

		SDL_Rect text_location = { kPosX, kPosY, kButtonWidth, kButtonHeight };
		text_renderer::renderText(parent_, button_text_, text_location, getTextColor(), getBackgroundColor(), 30);
	}
}