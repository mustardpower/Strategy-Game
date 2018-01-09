#include "SDLGraphPane.h"
#include "SDL_TextRenderer.h"

#include <algorithm>
#include <vector>

namespace global_domination
{
	SDLGraphPane::SDLGraphPane(SDL_Window* parent, SDL_Rect client_area) : SDLControl(parent, client_area)
	{
		number_of_intervals_x = 12;
		number_of_intervals_y = 10;
	}

	void SDLGraphPane::drawAxes(SDL_Renderer * renderer)
	{
		const double margin = 0.1;
		const int extra_axis_overlap = (int)(client_area_.w * (margin / 5.0));

		int y_axis_start_x = (int)(client_area_.x + (client_area_.w * margin));
		int y_axis_start_y = (int)(client_area_.y + (client_area_.h * margin));
		int axis_length_y = (int)(client_area_.h * (1.0 - 2 * margin));

		int x_axis_start_x = (int)(client_area_.x + (client_area_.w * margin));
		int x_axis_start_y = (int)(client_area_.y + (client_area_.h * margin) + axis_length_y);
		int axis_length_x = (int)(client_area_.w * (1.0 - 2 * margin));

		SDL_RenderDrawLine(
			renderer, 
			x_axis_start_x - extra_axis_overlap,
			x_axis_start_y, 
			x_axis_start_x + axis_length_x,
			x_axis_start_y
		);

		SDL_RenderDrawLine(
			renderer,
			y_axis_start_x,
			y_axis_start_y,
			y_axis_start_x,
			y_axis_start_y + axis_length_y + extra_axis_overlap
		);

		// draw markers on x axis
		const int interval_x = axis_length_x / axis_labels_x_.size();
		int marker_x = x_axis_start_x;
		for (size_t label_index = 0; label_index < axis_labels_x_.size(); label_index++)
		{
			int text_width, text_height;
			text_renderer::getTextDimensions(axis_labels_x_.at(label_index), text_width, text_height);
			int quarter_text_width = (int)(text_width / 4.0);
			SDL_RenderDrawLine(renderer, marker_x, x_axis_start_y, marker_x, x_axis_start_y + (extra_axis_overlap / 2));
			SDL_Rect label_location = { marker_x - quarter_text_width, x_axis_start_y + ( 2 * (extra_axis_overlap / 2)) , 0, 0 };
			text_renderer::renderText(parent_, axis_labels_x_.at(label_index), label_location, getTextColor(), getBackgroundColor(), font_size_);
			marker_x += interval_x;
		}

		// draw markers on y axis
		const int interval_y = axis_length_y / number_of_intervals_y;
		for (int marker_y = y_axis_start_y; marker_y < y_axis_start_y + axis_length_y; marker_y += interval_y)
		{
			SDL_RenderDrawLine(renderer, y_axis_start_x - (extra_axis_overlap / 2), marker_y, y_axis_start_x, marker_y);
		}
	}

	void SDLGraphPane::drawDataPoints(SDL_Renderer * renderer)
	{
		// map x values to the pixel on the x axis
		std::vector<double> x_values_mapped;
		const double margin = 0.1;

		if (data_points_x_.size() > 0)
		{
			double original_range_lower_x = *std::min_element(data_points_x_.begin(), data_points_x_.end());
			double original_range_upper_x = *std::max_element(data_points_x_.begin(), data_points_x_.end());
			
			int x_axis_start_x = (int)(client_area_.x + (client_area_.w * margin));
			double new_range_lower_x = x_axis_start_x;
			int axis_length_x = (int)(client_area_.w * (1.0 - 2 * margin));
			double new_range_upper_x = x_axis_start_x + axis_length_x;
			for (size_t index = 0; index < data_points_x_.size(); index++)
			{
				double unmapped_value_x = data_points_x_.at(index);
				double mapped_x = (unmapped_value_x - original_range_lower_x) / (original_range_upper_x - original_range_lower_x) * (new_range_upper_x - new_range_lower_x) + new_range_lower_x;
				x_values_mapped.push_back(mapped_x);
			}
		}
		

		// map y values to the pixel on the y axis
		std::vector<double> y_values_mapped;

		if (data_points_y_.size() > 0)
		{
			double original_range_lower_y = *std::min_element(data_points_y_.begin(), data_points_y_.end());
			double original_range_upper_y = *std::max_element(data_points_y_.begin(), data_points_y_.end());
			int y_axis_start_y = (int)(client_area_.y + (client_area_.h * margin));
			double new_range_lower_y = y_axis_start_y;
			int axis_length_y = (int)(client_area_.w * (1.0 - 2 * margin));
			double new_range_upper_y = y_axis_start_y + axis_length_y;
			for (size_t index = 0; index < data_points_y_.size(); index++)
			{
				double unmapped_value_y = data_points_y_.at(index);
				double mapped_y = (unmapped_value_y - original_range_lower_y) / (original_range_upper_y - original_range_lower_y) * (new_range_upper_y - new_range_lower_y) + new_range_lower_y;
				y_values_mapped.push_back(mapped_y);
			}
		}

		// draw lines made from mapped values here!
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
}

