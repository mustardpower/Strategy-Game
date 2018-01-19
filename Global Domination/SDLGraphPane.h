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
			int axisOverlap();
			void drawAxes(SDL_Renderer* renderer);
			void drawDataPoints(SDL_Renderer* renderer);
			void drawXAxisLabels(SDL_Renderer* renderer);
			void drawYAxisLabels(SDL_Renderer* renderer);
			void getAxisRangeY(double &original_range_lower_y, double &original_range_upper_y);
			std::vector<double> getMappedXValues();
			std::vector<double> getMappedYValues();
			bool handleClick(int mouse_x, int mouse_y);
			double mapDataPointY(double unmapped_point_y);
			double minYValue();
			double maxYValue();
			void render(SDL_Renderer* renderer);
			void setAxisLabelsX(std::vector<std::string> labels);
			void setAxisLabelsY(std::vector<std::string> labels);
			void setDataPoints(std::vector<double> values_x, std::vector<double> values_y);
			double unmapDataPointY(double mapped_point_y);
			SDL_Point xAxisStartPoint();
			SDL_Point xAxisEndPoint();
			int xAxisLength();
			SDL_Point yAxisStartPoint();
			SDL_Point yAxisEndPoint();
			int yAxisLength();
		private:
			std::vector<std::string> axis_labels_x_;
			std::vector<std::string> axis_labels_y_;
			float min_x_;
			float min_y_;
			float max_x_;
			float max_y_;
			const double plot_margin_ = 0.1; // percentage of client area from plot to client area edge
			std::vector<double> data_points_x_;
			std::vector<double> data_points_y_;
	};
}