#include "SDLControl.h"

#include <assert.h>

namespace global_domination
{
	SDLControl::SDLControl(SDL_Window* parent, SDL_Color background_color)
	{
		id_ = UNDEFINED_CONTROL_ID;
		parent_ = parent;
		background_color_ = background_color;
	}

	unsigned int SDLControl::getId()
	{
		return id_;
	}

	void SDLControl::setFontSize(int font_size)
	{
		font_size_ = font_size;
	}

	void SDLControl::setId(ControlID id)
	{
		assert(id_ == UNDEFINED_CONTROL_ID);
		id_ = id;
	}
}

