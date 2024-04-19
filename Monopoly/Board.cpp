#include "Board.h"

void Board::InitArray() throw (const char*) {

	int i = 0;
	string line;
	ifstream myfile;
	myfile.open(BoardLayoutFile);

	if (!myfile.is_open()) {
		throw("error in opening the file: "  BoardLayoutFile);
	}
	while (getline(myfile, line)) {
		FillIndex(line, i);
		i++;
	}

}

void Board::FillIndex(string line, int index) {

	if (line[0] == 'P')
		CreateAsset(line, index);
	else
		CreateInstuction(line, index);
}

void Board::CreateAsset(string line, int index) {//turning string into asset info
	string cityname, slotname;
	int price, rent;
	string next = line.substr(2, line.length());
	int pos = next.find(',');
	string select = next.substr(0, pos);
	cityname = select;
	next = next.substr(pos+1, next.length());
	pos = next.find(',');
	select = next.substr(0, pos);
	slotname = select;
	next = next.substr(pos+1, next.length());
	pos = next.find(',');
	select = next.substr(0, pos);
	price = stoi(select);
	next = next.substr(pos+1, next.length());
	rent = stoi(next);
	SlotArray[index] = new Asset(slotname, cityname, price, rent);


}
void Board::CreateInstuction(string line, int index) {//string to instruction info

	string slotname;int insttype;
	string next = line.substr(2, line.length());
	int pos = next.find(',');
	string select = next.substr(0, pos);
	insttype =select[0];//problem here
	next = next.substr(pos+1, next.length());
	slotname = next;
	SlotArray[index] = new Instruction(slotname, insttype);


}
Board::Board()
{
	InitArray();

}


Board::~Board()
{
	for (int i = 0; i < NumOfSlots; i++)
	{
		SlotArray[i]->~Slot();

	}
}
