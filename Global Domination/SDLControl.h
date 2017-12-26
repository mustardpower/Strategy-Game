#pragma once
#include "SDL.h"

#include <memory>
#include <vector>

#include "Action.h"
#include "ControlResources.h"

namespace global_domination
{
	class SDLControl
	{
	public:
		SDLControl(SDL_Window* parent, SDL_Rect client_area_);
		void addChildControl(std::shared_ptr<SDLControl> control);
		bool containsPoint(int x, int y);
		std::shared_ptr<SDLControl> getChildControl(ControlID id);
		unsigned int getId();
		SDL_Color getBackgroundColor();
		SDL_Color getTextColor();
		virtual bool handleClick(int mouse_x, int mouse_y) = 0;
		virtual void render(SDL_Renderer* renderer) = 0;
		void setFontSize(int font_size);
		void setId(ControlID id);
		void setSelection(bool selected);
		void setVisibility(bool visibility);
		void useSecondaryColorScheme();
	protected:
		SDL_Rect client_area_;
		std::vector<std::shared_ptr<SDLControl>> children_;
		int font_size_;
		SDL_Window* parent_;
		bool is_selected_;
		bool is_visible_;
	private:
		ControlID id_;
		bool use_secondary_color_scheme_;
	};
}