#include <iostream>
#include "Cards.h"

using namespace std;

int main() {
	//int numberDeck{};
	//int numberHand{};
	srand((int)time(NULL)); // regenerates the seed for the rand() call

	cout << "This file is just for testing at the moment." << '\n';

	Card card; // create an object card
	Deck* deck = new Deck();
	Hand* hand = new Hand();
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
	cout << "# of cards your hand can hold: " << hand->getSize() << '\n';

	Card* cardDrawn1 = deck->draw(); //fine
	hand->addHand(cardDrawn1); //adds the drawn card to the hand

	Card* cardDrawn2 = deck->draw();
	hand->addHand(cardDrawn2);

	Card* cardDrawn3 = deck->draw();
	hand->addHand(cardDrawn3);

	cout << "What card do you want to play?" << '\n';
	int index{};
	cin >> index;
	card.play(hand, index, deck);

	cout << "What card do you want to play?" << '\n';
	cin >> index;
	card.play(hand, index, deck);

	return 0;
}