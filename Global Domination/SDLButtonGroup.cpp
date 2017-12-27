#include "SDLButtonGroup.h"

#include "SDLButton.h"

namespace global_domination
{
	SDLButtonGroup::SDLButtonGroup()
	{
		selected_button_ = NULL;
	}

	void SDLButtonGroup::addToGroup(SDLButton* button)
	{
		buttons_.push_back(button);
		button->addToGroup(this);
	}

	void SDLButtonGroup::setSelection(SDLButton * button)
	{
		if (selected_button_)
		{
			selected_button_->setSelection(false);
		}
		
		selected_button_ = button;
	}
}
