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

	void SDLTabControl::drawTabHeaders(SDL_Renderer * renderer)
	{
		int tab_x_pos = client_area_.x;
		for (int idx = 0; idx < tab_names_.size(); idx++)
		{
			int w, h;
			w = h = 0;
			std::string tab_name = tab_names_[idx];
			TTF_SizeText(text_renderer::getFont(font_size_), tab_name.c_str(), &w, &h);

			const double percentage_margin = 0.2;
			SDL_Rect tab_name_location{ tab_x_pos, client_area_.y - h, w * (1.0 + 2 * percentage_margin), h };

			if (idx == current_page_)
			{
				SDL_SetRenderDrawColor(renderer, 170, 170, 170, 0);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
			}

			SDL_RenderFillRect(renderer, &tab_name_location);

			SDL_Rect tab_string_location(tab_name_location);
			tab_string_location.x = tab_name_location.x + w * percentage_margin;
			text_renderer::renderText(parent_, tab_name, tab_string_location, getTextColor(), getBackgroundColor(), font_size_);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderDrawRect(renderer, &tab_name_location);
			tab_x_pos += tab_name_location.w;
		}
	}

	bool SDLTabControl::handleClick(int mouse_x, int mouse_y)
	{
		for (int idx = 0; idx < tab_names_.size(); idx++)
		{
			if (containsPoint(tabHeaderLocation(idx), mouse_x, mouse_y))
			{
				current_page_ = idx;
				return true;
			}
		}

		return tabs_.at(current_page_)->handleClick(mouse_x, mouse_y);
	}

	void SDLTabControl::render(SDL_Renderer * renderer)
	{
		drawTabHeaders(renderer);
		tabs_.at(current_page_)->render(renderer);
	}
	SDL_Rect SDLTabControl::tabHeaderLocation(const int tab_number)
	{
		const double percentage_margin = 0.2;
		int w, h;
		w = h = 0;

		int tab_x_pos = client_area_.x;
		for (int i = 0; i < tab_number; i++)
		{
			std::string tab_name = tab_names_[i];
			TTF_SizeText(text_renderer::getFont(font_size_), tab_name.c_str(), &w, &h);
			tab_x_pos += w * (1.0 + 2 * percentage_margin);
		}

		TTF_SizeText(text_renderer::getFont(font_size_), tab_names_[tab_number].c_str(), &w, &h);
		return SDL_Rect{ tab_x_pos, client_area_.y - h, (int)(w * (1.0 + 2 * percentage_margin)), h };
	}
}

