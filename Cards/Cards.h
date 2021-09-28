#pragma once
#include <string>
#include <vector>
#include <type_traits>

using namespace std;

class Card {
public:
	Card();
	void play(vector<Card*> vector, int index);
	string name;
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

private:
	int sizeDeck{};
	vector<Card*> cards;
};

class Hand {
public:
	Hand();
	vector<Card*> handDrawn(Card* ptrCard);
	void setSize(int sizeHand);
	int getSize();

private:
	int sizeHand{};
	int cardIndex{};
	vector<Card*> cardsInHand;
};