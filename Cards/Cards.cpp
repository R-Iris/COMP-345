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
Card::Card(const Card* card) : cardTypeName(card->cardTypeName) { }

//Overloading the assignment operator
Card& Card::operator= (const Card& card) {
	this->cardTypeName = card.cardTypeName;

	return *this;
}

//Play method that is inherited by all children of the card class. It takes a card from the player's hand, creates an order and puts the card back into the deck.
void Card::play(Hand* hand, int index, Deck* deck, Player* player) {
	//Validating that the index the user inputted is correct
	if (!validateIndex(hand->getHand(), index)) {
		cout << "\nYour hand only contains " << hand->getHand().size() << " cards. The index you entered is invalid. Terminating program." << '\n';
		exit(1);
	}

	//Temporary pointer to the card played
	Card* playedCard = hand->getCardInHand(index);
	cout << "\nThe " << playedCard->cardTypeName << " card has been played." << '\n';

	//Creates a pointer to an order of the card's type
	Order* order = new Order(hand->getCardInHand(index)->getCardTypeName());

	//Adds the order to the player's list of orders
	player->issueOrder(order);

	//Removes card played from the hand
	hand->removeHand(index);

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

//Default constructor
Deck::Deck() : sizeDeck(5) {
	cout << "\nCreating a generic deck..." << '\n';

	//Since the default deck has 5 cards, and we have 5 different types of cards, we'll create 1 card of each type
	cards.push_back(new Card(Card::cardType::Bomb));
	cards.push_back(new Card(Card::cardType::Reinforcement));
	cards.push_back(new Card(Card::cardType::Blockade));
	cards.push_back(new Card(Card::cardType::Airlift));
	cards.push_back(new Card(Card::cardType::Diplomacy));
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
	cout << "\nYou picked the " << index + 1 << " nth card from the deck." << '\n';

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

/*
//Destructor for the deck object
Deck::~Deck() {
	//Removing each pointer and pointing them to NULL
	for (int i = 0; i < cards.size(); i++) {
		delete cards[i];
		cards[i] = NULL;
	}

	//Clearing the vector
	cards.clear();
}*/

//Overloading the output stream operator for the deck object
ostream& operator<< (ostream& out, const Deck& deck) {
	out << "The deck of " << deck.cards.size() << " card(s) contains " << deck.cards;

	return out;
}

//Default constructor
Hand::Hand() : sizeHand(3) {
	cout << "\nCreating the player's hand..." << '\n';
}

//Copy constructor
Hand::Hand(const Hand& hand) : sizeHand(hand.sizeHand) {
	//Copying each element from the original hand to the new one
	for (int i = 0; i < hand.cardsInHand.size(); i++) {
		cardsInHand.push_back(hand.cardsInHand[i]);
	}
}

//Overloading the assignment operator
Hand& Hand::operator= (const Hand& hand) {
	this->sizeHand = hand.sizeHand;
	this->cardsInHand = hand.cardsInHand;

	return *this;
}

//Adding a card to the hand
void Hand::addHand(Card* ptrCard) {
	cardsInHand.push_back(ptrCard);
}

void Hand::setSize(int number) {
	sizeHand = number;
}

int Hand::getSize() {
	return sizeHand;
}

//Retrieves the card in the hand at a specified index
Card* Hand::getCardInHand(int index) {
	return cardsInHand.at(index);
}

//Retrieves all cards in the hand
vector<Card*> Hand::getHand() {
	return cardsInHand;
}

//Removes a card at a specified index from the hand
void Hand::removeHand(int index) {
	cardsInHand.erase(cardsInHand.begin() + index);
}

//Verifies if the hand is full or not
bool Hand::handFull() {
	if (cardsInHand.size() >= sizeHand) {
		cout << "Your hand is full." << '\n';
		return true;
	}

	return false;
}

/*
//Destructor for the hand object
Hand::~Hand() {
	//Removing each pointer and pointing them to NULL
	for (int i = 0; i < cardsInHand.size(); i++) {
		delete cardsInHand[i];
		cardsInHand[i] = NULL;
	}

	//Clearing the vector
	cardsInHand.clear();
}*/

//Overloading the output stream operator for the hand object
ostream& operator<< (ostream& out, const Hand& hand) {
	out << "The hand of " << hand.cardsInHand.size() << " card(s) contains " << hand.cardsInHand;

	return out;
}

//--- The following methods are only for the implementation of Assignemnt 1, they'll be removed in the future ---
Player::Player() : name("Default player") { }

//Adds the order to the player's list of orders
void Player::issueOrder(Order* order) {
	orders.push_back(order);
}

//Retrieves the list of orders
vector<Order*> Player::getOrders() {
	return orders;
}

/*
//Destructor for the player object
Player::~Player() {
	//Removing each pointer and pointing them to NULL
	for (int i = 0; i < orders.size(); i++) {
		delete orders[i];
		orders[i] = NULL;
	}

	//Clearing the vector
	orders.clear();
}*/

Order::Order(string name) : name(name) {
	cout << "The " << name << " order has been initiated.";
}

//Overloading the output stream for vectors containing pointers to order objects
ostream& operator<< (ostream& out, const vector<Order*> orders) {
	out << "[ ";
	for (int i = 0; i < orders.size(); i++) {
		out << orders[i]->name;
		if (i != orders.size() - 1) out << ", ";
	}
	out << " ]\n";

	//The output has the form [ Pointer1, Pointer2, Pointer3 ]
	return out;
}