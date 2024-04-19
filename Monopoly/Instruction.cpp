#include "Instruction.h"
ostream& operator<<(ostream& os, const Instruction& inst) {

	cout << "Slot type Instruction by the name of " << inst.GetName() << endl;
	cout << "instruction type " << inst.GetTypeS() << endl;
	return os;
}
string Instruction::GetTypeS()const {
	switch(SlotType) {
	case jail: return "jail";
	case Start:return "Start";
	case Get_Ticket:return "Get Ticket";
	}
}

int Instruction::GetTypeInt()const {

	switch (SlotType) {
	case jail: return 1;
	case Start:return 2;
	case Get_Ticket:return 3;
	}


}
Instruction::Instruction(string SlotName, int Slottype):Slot(SlotName)
{
	SetType(Slottype);
}


Instruction::~Instruction()
{
}
