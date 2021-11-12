#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>

#include "Cards.h"

using namespace std;

//Default constructor
Card::Card() : cardTypeName("Default") { }

Card::Card(cardType type) {
	switch (type) {
	case cardType::Bomb:
		cardTypeName = "Bomb";
		break;
	case cardType::Reinforcement:
		cardTypeName = "Reinforcement";
		break;
	case cardType::Blockade:
		cardTypeName = "Blockade";
		break;
	case cardType::Airlift:
		cardTypeName = "Airlift";
		break;
	case cardType::Diplomacy:
		cardTypeName = "Diplomacy";
		break;
	}
}

//Copy constructor
Card::Card(const Card &card) : cardTypeName(card.cardTypeName) { }

//Overloading the assignment operator
Card& Card::operator= (const Card& card) {
	this->cardTypeName = card.cardTypeName;

	return *this;
}

//Play method that is inherited by all children of the card class. It takes a card from the player's hand, creates an order and puts the card back into the deck.
void Card::play(Hand* hand, int index, Deck* deck, Player* player,Player* otherPlayer, OrdersList* ordersList, Territory* start, Territory* target,GameEngine* gameEngine) {
	//Validating that the index the user inputted is correct
	if (!validateIndex(hand->getCardsInHand(), index)) {
		cout << "\nYour hand only contains " << hand->getCardsInHand().size() << " cards. The index you entered is invalid. Terminating program." << '\n';
		exit(1);
	}

	//Temporary pointer to the card played
	Card* playedCard = hand->getCardInHand(index);
	cout << "\nThe " << playedCard->cardTypeName << " card has been played." << '\n';
	//Creates a pointer to an order of the card's type
	//Order* order = new Order(hand->getCardInHand(index)->getCardTypeName());
	switch (enumToInt(playedCard->getCardTypeName())) {
	case 0:
		ordersList->addOrders(new Bomb(player,target, gameEngine));
		break;
	case 1:
		ordersList->addOrders(new Deploy(player, 10, target, gameEngine)); //None of the orders are reinforcement. From the first PDF "reinforcement: the player receives 5 reinforcement army units."
		break;
	case 2:
		ordersList->addOrders(new Blockade(player,target,gameEngine));
		break;
	case 3:
		ordersList->addOrders(new Airlift(player, 10, start, target, gameEngine));
		break;
	case 4:
		ordersList->addOrders(new Negotiate(player,otherPlayer, gameEngine));
		break;
	}

	//Removes card played from the hand
	hand->removeCard(index);

	//Adds the card played to the deck
	deck->addCard(playedCard);
}

//Overloading the output stream operator for vectors containing pointers to card objects
ostream& operator<< (ostream& out, const vector<Card*> cards) {
	out << "[ ";
	for (int i = 0; i < cards.size(); i++) {
		out << cards[i]->getCardTypeName();
		if (i != cards.size() - 1) out << ", ";
	}
	out << " ]\n";

	//The output has the form [ Pointer1, Pointer2, Pointer3 ]
	return out;
}

//Overloading the ouput stream operator for the card object
ostream& operator<< (ostream& out, const Card& card) {
	out << "The card's name is " << card.cardTypeName;

	return out;
}

//Validating the index passed in the play method above
bool Card::validateIndex(vector<Card*> vector, int index) {
	if (index >= vector.size()) return false;
	return true;
}

string Card::getCardTypeName() {
	return cardTypeName;
}

int Card::enumToInt(string name) {
	if (name == "Bomb") return 0;
	if (name == "Reinforcement") return 1;
	if (name == "Blockade") return 2;
	if (name == "Airlift") return 3;

	//Diplomacy
	return 4;
}

//Default constructor
Deck::Deck() : sizeDeck(5) {
	//Since the default deck has 5 cards, and we have 5 different types of cards, we'll create 1 card of each type
	cards.push_back(new Card(Card::cardType::Bomb));
	cards.push_back(new Card(Card::cardType::Reinforcement));
	cards.push_back(new Card(Card::cardType::Blockade));
	cards.push_back(new Card(Card::cardType::Airlift));
	cards.push_back(new Card(Card::cardType::Diplomacy));
}

//Constructor accepting an integer
Deck::Deck(int number) : sizeDeck(number) {
	int numberCorrected{ number - 5 };

	//Making sure the deck has a card of each type
	cards.push_back(new Card(Card::cardType::Bomb));
	cards.push_back(new Card(Card::cardType::Reinforcement));
	cards.push_back(new Card(Card::cardType::Blockade));
	cards.push_back(new Card(Card::cardType::Airlift));
	cards.push_back(new Card(Card::cardType::Diplomacy));
	
	for (int i = 0; i < numberCorrected; i++) {

		//Random int from 0 to 4
		int typeNumber{ rand() % 4 };

		switch (typeNumber) {
		case 0:
			cards.push_back(new Card(Card::cardType::Bomb));
			break;
		case 1:
			cards.push_back(new Card(Card::cardType::Reinforcement));
			break;
		case 2:
			cards.push_back(new Card(Card::cardType::Blockade));
			break;
		case 3:
			cards.push_back(new Card(Card::cardType::Airlift));
			break;
		case 4:
			cards.push_back(new Card(Card::cardType::Diplomacy));
			break;
		}
	}
		
}

//Copy constructor
Deck::Deck(const Deck& deck) : sizeDeck(deck.sizeDeck) {
	for (int i = 0; i < deck.cards.size(); i++) {
		cards.push_back(deck.cards[i]);
	}
}

//Overloading the assignment operator
Deck& Deck::operator= (const Deck& deck) {
	this->sizeDeck = deck.sizeDeck;
	this->cards = deck.cards;

	return *this;
}

void Deck::setSize(int number) {
	sizeDeck = number;
}

int Deck::getSize() {
	return sizeDeck;
}

//Draw method that takes a card from the deck and adds it to the player's hand
Card* Deck::draw() {
	//Random int from 0 to the size of the deck
	int index{ rand() % (int)cards.size() };

	//Temporary pointer to the drawn card
	Card* cardDrawn = cards[index];

	//Removing the card from the deck
	cards.erase(cards.begin() + index);

	return cardDrawn;
}

//Adds a card to the deck
void Deck::addCard(Card* card) {
	cards.push_back(card);
	cout << "\nThe " << card->getCardTypeName() << " card has been added to the deck." << '\n';
}

//Destructor for the deck object
Deck::~Deck() {
	//Stopping the deck from resizing itself
	cards.reserve(cards.size());

	//Removing each pointer and pointing them to NULL
	for (int i = 0; i < cards.size(); i++) {
		cards[i] = NULL;
	}

	//Clearing the vector
	cards.clear();
}

//Overloading the output stream operator for the deck object
ostream& operator<< (ostream& out, const Deck& deck) {
	out << "The deck of " << deck.cards.size() << " card(s) contains " << deck.cards;

	return out;
}

//Default constructor
Hand::Hand() : maxSizeHand(3) {}

//Constructor accepting an integer
Hand::Hand(int number) : maxSizeHand(number) {}

//Copy constructor
Hand::Hand(const Hand& hand) : maxSizeHand(hand.maxSizeHand) {
	//Copying each element from the original hand to the new one
	for (int i = 0; i < hand.cardsInHand.size(); i++) {
		cardsInHand.push_back(hand.cardsInHand[i]);
	}
}

//Overloading the assignment operator
Hand& Hand::operator= (const Hand& hand) {
	this->maxSizeHand = hand.maxSizeHand;
	this->cardsInHand = hand.cardsInHand;

	return *this;
}

//Adding a card to the hand
void Hand::addHand(Card* ptrCard) {
	cardsInHand.push_back(ptrCard);
}

void Hand::setMaxSize(int number) {
	maxSizeHand = number;
}

int Hand::getMaxSize() {
	return maxSizeHand;
}

//Retrieves the card in the hand at a specified index
Card* Hand::getCardInHand(int index) {
	return cardsInHand.at(index);
}

int Hand::getSize()
{
	return cardsInHand.size();
}

//Retrieves all cards in the hand
vector<Card*> Hand::getCardsInHand() {
	return cardsInHand;
}

//Removes a card at a specified index from the hand
void Hand::removeCard(int index) {
	cardsInHand.erase(cardsInHand.begin() + index);
}

//Verifies if the hand is full or not
bool Hand::handFull() {
	if (cardsInHand.size() == maxSizeHand) {
		cout << "\nYour hand is full." << '\n';
		return true;
	}

	return false;
}

//Destructor for the hand object
Hand::~Hand() {
	//Stopping the hand from resizing itself
	cardsInHand.reserve(cardsInHand.size());

	//Removing each pointer and pointing them to NULL
	for (int i = 0; i < cardsInHand.size(); i++) {
		cardsInHand[i] = NULL;
	}

	//Clearing the vector
	cardsInHand.clear();
}

//Overloading the output stream operator for the hand object
ostream& operator<< (ostream& out, const Hand& hand) {
	out << "The hand of " << hand.cardsInHand.size() << " card(s) contains " << hand.cardsInHand;

	return out;
}