#include "Slot.h"



Slot::Slot(string name)
{
	this->SetName(name);
}


Slot::~Slot()
{
	this->SlotName.~basic_string();
}
