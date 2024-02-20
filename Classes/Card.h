#pragma once
#include "Internals.h"

class Card
{
private:
	INT16 rank;
	char shape;
	char color;
public:
	Card();
	Card(INT16, const char, const char);
	Card(const Card&);

	const Card& operator=(const Card&);

	void setRank(const INT16);
	void setShape(const char);
	void setColor(const char);

	const INT16 getRank() const;
	const char getShape() const;
	const char getColor() const;

	~Card();
	
};

