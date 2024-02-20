#pragma once

#include "Card.h"

class Deck
{
private:
	std::vector<Card*> deck;
public:
	Deck();

	void shuffle();
	Card& draw();

	~Deck();
};

