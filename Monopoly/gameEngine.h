#pragma once
#include "includess.h"
#include "Board.h"
#include "Deck.h"
#include "Player.h"
#include "Instruction.h"
#include "Asset.h"
#define DeckSize 100
class gameEngine
{
	Board GameBoard;
	queue<Player*> PQueue;
	int NumberOfPlayers;
	Deck* Cards;


	bool CheckName(string name,int i)throw(const char*);//return true if name is available
	bool AssetOptions(Asset* asset, Player* P);
	bool InstuctionOption(Instruction* instructin, Player* P);
	void RemovePlayer(Player* P);//function to remove player and free his holdings
	int throwDice();//function to throuw the dice
	void PrintSlotInfo(int position);//functin to print the position on board used twice before and after dice throw
	bool JailCheak(Player* P);//function to cheack for jail time and remove time
	bool NewSlotOptions(Slot* slot, Player* P);
	bool Turn(Player* P);//return true is player is still in the game false if he quit
	void intigame();
public:
	void RunGame();
	gameEngine();
	~gameEngine();
};

