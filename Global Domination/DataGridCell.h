#pragma once

#include "Action.h"

namespace global_domination
{
	class DataGridCell
	{
	public:
		DataGridCell() {};
		void invokeAction() const;
		virtual std::string reportString() const = 0;
		void setAction(std::shared_ptr<Action> an_action);

		DataGridCell(std::shared_ptr<Action> an_action)
		{
			action_ = an_action;
		}

	private:
		std::shared_ptr<Action> action_;
		SDL_Color text_color_;
		std::shared_ptr<SDL_Rect> text_location_;
	};

	inline void DataGridCell::invokeAction() const
	{
		if (action_)
		{
			action_->execute();
		}
	}

	inline void DataGridCell::setAction(std::shared_ptr<Action> an_action)
	{
		action_ = an_action;
	}
}