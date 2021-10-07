#include <iostream>
#include "Cards.h"

using namespace std;

int main() {
	srand((int)time(NULL));			//Regenerate the seed for the rand() call

	Card* card = new Card();		//Create an object card
	Player* player = new Player();	//Create an object player

	int cardsDeck{};
	cout << "Enter number of cards in the deck. Must be a multiple of 5 and at most 30: " << '\n';
	cin >> cardsDeck;
	while (cardsDeck % 5 != 0 || cardsDeck > 30) {
		cout << "The number of cards you've entered does not fit the requirements. Please try again." << '\n';
		cin >> cardsDeck;
	}

	Deck* deck = new Deck(cardsDeck);	//Create a deck object
	cout << *deck;

	Deck* copyDeck = new Deck(*deck);	//Copy constructor		
	Deck copyDeck2 = *deck;				//Calls overloaded assignment operator

	int cardsHand{};
	cout << "\nEnter number for the player's hand. It must be at most 5: " << '\n';
	cin >> cardsHand;
	while (cardsHand > 5) {
		cout << "The number of cards you've entered does not fit the requirements. Please try again." << '\n';
		cin >> cardsDeck;
	}

	Hand* hand = new Hand(cardsHand);		//Create an object hand

	cout << "# of cards your hand can hold: " << hand->getSize() << '\n';

	while (!(hand->handFull())) {
		hand->addHand(deck->draw());	//Draws and adds the drawn card to the hand
		cout << *deck << *hand;
	}

	Hand* copyHand = new Hand(*hand);	//Copy constructor
	Hand copyHand2 = *hand;				//Calls overloaded assignment operator

	int index{};
	cout << endl << "What card do you want to play? Enter the index: ";
	cin >> index;
	card->play(hand, index, deck, player);
	cout << *deck << *hand;

	cout << endl << "What card do you want to play? Enter the index: ";
	cin >> index;
	card->play(hand, index, deck, player);
	cout << *deck << *hand;

	cout << "\nThe player has the following orders in his list: " << player->getOrders();

	cout << "\n----------------------------------------------------------\n\n";

	cout << "Original deck: " << *deck << "Its memory address is : " << &deck << '\n';
	cout << "Using the copy constructor: " << *copyDeck << "Its memory address is: " << &copyDeck << '\n';		//Output of the copied deck
	cout << "Using the assignment operator: " << copyDeck2 << "Its memory address is: " << &copyDeck2 << '\n';	//Output of the copied deck with assignment operator

	cout << "\nOriginal hand: " << *hand << "Its memory address is: " << &hand << '\n';
	cout << "Using the copy constructor: " << *copyHand << "Its memory address is: " << &copyHand << '\n';		//Output of the copied hand
	cout << "Using the assignment operator: " << copyHand2 << "Its memory address is: " << &copyHand2 << '\n';	//Output of the copied hand with assignment operator

	delete card;
	delete player;
	delete deck;
	delete hand;
	delete copyDeck;
	delete copyHand;
	card = NULL;
	player = NULL;
	deck = NULL;
	hand = NULL;
	copyDeck = NULL;
	copyHand = NULL;

	return 0;
}