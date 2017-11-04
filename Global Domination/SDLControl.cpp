#include "SDLControl.h"

unsigned int global_domination::SDLControl::getId()
{
	return id_;
}

void global_domination::SDLControl::setId(ControlID id)
{
	id_ = id;
}
