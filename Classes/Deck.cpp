#include "Deck.h"

Deck::Deck() {
	for (int i = 1; i <= 13; i++) {
		deck.push_back(new Card(i, 's', 'b')); // appending spades
	}
	for (int i = 1; i <= 13; i++) {
		deck.push_back(new Card(i, 'c', 'b')); // appending clovers
	}
	for (int i = 1; i <= 13; i++) {
		deck.push_back(new Card(i, 'h', 'r')); // appending hearts
	}
	for (int i = 1; i <= 13; i++) {
		deck.push_back(new Card(i, 'd', 'r')); // appending diamonds
	}

	// appending jokers
	deck.push_back(new Card(NULL, 'j', 'b'));
	deck.push_back(new Card(NULL, 'j', 'r'));
}

void Deck::shuffle() {
	Card* tempDeck[CARD_NO] = { nullptr, };
	unsigned int cdNo = 0;
	unsigned int idx = 0;

	// move all cards to temp deck
	for (int i = 0; i < CARD_NO; i++) {
		tempDeck[i] = deck[i];
	}

	if (deck.size() != CARD_NO) {
		// error case, shuffle would be done one time when the game begins. 
		exit(-1);
	}

	while (!deck.empty()) {
		deck.pop_back();
	}
	
	srand(static_cast<unsigned short>(time(NULL)));
	while (true) {
		if (idx >= CARD_NO) { // if deck is full, exit the loop
			break;
		}

		cdNo = rand() % CARD_NO;
		if (tempDeck[cdNo] != nullptr) { // if picked card is not in the deck
			deck.push_back(tempDeck[cdNo]); // append the card to the deck
			tempDeck[cdNo] = nullptr; // remove the card from the tempdeck
			idx++; // increase the index that indicates the number of cards in the deck
		}
		else {
			continue;
		}
	}
}

Card& Deck::draw() {
	Card* d = new Card();
	d = deck[deck.size() - 1];
	deck.pop_back();
	return *d;
}

Deck::~Deck() {
	while (!deck.empty()) {
		deck.pop_back();
	}
}