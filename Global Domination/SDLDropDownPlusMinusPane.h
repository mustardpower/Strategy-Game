#pragma once

#include "SDLCompositePane.h"

namespace global_domination
{
	class SDLDropDownPlusMinusPane : public SDLCompositePane
	{
	public:
		SDLDropDownPlusMinusPane(SDL_Window* parent, SDL_Rect client_area);
		void initialize();
		void setItems(std::vector<std::string> items);
		void respondToAction(Sint32 action);
	};
}