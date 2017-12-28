#pragma once
#include "SDLControl.h"

namespace global_domination
{
	class SDLButtonGroup;

	class SDLCompositePane : public SDLControl
	{
	public:
		SDLCompositePane(SDL_Window* parent, SDL_Rect client_area_);
		~SDLCompositePane();
		void addButtonGroup(SDLButtonGroup* group);
		void addLabel(std::string text, int pos_x, int pos_y, ControlID id, int font_size = 30, bool use_secondary_color_scheme = false);
		virtual bool handleClick(int mouse_x, int mouse_y);
		virtual void initialize() = 0;
		virtual void render(SDL_Renderer* renderer);
		virtual void respondToAction(TYPES::ACTION_LIST action) = 0;
		void setLabelText(ControlID id, std::string text);

	private:
		std::vector<SDLButtonGroup*> button_groups_;
	};
}
