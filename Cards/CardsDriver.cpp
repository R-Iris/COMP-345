#include <iostream>
#include "Cards.h"

using namespace std;

int main() {
	//int numberDeck{};
	//int numberHand{};
	srand((int)time(NULL)); // regenerates the seed for the rand() call

	cout << "This file is just for testing at the moment." << '\n';

	Card card; // Create an object card

	Deck* deck = new Deck();
	cout << *deck;

	Deck copyDeck(*deck); // Copy constructor
	Deck copyDeck2 = *deck; // Calls overloaded assignment

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
	cout << *deck << *hand;

	Card* cardDrawn2 = deck->draw();
	hand->addHand(cardDrawn2);
	cout << *deck << *hand;

	Card* cardDrawn3 = deck->draw();
	hand->addHand(cardDrawn3);
	cout << *deck << *hand;

	Hand copyHand(*hand);
	Hand copyHand2 = *hand;

	cout << "What card do you want to play? Enter the index: ";
	int index{};
	cin >> index;
	card.play(hand, index, deck);
	cout << *deck << *hand;

	cout << "What card do you want to play? Enter the index: ";
	cin >> index;
	card.play(hand, index, deck);
	cout << *deck << *hand;

	cout << "\n----------------------------------------------------------\n\n";
	
	cout << "Original deck: " << *deck << "Its memory address is : " << &deck << '\n';
	cout << "Using the copy constructor: " << copyDeck << "Its memory address is: " << &copyDeck << '\n'; // Output of the copied deck
	cout << "Using the assignment operator: " << copyDeck2 << "Its memory address is: " << &copyDeck2 << '\n'; // Output of the copied deck with assignment operator

	cout << "\nOriginal hand: " << *hand << "Its memory address is: " << &hand << '\n';
	cout << "Using the copy constructor: " << copyHand << "Its memory address is: " << &copyHand << '\n'; // Output of the copied hand
	cout << "Using the assignment operator: " << copyHand2 << "Its memory address is: " << &copyHand2 << '\n'; // Output of the copied hand with assignment operator


	delete deck;
	delete hand;

	return 0;
}