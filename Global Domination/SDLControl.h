#pragma once
#include "SDL.h"

#include "ControlResources.h"

namespace global_domination
{
	class SDLControl
	{
	public:
		SDLControl(SDL_Window* parent, SDL_Color background_color = { 0,0,0,0xFF });
		unsigned int getId();
		virtual bool handleClick(int mouse_x, int mouse_y) = 0;
		virtual void render(SDL_Renderer* renderer) = 0;
		void setFontSize(int font_size);
		void setId(ControlID id);
	protected:
		SDL_Color background_color_;
		int font_size_;
		SDL_Window* parent_;
	private:
		ControlID id_;
	};
}