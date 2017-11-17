#pragma once

#include <memory>
#include <vector>

#include "SDL.h"

#include "Action.h"
#include "ControlResources.h"
#include "SDLControl.h"
#include "ViewModel.h"

namespace global_domination
{
	class View
	{
	public:
		View(SDL_Window* parent, SDL_Rect client_area);
		virtual ~View();
		void addControl(std::shared_ptr<SDLControl> control);
		std::shared_ptr<SDLControl> getControl(ControlID id);
		std::shared_ptr<ViewModel> getReciever();
		void setReciever(std::shared_ptr<ViewModel> reciever);
		void handleClick(int mouse_x, int mouse_y);
		virtual void initialize() = 0;
		virtual void onKeyDown() = 0;
		virtual void onKeyUp() = 0;
		virtual void onKeyPress(int keyCode) = 0;
		void render(SDL_Renderer* renderer);

	protected:
		std::shared_ptr<ViewModel> reciever_;
		SDL_Rect client_area_;
		SDL_Window* parent_;
	private:
		std::vector<std::shared_ptr<SDLControl>> controls_;
	};
}