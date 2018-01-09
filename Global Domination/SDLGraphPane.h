#pragma once

#include "SDL.h"

#include "SDLControl.h"

namespace global_domination
{
	struct Point2D
	{
		double x_;
		double y_;
		Point2D(double x, double y)
		{
			x_ = x;
			y_ = y;
		}
	};
	class SDLGraphPane : public SDLControl
	{
		public:
			SDLGraphPane(SDL_Window* parent, SDL_Rect client_area);
			void drawAxes(SDL_Renderer* renderer);
			void drawDataPoints(SDL_Renderer* renderer);
			bool handleClick(int mouse_x, int mouse_y);
			void render(SDL_Renderer* renderer);
			void setAxisLabelsX(std::vector<std::string> labels);
			void setAxisLabelsY(std::vector<std::string> labels);
			void setDataPoints(std::vector<double> values_x, std::vector<double> values_y);
		private:
			std::vector<std::string> axis_labels_x_;
			std::vector<std::string> axis_labels_y_;
			float min_x_;
			float min_y_;
			float max_x_;
			float max_y_;
			int number_of_intervals_x;
			int number_of_intervals_y;
			std::vector<double> data_points_x_;
			std::vector<double> data_points_y_;
	};
}