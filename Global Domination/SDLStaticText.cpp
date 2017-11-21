#include "SDLStaticText.h"
#include "SDL_TextRenderer.h"

#include "ColorPreferences.h"

namespace global_domination
{
	SDLStaticText::SDLStaticText(SDL_Window * parent, std::string text, int pos_x, int pos_y) : SDLControl(parent),
		kPosX(pos_x), kPosY(pos_y)
	{
		text_ = text;
	}

	bool SDLStaticText::handleClick(int x, int y)
	{
		return false;
	}

	void SDLStaticText::render(SDL_Renderer * renderer)
	{
		SDL_Rect textLocationTitle = { kPosX, kPosY, 0, 0 };
		text_renderer::renderText(parent_, text_, textLocationTitle, getTextColor(), getBackgroundColor(), font_size_);
	}
	void SDLStaticText::setText(std::string text)
	{
		text_ = text;
	}
}
