#pragma once

#include "SDL.h"

#include "SDLControl.h"

namespace global_domination
{
	struct Point2D
	{
		float x;
		float y;
	};
	class SDLGraphPane : public SDLControl
	{
		public:
			SDLGraphPane(SDL_Window* parent, SDL_Rect client_area);
			void drawAxes(SDL_Renderer* renderer);
			bool handleClick(int mouse_x, int mouse_y);
			void render(SDL_Renderer* renderer);
		private:
			float min_x_;
			float min_y_;
			float max_x_;
			float max_y_;
			int number_of_intervals_x;
			int number_of_intervals_y;
			std::vector<Point2D> data_points_;
	};
}