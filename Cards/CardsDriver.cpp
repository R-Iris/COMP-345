#include <iostream>
#include "Cards.h"

using namespace std;
	
int main() {
	srand((int)time(NULL));			//Regenerate the seed for the rand() call

	Card* card = new Card();		//Create an object card
	Player* player = new Player();	//Create an object player
	Deck* deck = new Deck();		//Create an object deck
	cout << *deck;

	Deck copyDeck(*deck);			//Copy constructor
	Deck copyDeck2 = *deck;			//Calls overloaded assignment operator

	Hand* hand = new Hand();		//Create an object hand

	cout << "# of cards your hand can hold: " << hand->getSize() << '\n';

	hand->addHand(deck->draw());	//Draws and adds the drawn card to the hand
	cout << *deck << *hand;

	hand->addHand(deck->draw());
	cout << *deck << *hand;

	hand->addHand(deck->draw());
	cout << *deck << *hand;

	Hand copyHand(*hand);			//Copy constructor
	Hand copyHand2 = *hand;			//Calls overloaded assignment operator

	int index{};
	cout << "What card do you want to play? Enter the index: ";
	cin >> index;
	card->play(hand, index, deck, player);
	cout << *deck << *hand;

	cout << "What card do you want to play? Enter the index: ";
	cin >> index;
	card->play(hand, index, deck, player);
	cout << *deck << *hand;

	cout << "\nThe player has the following orders in his list: " << player->getOrders();

	cout << "\n----------------------------------------------------------\n\n";

	cout << "Original deck: " << *deck << "Its memory address is : " << &deck << '\n';
	cout << "Using the copy constructor: " << copyDeck << "Its memory address is: " << &copyDeck << '\n';		// Output of the copied deck
	cout << "Using the assignment operator: " << copyDeck2 << "Its memory address is: " << &copyDeck2 << '\n'; // Output of the copied deck with assignment operator

	cout << "\nOriginal hand: " << *hand << "Its memory address is: " << &hand << '\n';
	cout << "Using the copy constructor: " << copyHand << "Its memory address is: " << &copyHand << '\n';		// Output of the copied hand
	cout << "Using the assignment operator: " << copyHand2 << "Its memory address is: " << &copyHand2 << '\n'; // Output of the copied hand with assignment operator

	delete card;
	delete player;
	delete deck;
	delete hand;
	card = NULL;
	player = NULL;
	deck = NULL;
	hand = NULL;

	return 0;
}