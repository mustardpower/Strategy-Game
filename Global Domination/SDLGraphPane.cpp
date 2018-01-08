#include "SDLGraphPane.h"

namespace global_domination
{
	SDLGraphPane::SDLGraphPane(SDL_Window* parent, SDL_Rect client_area) : SDLControl(parent, client_area)
	{
		number_of_intervals_x = 10;
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
		const int interval_x = axis_length_x / number_of_intervals_x;
		for (int marker_x = x_axis_start_x; marker_x < x_axis_start_x + axis_length_x; marker_x += interval_x)
		{
			SDL_RenderDrawLine(renderer, marker_x, x_axis_start_y, marker_x, x_axis_start_y + (extra_axis_overlap / 2));
		}

		// draw markers on y axis
		const int interval_y = axis_length_y / number_of_intervals_y;
		for (int marker_y = y_axis_start_y; marker_y < y_axis_start_y + axis_length_y; marker_y += interval_y)
		{
			SDL_RenderDrawLine(renderer, y_axis_start_x - (extra_axis_overlap / 2), marker_y, y_axis_start_x, marker_y);
		}
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
	}
}

