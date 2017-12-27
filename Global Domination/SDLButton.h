#pragma once
#include <memory>
#include <string>

#include "SDL.h"

#include "Action.h"
#include "SDLControl.h"

namespace global_domination
{
	class SDLButtonGroup;
	class SDLButton : public SDLControl
	{
	public:
		SDLButton(SDL_Window* parent, std::string button_text, std::shared_ptr<Action> action, SDL_Rect client_area);
		void addToGroup(SDLButtonGroup* group);
		bool containsPoint(int x, int y);
		bool handleClick(int x, int y);
		void invokeAction() const;
		void render(SDL_Renderer* renderer);
		void setSelection(bool selected);
		void trigger();
	private:
		std::shared_ptr<Action> action_;
		std::string button_text_;
		SDLButtonGroup* button_group_;
	};
}