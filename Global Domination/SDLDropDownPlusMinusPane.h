#pragma once

#include "SDLCompositePane.h"

#include "SDLDropDownList.h"

namespace global_domination
{
	class SDLDropDownPlusMinusPane : public SDLCompositePane
	{
	public:
		SDLDropDownPlusMinusPane(SDL_Window* parent, SDL_Rect client_area);
		void initialize();
		void setItems(std::vector<std::string> items);
		void respondToAction(Sint32 action);
	private:
		std::shared_ptr<SDLDropDownList> dropdown_list_;
	};
}