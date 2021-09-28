#pragma once
#include <string>
#include <vector>
#include <type_traits>

using namespace std;

class Card {
public:
	Card();
	void play(class Hand*, int, class Deck*);
	bool validateIndex(vector<Card*>, int);
	string name;

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
	void addHand(Card*);
	Card* getCardInHand(int);
	void setSize(int);
	int getSize();
	vector<Card*> getHand();
	void removeHand(int);
	bool handFull();

	friend ostream& operator<< (ostream&, const vector<Card*>);

private:
	int sizeHand{};
	vector<Card*> cardsInHand;
};