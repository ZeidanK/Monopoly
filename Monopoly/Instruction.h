#pragma once
#include "Slot.h"
class Instruction:public Slot
{
	enum instruction { jail=74, Start=83, Get_Ticket=84 };

	instruction SlotType;

	void SetType(int num) { SlotType = (instruction)num; }
public:

	virtual void PrintSlot() { cout << *this; }
	string GetTypeS()const;
	int GetTypeInt()const;
	friend ostream& operator<<(ostream& os, const Instruction& instruction);
	Instruction(string SlotName,int Slottype);
	~Instruction();
};

