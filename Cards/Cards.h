#pragma once
#include <string>
#include <vector>
#include <type_traits>

#include "../Player/Player.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Game Engine/GameEngine.h"

using namespace std;

// Forward declaration
class Player;
class Territory;
class OrdersList;
class GameEngine;

class Card {
public:
	enum class cardType { Bomb, Reinforcement, Blockade, Airlift, Diplomacy };
	Card();
	Card(cardType);
	Card(const Card&);
	Card& operator= (const Card&);
	virtual void play(class Hand*, int, class Deck*, Player*,Player*, OrdersList*, Territory*, Territory*,GameEngine* gameEngine);
	bool validateIndex(vector<Card*>, int);
	string getCardTypeName();
	int enumToInt(string);

	//Output stream operator for vectors containing pointers to card objects
	friend ostream& operator<< (ostream&, const vector<Card*>);

	//Output stream operator for objects of type card
	friend ostream& operator<< (ostream&, const Card&);

private:
	string cardTypeName;
};

class Deck {
public:
	Deck();
	Deck(int);
	Deck(const Deck&);
	Deck& operator= (const Deck&);
	void setSize(int sizeDeck);
	int getSize();
	Card* draw();
	void addCard(Card* card);
	~Deck();

	friend ostream& operator<< (ostream&, const vector<Card*>);

	//Output stream operator for a deck object
	friend ostream& operator<< (ostream&, const Deck&);

private:
	int sizeDeck{};
	vector<Card*> cards;
};

class Hand {
public:
	Hand();
	Hand(int);
	Hand(const Hand&);
	Hand& operator= (const Hand&);
	void addHand(Card*);
	Card* getCardInHand(int);
	int getSize();
	void setMaxSize(int);
	int getMaxSize();
	vector<Card*> getCardsInHand();
	//Change name of this
	void removeCard(int);
	bool handFull();
	~Hand();

	friend ostream& operator<< (ostream&, const vector<Card*>);

	//Output stream operator for a hand object
	friend ostream& operator<< (ostream&, const Hand&);

private:
	int maxSizeHand;
	vector<Card*> cardsInHand;
};