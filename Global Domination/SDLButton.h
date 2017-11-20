#pragma once
#include <memory>
#include <string>

#include "SDL.h"

#include "Action.h"
#include "SDLControl.h"

namespace global_domination
{
	class SDLButton : public SDLControl
	{
	public:
		SDLButton(SDL_Window* parent, std::string button_text, std::shared_ptr<Action> action, int pos_x, int pos_y, int width, int height, SDL_Color background_color);
		bool containsPoint(int x, int y);
		bool handleClick(int x, int y);
		void invokeAction() const;
		void render(SDL_Renderer* renderer);
	private:
		const int kButtonWidth;
		const int kButtonHeight;
		const int kPosX;
		const int kPosY;
		std::shared_ptr<Action> action_;
		std::string button_text_;
	};
}