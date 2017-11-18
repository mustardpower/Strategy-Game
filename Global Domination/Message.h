#pragma once
#include <string>

class Message
{
public:
	Message() {}
	Message(std::string message_title, std::string message_text);
	Message::Message(const Message& another);
	std::string getTitle() const;
private:
	std::string message_title_;
	std::string message_text_;
};