#include "SDLGraphPane.h"
#include "SDL_TextRenderer.h"

#include <algorithm>
#include <vector>

namespace global_domination
{
	SDLGraphPane::SDLGraphPane(SDL_Window* parent, SDL_Rect client_area) : SDLControl(parent, client_area)
	{
	}

	int SDLGraphPane::axisOverlap()
	{
		return (int)(client_area_.w * (plot_margin_ / 5.0));
	}

	void SDLGraphPane::drawAxes(SDL_Renderer * renderer)
	{
		SDL_RenderDrawLine(
			renderer, 
			xAxisStartPoint().x - axisOverlap(),
			xAxisStartPoint().y,
			xAxisEndPoint().x,
			xAxisEndPoint().y
		);

		SDL_RenderDrawLine(
			renderer,
			yAxisStartPoint().x,
			yAxisStartPoint().y,
			yAxisEndPoint().x,
			yAxisEndPoint().y + axisOverlap()
		);

		drawXAxisLabels(renderer);
		drawYAxisLabels(renderer);
	}

	void SDLGraphPane::drawDataPoints(SDL_Renderer * renderer)
	{
		// map x values to the pixel on the x axis
		std::vector<double> x_values_mapped = getMappedXValues();
		std::vector<double> y_values_mapped = getMappedYValues();

		SDL_Point* mapped_points = new SDL_Point[data_points_x_.size()];
		for (size_t index = 0; index < data_points_y_.size(); index++)
		{
			x_values_mapped[index], y_values_mapped[index];
			const SDL_Point pt{ (int)x_values_mapped[index] , (int)y_values_mapped[index] };
			mapped_points[index] = pt;
		}
		// draw lines made from mapped values here!
		for (size_t index = 0; index < data_points_y_.size(); index++)
		{
			SDL_RenderDrawLines(renderer, mapped_points, data_points_y_.size());
		}

		delete[] mapped_points;
	}

	void SDLGraphPane::drawXAxisLabels(SDL_Renderer * renderer)
	{
		const int interval_x = xAxisLength() / axis_labels_x_.size();
		int marker_x = xAxisStartPoint().x;
		for (size_t label_index = 0; label_index < axis_labels_x_.size(); label_index++)
		{
			int text_width, text_height;
			text_renderer::getTextDimensions(axis_labels_x_.at(label_index), text_width, text_height);
			int quarter_text_width = (int)(text_width / 4.0);
			SDL_RenderDrawLine(renderer, marker_x, xAxisStartPoint().y, marker_x, xAxisStartPoint().y + (axisOverlap() / 2));
			SDL_Rect label_location = { marker_x - quarter_text_width, xAxisStartPoint().y + (2 * (axisOverlap() / 2)) , 0, 0 };
			text_renderer::renderText(parent_, axis_labels_x_.at(label_index), label_location, getTextColor(), getBackgroundColor(), font_size_);
			marker_x += interval_x;
		}
	}

	void SDLGraphPane::drawYAxisLabels(SDL_Renderer * renderer)
	{
		const int kDefaultNoOfIntervals = 10;
		int number_of_intervals = data_points_y_.empty() ? kDefaultNoOfIntervals : data_points_y_.size();
		const int interval_y = yAxisLength() / number_of_intervals;
		for (int marker_y = yAxisStartPoint().y; marker_y < yAxisStartPoint().y + yAxisLength(); marker_y += interval_y)
		{
			SDL_RenderDrawLine(renderer, yAxisStartPoint().x - (axisOverlap() / 2), marker_y, yAxisStartPoint().x, marker_y);
		}
	}

	std::vector<double> SDLGraphPane::getMappedXValues()
	{
		std::vector<double> x_values_mapped;
		if (data_points_x_.size() > 0)
		{
			double original_range_lower_x = *std::min_element(data_points_x_.begin(), data_points_x_.end());
			double original_range_upper_x = *std::max_element(data_points_x_.begin(), data_points_x_.end());

			double new_range_lower_x = xAxisStartPoint().x;
			double new_range_upper_x = xAxisStartPoint().x + xAxisLength();
			for (size_t index = 0; index < data_points_x_.size(); index++)
			{
				double unmapped_value_x = data_points_x_.at(index);
				double mapped_x = (unmapped_value_x - original_range_lower_x) / (original_range_upper_x - original_range_lower_x) * (new_range_upper_x - new_range_lower_x) + new_range_lower_x;
				x_values_mapped.push_back(mapped_x);
			}
		}
		return x_values_mapped;
	}

	std::vector<double> SDLGraphPane::getMappedYValues()
	{
		std::vector<double> y_values_mapped;
		if (data_points_y_.size() > 0)
		{
			const int kNumOfDataPointsDisplayed = std::min(data_points_x_.size(), data_points_y_.size());
			std::vector<double>::iterator first_data_point = data_points_y_.end() - kNumOfDataPointsDisplayed;
			double original_range_lower_y = *std::min_element(first_data_point, data_points_y_.end());
			double original_range_upper_y = *std::max_element(first_data_point, data_points_y_.end());

			if (original_range_lower_y == original_range_upper_y)
			{
				original_range_lower_y = original_range_lower_y * 0.5;
				original_range_upper_y = original_range_upper_y * 1.5;
			}

			double new_range_lower_y = yAxisStartPoint().y;
			double new_range_upper_y = yAxisStartPoint().y + yAxisLength();
			for (size_t index = 0; index < data_points_y_.size(); index++)
			{
				double unmapped_value_y = data_points_y_.at(index);
				double mapped_y = (unmapped_value_y - original_range_lower_y) / (original_range_upper_y - original_range_lower_y) * (new_range_upper_y - new_range_lower_y) + new_range_lower_y;
				y_values_mapped.push_back(mapped_y);
			}
		}
		return y_values_mapped;
	}

	bool SDLGraphPane::handleClick(int mouse_x, int mouse_y)
	{
		return false;
	}

	void SDLGraphPane::render(SDL_Renderer * renderer)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);
		SDL_RenderFillRect(renderer, &client_area_);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderDrawRect(renderer, &client_area_);

		drawAxes(renderer);
		drawDataPoints(renderer);
	}

	void SDLGraphPane::setAxisLabelsX(std::vector<std::string> labels)
	{
		axis_labels_x_ = labels;
	}

	void SDLGraphPane::setAxisLabelsY(std::vector<std::string> labels)
	{
		axis_labels_y_ = labels;
	}
	void SDLGraphPane::setDataPoints(std::vector<double> values_x, std::vector<double> values_y)
	{
		data_points_x_ = values_x;
		data_points_y_ = values_y;
	}
	SDL_Point SDLGraphPane::xAxisStartPoint()
	{
		int x_axis_start_x = (int)(client_area_.x + (client_area_.w * plot_margin_));
		int x_axis_start_y = (int)(client_area_.y + (client_area_.h * plot_margin_) + yAxisLength());
		return SDL_Point{ x_axis_start_x, x_axis_start_y };
	}
	SDL_Point SDLGraphPane::xAxisEndPoint()
	{
		int end_x = xAxisStartPoint().x + xAxisLength();
		int end_y =	xAxisStartPoint().y;
		return SDL_Point{ end_x, end_y };
	}
	int SDLGraphPane::xAxisLength()
	{
		return (int)(client_area_.w * (1.0 - 2 * plot_margin_));
	}
	SDL_Point SDLGraphPane::yAxisStartPoint()
	{
		int y_axis_start_x = (int)(client_area_.x + (client_area_.w * plot_margin_));
		int y_axis_start_y = (int)(client_area_.y + (client_area_.h * plot_margin_));
		return SDL_Point{ y_axis_start_x, y_axis_start_y };
	}
	SDL_Point SDLGraphPane::yAxisEndPoint()
	{
		int end_x = yAxisStartPoint().x;
		int end_y = yAxisStartPoint().y + yAxisLength();
		return SDL_Point{ end_x, end_y };
	}
	int SDLGraphPane::yAxisLength()
	{
		return (int)(client_area_.h * (1.0 - 2 * plot_margin_));
	}
}

