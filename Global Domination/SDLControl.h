#pragma once
#include "SDL.h"

#include "ControlResources.h"

namespace global_domination
{
	class SDLControl
	{
	public:
		SDLControl();
		unsigned int getId();
		virtual bool handleClick(int mouse_x, int mouse_y) = 0;
		virtual void render(SDL_Renderer* renderer) = 0;
		void setFontSize(int font_size);
		void setId(ControlID id);
	protected:
		SDL_Color background_color_;
		int font_size_;
	private:
		ControlID id_;
	};
}