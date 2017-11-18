#include "Message.h"

Message::Message(std::string message_title, std::string message_text)
{
	message_title_ = message_title;
	message_text_ = message_text;
}

Message::Message(const Message& another)
{
	message_text_ = another.message_text_;
	message_title_ = another.message_title_;
}

std::string Message::getTitle() const
{
	return message_title_;
}
