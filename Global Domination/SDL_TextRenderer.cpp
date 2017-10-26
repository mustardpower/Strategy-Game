#include "SDL_TextRenderer.h"

TTF_Font * SDL_TextRenderer::font = NULL;

SDL_TextRenderer::~SDL_TextRenderer()
{
	TTF_CloseFont(font);
}

TTF_Font * SDL_TextRenderer::getFont()
{
	if (font) { return font; }

	const int fontSize = 30;
	font = TTF_OpenFont(".\\fonts\\ARIAL.TTF", fontSize);
	if (!font)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font loading failed with error : %s\n", SDL_GetError());
	}
}

void SDL_TextRenderer::renderText(SDL_Window* window, std::string text, SDL_Rect textLocation, SDL_Color foregroundColor)
{	
	SDL_Color backgroundColor = { 0, 0, 0 };
	SDL_Surface* textSurface = TTF_RenderText_Shaded(getFont(), text.c_str(), foregroundColor, backgroundColor);

		// Pass zero for width and height to draw the whole surface
	SDL_Surface* screen = SDL_GetWindowSurface(window);
	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);

	SDL_FreeSurface(textSurface);
}
