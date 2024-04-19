#pragma once
#include "includess.h"
#include "Slot.h"
#include "Asset.h"
#include "Instruction.h"
#define BoardLayoutFile "BoardLayout.txt"
class Board
{
	Slot* SlotArray[NumOfSlots];

	void CreateAsset(string line, int index);
	void CreateInstuction(string line, int index);
	void FillIndex(string line, int index);
public:

	Slot* GetSlot(int pos) { return SlotArray[pos - 1]; }
	void PrintSlotInfo(int position) {
		GetSlot(position)->PrintSlot();
	}
	void InitArray()throw (const char*);//read the file and fill the slotarray
	Board();
	~Board();
};

