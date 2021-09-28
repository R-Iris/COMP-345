#pragma once
#include <string>
#include <vector>
#include <type_traits>

using namespace std;

class Card {
public:
	Card();
	Card* play(vector<Card*>, int);
	bool validateIndex(vector<Card*>, int);
	string name;

private:
	Card* card;

	friend ostream& operator<< (ostream&, const vector<Card*>);
};

// --- children of the class Card, each with their respective constructors ---
class Bomb : public Card {
public:
	Bomb();
};

class Reinforcement : public Card {
public:
	Reinforcement();
};

class Blockade : public Card {
public:
	Blockade();
};

class Airlift : public Card {
public:
	Airlift();
};

class Diplomacy : public Card {
public:
	Diplomacy();
};
// -------------------------------

class Deck {
public:
	Deck();
	void setSize(int sizeDeck);
	int getSize();
	Card* draw();
	void addCard(Card* card);

	friend ostream& operator<< (ostream&, const vector<Card*>);

private:
	int sizeDeck{};
	vector<Card*> cards;
};

class Hand {
public:
	Hand();
	string toString();
	vector<Card*> handDrawn(Card*);
	void setSize(int);
	int getSize();

	friend ostream& operator<< (ostream&, const vector<Card*>);

private:
	int sizeHand{};
	int cardIndex{};
	vector<Card*> cardsInHand;
};