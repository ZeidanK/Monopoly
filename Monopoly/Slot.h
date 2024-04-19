#pragma once
#include "includess.h"
class Slot
{

	void SetName(string name) {
		SlotName = name;
	}


protected:
	string SlotName;


public:
	virtual string GetName()const { return SlotName; }
	virtual void PrintSlot()=0;

	 Slot(string name);
	~Slot();
};

