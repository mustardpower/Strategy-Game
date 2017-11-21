#pragma once
#include "SDL.h"

#include "ControlResources.h"

namespace global_domination
{
	class SDLControl
	{
	public:
		SDLControl(SDL_Window* parent);
		unsigned int getId();
		SDL_Color getBackgroundColor();
		SDL_Color getTextColor();
		virtual bool handleClick(int mouse_x, int mouse_y) = 0;
		virtual void render(SDL_Renderer* renderer) = 0;
		void setFontSize(int font_size);
		void setId(ControlID id);
		void useSecondaryColorScheme();
	protected:
		int font_size_;
		SDL_Window* parent_;
	private:
		ControlID id_;
		bool use_secondary_color_scheme_;
	};
}