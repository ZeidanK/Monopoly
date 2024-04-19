#include "Deck.h"


void Deck::initDeck(int DeckSize) {
	int random, sign;
	for (int i = 0; i < DeckSize; i++) {
		sign = rand() % 2;
		random = rand() % 350;
		if (sign)
			StackCards.push(random);
		else StackCards.push(random*(-1));
	}
}

int Deck::DrawCard() {
	int res = StackCards.front();
	StackCards.pop();
	StackCards.push(res);
	return res;
}

Deck::Deck(int DeckSize)
{
	initDeck(DeckSize);
}


Deck::~Deck()
{
}
