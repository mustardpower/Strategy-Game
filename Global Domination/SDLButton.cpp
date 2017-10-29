#include "SDLButton.h"

#include "SDL_ttf.h"

#include "SDL_TextRenderer.h"

namespace global_domination
{
	SDLButton::SDLButton(SDL_Window * parent, std::string button_text, int pos_x, int pos_y) : kPosX(pos_x), kPosY(pos_y)
	{
		button_text_ = button_text;
		parent_window_ = parent;
	}

	void SDLButton::render(SDL_Renderer* renderer)
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);

		int index = 0;
		SDL_Color text_color = { 0,255,0 };

		TTF_Font* font = text_renderer::getFont();
		if (!font) { return; }

		SDL_Rect text_location = { kPosX, kPosY, 200, 300 };
		text_renderer::renderText(parent_window_, button_text_, text_location, text_color);

		SDL_UpdateWindowSurface(parent_window_);
	}
}