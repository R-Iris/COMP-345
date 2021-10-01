#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include "Cards.h"

using namespace std;

// Default constructor
Card::Card() : name("No name") { }

Card::Card(const Card* card) : name(card->name) { }

Card& Card::operator= (const Card& card) {
	this->name = card.name;

	return *this;
}

void Card::play(Hand* hand, int index, Deck* deck, Player* player) {
	if (!validateIndex(hand->getHand(), index)) {
		cout << "\nYour hand only contains " << hand->getHand().size() << " cards. The index you entered is invalid. Terminating program." << '\n';
		exit(1);
	}

	Card* playedCard = hand->getCardInHand(index);
	cout << "\nThe " << playedCard->name << " card has been played." << '\n';

	hand->getCardInHand(index)->play(hand, index, deck, player); // calling the child's play method

	hand->removeHand(index); // removes card played from the hand
	deck->addCard(playedCard); // adds the card played to the deck
}

ostream& operator<< (ostream& out, const vector<Card*> cards) {
	out << "[ ";
	for (int i = 0; i < cards.size(); i++) {
		out << cards[i]->name;
		if (i != cards.size() - 1) out << ", ";
	}
	out << " ]\n";

	return out;
}

ostream& operator<< (ostream& out, const Card& card) {
	out << "The card's name is " << card.name;

	return out;
}

bool Card::validateIndex(vector<Card*> vector, int index) {
	if (index >= vector.size()) return false; // Actually returns 0
	return true; // Actually returns 1
}

Bomb::Bomb() { name = "Bomb"; }

void Bomb::play(Hand* hand, int index, Deck* deck, Player* player) {
	Order* order = new Order("Bomb");
	player->issueOrder(order);
}

Reinforcement::Reinforcement() { name = "Reinforcement"; }

void Reinforcement::play(Hand* hand, int index, Deck* deck, Player* player) {
	Order* order = new Order("Reinforcement");
	player->issueOrder(order);
}

Blockade::Blockade() { name = "Blockade"; }

void Blockade::play(Hand* hand, int index, Deck* deck, Player* player) {
	Order* order = new Order("Blockade");
	player->issueOrder(order);
}

Airlift::Airlift() { name = "Airlift"; }

void Airlift::play(Hand* hand, int index, Deck* deck, Player* player) {
	Order* order = new Order("Airlift");
	player->issueOrder(order);
}

Diplomacy::Diplomacy() { name = "Diplomacy"; }

void Diplomacy::play(Hand* hand, int index, Deck* deck, Player* player) {
	Order* order = new Order("Diplomacy");
	player->issueOrder(order);
}

// Default constructor
Deck::Deck() : sizeDeck(5) {
	cout << "\nCreating a generic deck..." << '\n';

	// Since the default deck has 5 cards, and we have 5 different types of cards, we'll create 1 card of each type
	cards.push_back(new Bomb());
	cards.push_back(new Reinforcement());
	cards.push_back(new Blockade());
	cards.push_back(new Airlift());
	cards.push_back(new Diplomacy());
}

Deck::Deck(const Deck& deck) : sizeDeck(deck.sizeDeck) {
	for (int i = 0; i < deck.cards.size(); i++) {
		cards.push_back(deck.cards[i]);
	}
}

Deck& Deck::operator= (const Deck& deck) {
	this->sizeDeck = deck.sizeDeck;
	this->cards = deck.cards;

	return *this;
}

void Deck::setSize(int number) {
	sizeDeck = number; // sets the number of cards in the deck
}

int Deck::getSize() {
	return sizeDeck;
}

Card* Deck::draw() {
	int index{ rand() % (int)cards.size() }; // index in the range of 0 and 4
	cout << "\nYou picked the " << index + 1 << " nth card from the deck." << '\n';
	Card* cardDrawn = cards[index];

	cards.erase(cards.begin() + index);

	return cardDrawn;
}

void Deck::addCard(Card* card) {
	cards.push_back(card);
	cout << "\nThe " << card->name << " card has been added to the deck." << '\n';
}

ostream& operator<< (ostream& out, const Deck& deck) {
	out << "The deck of " << deck.cards.size() << " card(s) contains " << deck.cards;

	return out;
}

// Default constructor
Hand::Hand() : sizeHand(3) {
	cout << "\nCreating the player's hand..." << '\n';
}

Hand::Hand(const Hand& hand) : sizeHand(hand.sizeHand) {
	for (int i = 0; i < hand.cardsInHand.size(); i++) {
		cardsInHand.push_back(hand.cardsInHand[i]);
	}
}

Hand& Hand::operator= (const Hand& hand) {
	this->sizeHand = hand.sizeHand;
	this->cardsInHand = hand.cardsInHand;

	return *this;
}

void Hand::addHand(Card* ptrCard) {
	cardsInHand.push_back(ptrCard);
}

void Hand::setSize(int number) {
	sizeHand = number; // sets the number of cards in the player's hand
}

int Hand::getSize() {
	return sizeHand;
}

Card* Hand::getCardInHand(int index) {
	return cardsInHand.at(index);
}

vector<Card*> Hand::getHand() {
	return cardsInHand;
}

void Hand::removeHand(int index) {
	cardsInHand.erase(cardsInHand.begin() + index);
}

bool Hand::handFull() {
	if (cardsInHand.size() >= sizeHand) {
		cout << "Your hand is full." << '\n';
		return true;
	}

	return false;
}

ostream& operator<< (ostream& out, const Hand& hand) {
	out << "The hand of " << hand.cardsInHand.size() << " card(s) contains " << hand.cardsInHand;

	return out;
}


//--- The following methods are only for the implementation of Assignemnt 1, they'll be removed in the future ---
Player::Player() : name("Default player") { }

void Player::issueOrder(Order* order) {
	orders.push_back(order);
}

vector<Order*> Player::getOrders() {
	return orders;
}

Order::Order(string name) : name(name) {
	cout << "The " << name << " order has been initiated.";
}

ostream& operator<< (ostream& out, const vector<Order*> orders) {
	out << "[ ";
	for (int i = 0; i < orders.size(); i++) {
		out << orders[i]->name;
		if (i != orders.size() - 1) out << ", ";
	}
	out << " ]\n";

	return out;
}