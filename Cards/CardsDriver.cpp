#include <iostream>
#include "Cards.h"

using namespace std;

int main() {
	//int numberDeck{};
	//int numberHand{};
	srand((int)time(NULL)); // regenerates the seed for the rand() call

	cout << "This file is just for testing at the moment." << '\n';

	Deck deck; // create an object deck
	Hand hand; // create an object hand
	Card card; // create an object card
	/*
	cout << "Enter how many cards you wish to have in your deck. The integer must be between 15 and 25: ";
	cin >> numberDeck;
	while ((numberDeck < 15) || numberDeck > 25) {
		cout << "Please enter an integer between 15 and 25: ";
		cin >> numberDeck;
	}
	deck.setSize(ptrDeck);
	cout << "Enter how many cards you wish to have in your hand. The integer must be between 2 and 3: ";
	cin >> numberHand;
	while ((numberHand < 2) || numberHand > 3)
	{
		cout << "Please enter an integer between 2 and 3: ";
		cin >> numberHand;
	}
	hand.setSize(numberHand);
	*/
	cout << "# of cards your hand can hold: " << hand.getSize() << '\n';

	vector<Card*> cardsInHand;

	Card* cardDrawn1 = deck.draw();
	cardsInHand = hand.addHand(cardDrawn1);

	Card* cardDrawn2 = deck.draw();
	cardsInHand = hand.addHand(cardDrawn2);

	Card* cardDrawn3 = deck.draw();
	cardsInHand = hand.addHand(cardDrawn3);

	Card* cardPlayed1 = card.play(cardsInHand, 1);
	deck.addCard(cardPlayed1);
	hand.removeHand(cardPlayed1);

	Card* cardPlayed2 = card.play(cardsInHand, 0);
	deck.addCard(cardPlayed2);
	hand.removeHand(cardPlayed2);

	return 0;
}