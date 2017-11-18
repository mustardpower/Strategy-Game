#include "InboxView.h"

#include "ControlResources.h"
#include "Game.h"
#include "SDLStaticText.h"

namespace global_domination {

	InboxView::InboxView(Game* the_game, SDL_Window * parent, SDL_Rect client_area) : View(the_game, parent, client_area)
	{
	}

	void InboxView::initialize()
	{
		std::shared_ptr<SDLStaticText> title_label = std::make_shared<SDLStaticText>(parent_, "INBOX", client_area_.w * 0.25, client_area_.h * 0.05);
		addControl(title_label);
		
		std::string nation_name = the_game_->getGameModel()->getSelectedNationName();
		std::shared_ptr<SDLStaticText> name_label = std::make_shared<SDLStaticText>(parent_, nation_name, client_area_.w * 0.25, client_area_.h * 0.25);
		addControl(name_label);

		std::shared_ptr<SDLMenu<Message>> message_list = std::make_shared<SDLMenu<Message>>(parent_, client_area_.w * 0.2, client_area_.h * 0.4, client_area_.h * 0.1);
		message_list->setId(INBOX_LIST);
		addControl(message_list);

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
		}
	}

	void InboxView::updateMessageList()
	{
		std::vector<Message> messages = the_game_->getGameModel()->getInboxMessages();
		std::shared_ptr<Action> messageSelectionAction = std::make_shared<Action>(the_game_, TYPES::ACTION_LIST::SELECTING_MESSAGE);
		std::shared_ptr<SDLMenu<Message>> message_list = std::dynamic_pointer_cast<SDLMenu<Message>>(getControl(INBOX_LIST));
		
		message_list->clearItems();

		for (std::vector<Message>::const_iterator message = messages.cbegin(); message != messages.end(); message++)
		{
			message_list->addMenuItem(MenuItem<Message>(message->getTitle(), messageSelectionAction, *message));
		}
	}
}
