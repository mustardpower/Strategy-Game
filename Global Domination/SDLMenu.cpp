#include "SDLMenu.h"

string MenuItem::reportString() const
{
	return text;
}

void MenuItem::invokeAction() const
{
	action->Execute();
}
