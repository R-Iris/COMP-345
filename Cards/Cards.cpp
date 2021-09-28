#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include "Cards.h"

using namespace std;

// Default constructor
Card::Card() : name("No name"), card(NULL) {
	return;
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

Card* Card::play(vector<Card*> vector, int index) {
	if (!validateIndex(vector, index)) {
		cout << "\nYour hand only contains " << vector.size() << " cards. The index you entered is invalid. Terminating program." << '\n';
		exit(1);
	}

	cout << "\nThe " << vector[index]->name << " card has been played." << '\n';
	card = vector[index];
	vector.erase(vector.begin() + index); // Removing the card from the hand

	cout << "You have the following cards in your hand: " << vector;

	return card;
}

bool Card::validateIndex(vector<Card*> vector, int index) {
	if (index >= vector.size()) return false; // Actually returns 0
	return true; // Actually returns 1
}

Bomb::Bomb() {
	name = "Bomb";
}

Reinforcement::Reinforcement() {
	name = "Reinforcement";
}

Blockade::Blockade() {
	name = "Blockade";
}

Airlift::Airlift() {
	name = "Airlift";
}

Diplomacy::Diplomacy() {
	name = "Diplomacy";
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

	cout << "The generated deck has " << cards.size() << " cards." << '\n';
	cout << cards;
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

	//--------------------- THIS PORTION IS JUST FOR TESTING ---------------------------------------

	cards.erase(cards.begin() + index);

	cout << "The deck has " << cards.size() << " cards in it." << '\n';

	cout << cards;
	//----------------------------------------------------------------------------------------------

	return cardDrawn;
}

void Deck::addCard(Card* card) {
	cards.push_back(card);
	cout << "\nThe " << card->name << " has been added to the deck." << '\n';
	cout << "Cards in the deck: " << cards;
}

// Default constructor
Hand::Hand() : sizeHand(3) {
	cout << "\nCreating the player's hand..." << '\n';
}


vector<Card*> Hand::handDrawn(Card* ptrCard) {
	cardsInHand.push_back(ptrCard);

	cout << "\nYou have " << cardsInHand.size() << " card(s) in your hand." << '\n';
	cout << "The following cards are in your hand: " << cardsInHand;

	return cardsInHand;
}

void Hand::setSize(int number) {
	sizeHand = number; // sets the number of cards in the player's hand
}

int Hand::getSize() {
	return sizeHand;
}