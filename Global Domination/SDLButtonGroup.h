#pragma once

#include <vector>

namespace global_domination
{
	class SDLButton;

	class SDLButtonGroup
	{
	public:
		SDLButtonGroup();
		void addToGroup(SDLButton* button);
		void setSelection(SDLButton* button);
	private:
		std::vector<SDLButton*> buttons_;
		SDLButton* selected_button_;
	};
}