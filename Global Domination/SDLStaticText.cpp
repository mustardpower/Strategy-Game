#include "SDLStaticText.h"
#include "SDL_TextRenderer.h"

namespace global_domination
{
	SDLStaticText::SDLStaticText(SDL_Window * parent, std::string text, int pos_x, int pos_y) : kPosX(pos_x), kPosY(pos_y)
	{
		parent_ = parent;
		text_ = text;
	}

	void SDLStaticText::handleClick(int x, int y)
	{
	}

	void SDLStaticText::render(SDL_Renderer * renderer)
	{
		SDL_Rect textLocationTitle = { kPosX, kPosY, 0, 0 };
		text_renderer::renderText(parent_, text_, textLocationTitle, { 0, 255, 0 });
	}
}
