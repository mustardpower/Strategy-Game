#include "SDLDropDownList.h"

#include "ColorPreferences.h"
#include "SDL_TextRenderer.h"

namespace global_domination
{
	SDLDropDownList::SDLDropDownList(SDL_Window * parent, SDL_Rect client_area) : SDLControl(parent, client_area)
	{
		selected_index_ = 0;
		is_expanded_ = false;
	}

	void SDLDropDownList::drawExpandedItems(SDL_Renderer* renderer)
	{
		for (int i = 0; i < items_.size(); i++)
		{
			SDL_Rect item_client_area{ client_area_.x, client_area_.y + ((i + 1) * client_area_.h), client_area_.w, client_area_.h };

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
			SDL_RenderFillRect(renderer, &item_client_area);

			SDL_Rect text_location = text_renderer::getCenteredTextLocation(item_client_area, items_.at(selected_index_), font_size_);
			text_renderer::renderText(parent_, items_.at(i), text_location, ColorPreferences::getPrimaryTextColor(), ColorPreferences::getPrimaryBackgroundColor(), font_size_);
		}

		SDL_Rect expanded_client_area{ client_area_.x, client_area_.y + client_area_.h, client_area_.w, client_area_.h * items_.size() };
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderDrawRect(renderer, &expanded_client_area);
	}

	bool SDLDropDownList::handleClick(int mouse_x, int mouse_y)
	{
		if (containsPoint(mouse_x, mouse_y))
		{
			is_expanded_ = !is_expanded_;
			return true;
		}

		if (is_expanded_)
		{
			for (int i = 0; i < items_.size(); i++)
			{
				SDL_Rect item_client_area{ client_area_.x, client_area_.y + ((i + 1) * client_area_.h), client_area_.w, client_area_.h };
				if (containsPoint(item_client_area, mouse_x, mouse_y))
				{
					selected_index_ = i;
					is_expanded_ = false;
					return true;
				}
			}
		}
		
		is_expanded_ = false;
		return false;
	}

	void SDLDropDownList::render(SDL_Renderer * renderer)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderFillRect(renderer, &client_area_);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderDrawRect(renderer, &client_area_);

		if (selected_index_ < items_.size())
		{
			SDL_Rect text_location = text_renderer::getCenteredTextLocation(client_area_, items_.at(selected_index_), font_size_);
			text_renderer::renderText(parent_, items_.at(selected_index_), text_location, ColorPreferences::getPrimaryTextColor(), ColorPreferences::getPrimaryBackgroundColor(), font_size_);

			if (is_expanded_)
			{
				drawExpandedItems(renderer);
			}
		}
	}

	void SDLDropDownList::setItems(std::vector<std::string> items)
	{
		items_ = items;
	}
}

