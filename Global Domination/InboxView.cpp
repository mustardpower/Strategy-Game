#include "InboxView.h"

#include "ControlResources.h"
#include "Game.h"
#include "SDLListBox.h"
#include "SDLStaticText.h"

namespace global_domination {

	InboxView::InboxView(Game* the_game, SDL_Window * parent, SDL_Rect client_area) : SDLCompositePane(parent, client_area)
	{
		the_game_ = the_game;
	}

	void InboxView::initialize()
	{
		SDL_Rect list_box_client_area{ client_area_.w * 0.05, client_area_.h * 0.15, client_area_.w * 0.25, client_area_.h * 0.8 };
		std::shared_ptr<SDLListBox<Message>> message_list = std::make_shared<SDLListBox<Message>>(parent_, list_box_client_area, list_box_client_area.h * 0.2);
		message_list->setId(INBOX_LIST);
		addChildControl(message_list);

		addLabel("", client_area_.w * 0.6, client_area_.h * 0.3, SELECTED_MESSAGE_TITLE_LABEL);
		addLabel("", client_area_.w * 0.6, client_area_.h * 0.4, SELECTED_MESSAGE_TEXT_LABEL, 12);

		updateMessageList();
		
	}
	
	void InboxView::respondToAction(TYPES::ACTION_LIST action)
	{
		switch (action)
		{
			case TYPES::ACTION_LIST::NEXT_TURN:
			{
				updateMessageList();
			}
			break;
			case TYPES::ACTION_LIST::SELECTING_MESSAGE:
			{
				updateSelectedMessageText();
			}
			break;
		}
	}

	void InboxView::updateMessageList()
	{
		std::vector<Message> messages = the_game_->getGameModel()->getInboxMessages();
		if (messages.empty()) { return; }

		std::shared_ptr<Action> messageSelectionAction = std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::SELECTING_MESSAGE);
		std::shared_ptr<SDLListBox<Message>> message_list = std::dynamic_pointer_cast<SDLListBox<Message>>(getChildControl(INBOX_LIST));
		
		message_list->clearItems();

		for (std::vector<Message>::const_iterator message = messages.cbegin(); message != messages.end(); message++)
		{
			message_list->addItem(ListItem<Message>(message->getTitle(), messageSelectionAction, *message));
		}

		updateSelectedMessageText();
	}

	void InboxView::updateSelectedMessageText()
	{
		std::shared_ptr<SDLListBox<Message>> message_list = std::dynamic_pointer_cast<SDLListBox<Message>>(getChildControl(INBOX_LIST));
		Message* selected_message = message_list->selectedItem();
		if (selected_message)
		{
			setLabelText(SELECTED_MESSAGE_TEXT_LABEL, selected_message->getMessageText());
			setLabelText(SELECTED_MESSAGE_TITLE_LABEL, selected_message->getTitle());
		}
	}
}
