#pragma once
#include "SDLControl.h"

namespace global_domination
{
	class SDLTabControl : public SDLControl
	{
	public:
		SDLTabControl(SDL_Window* parent, SDL_Rect client_area);
		void addTab(std::string tab_name, std::shared_ptr<SDLControl> control);
		void drawTabHeaders(SDL_Renderer* renderer);
		bool handleClick(int mouse_x, int mouse_y);
		void render(SDL_Renderer* renderer);
	private:
		unsigned int current_page_;
		std::vector<std::string> tab_names_;
		std::vector<std::shared_ptr<SDLControl>> tabs_;
	};
}