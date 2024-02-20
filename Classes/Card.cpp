#include "Card.h"

Card::Card() : rank(NULL), shape(NULL), color(NULL) {}

Card::Card(const INT16 rk, const char sp, const char cl) { // if jokers, rank = NULL, shape = 'j', and each color
	this->rank = rk;
	this->shape = sp;
	this->color = cl;
}

Card::Card(const Card& other) {
	this->rank = other.rank;
	this->shape = other.shape;
	this->color = other.color;
}

const Card& Card::operator=(const Card& other) {
	this->rank = other.rank;
	this->shape = other.shape;
	this->color = other.color;

	return *this;
}


void Card::setRank(const INT16 rk) {
	this->rank = rk;
}

void Card::setShape(const char sp) {
	this->shape = sp;
}

void Card::setColor(const char cl) {
	this->color = cl;
}

const INT16 Card::getRank() const {
	return this->rank;
}

const char Card::getShape() const {
	return this->shape;
}

const char Card::getColor() const {
	return this->color;
}

Card::~Card() {
	this->rank = NULL;
	this->color = NULL;
	this->shape = NULL;
}