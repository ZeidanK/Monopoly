#pragma once
#include <queue>
#include "includess.h"

class Deck
{
	queue<int> StackCards;	
	void initDeck(int DeckSize);
public:
	int DrawCard(); const
	Deck(int DeckSize=0);
	~Deck();
};

