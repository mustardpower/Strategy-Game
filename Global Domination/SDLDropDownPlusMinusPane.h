#pragma once

#include "SDLCompositePane.h"

#include "SDLDropDownList.h"

namespace global_domination
{
	class SDLDropDownPlusMinusPane : public SDLCompositePane
	{
	public:
		SDLDropDownPlusMinusPane(SDL_Window* parent, SDL_Rect client_area);
		std::string getText() const;
		void initialize();
		void setItems(std::vector<std::string> items);
		void setText(std::string text);
		void respondToAction(Sint32 action);
	private:
		std::shared_ptr<SDLDropDownList> dropdown_list_;
	};
}