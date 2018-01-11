#include "SDLTabControl.h"
#include "SDL_TextRenderer.h"

namespace global_domination
{
	SDLTabControl::SDLTabControl(SDL_Window * parent, SDL_Rect client_area) : SDLControl(parent, client_area)
	{
		current_page_ = 0;
	}

	void SDLTabControl::addTab(std::string tab_name, std::shared_ptr<SDLControl> control)
	{
		tab_names_.push_back(tab_name);
		tabs_.push_back(control);
	}

	bool SDLTabControl::handleClick(int mouse_x, int mouse_y)
	{
		return tabs_.at(current_page_)->handleClick(mouse_x, mouse_y);
	}

	void SDLTabControl::render(SDL_Renderer * renderer)
	{
		for(std::vector<std::string>::iterator tab_name = tab_names_.begin(); tab_name != tab_names_.end(); tab_name++)
		{
			SDL_Rect tab_name_location{ 100 , 100, 0, 0 };
			text_renderer::renderText(parent_, *tab_name, tab_name_location, getTextColor(), getBackgroundColor(), font_size_);
		}

		tabs_.at(current_page_)->render(renderer);
	}
}

