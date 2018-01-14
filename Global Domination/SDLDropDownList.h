#pragma once
#include "SDLControl.h"

namespace global_domination
{
	class SDLDropDownList : public SDLControl
	{
	public:
		SDLDropDownList(SDL_Window* parent, SDL_Rect client_area);
		void drawExpandedItems(SDL_Renderer* renderer);
		bool handleClick(int mouse_x, int mouse_y);
		void render(SDL_Renderer* renderer);
		void setItems(std::vector<std::string> items);
	private:
		bool is_expanded_;
		std::vector<std::string> items_;
		unsigned int selected_index_;
	};
}