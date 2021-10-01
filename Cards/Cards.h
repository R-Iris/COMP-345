#pragma once
#include <string>
#include <vector>
#include <type_traits>

using namespace std;

class Card {
public:
	Card();
	Card(const Card*);
	Card& operator= (const Card&);
	virtual void play(class Hand*, int, class Deck*, class Player*);
	bool validateIndex(vector<Card*>, int);
	string name;

	//Output stream operator for vectors
	friend ostream& operator<< (ostream&, const vector<Card*>);

	//Output stream operator for cards
	friend ostream& operator<< (ostream&, const Card&);
};

// --- children of the class Card, each with their respective constructors ---
class Bomb : public Card {
public:
	Bomb();
	void play(Hand*, int, Deck*, class Player*);
};

class Reinforcement : public Card {
public:
	Reinforcement();
	void play(Hand*, int, Deck*, class Player*);
};

class Blockade : public Card {
public:
	Blockade();
	void play(Hand*, int, Deck*, class Player*);
};

class Airlift : public Card {
public:
	Airlift();
	void play(Hand*, int, Deck*, class Player*);
};

class Diplomacy : public Card {
public:
	Diplomacy();
	void play(Hand*, int, Deck*, class Player*);
};
// -------------------------------

class Deck {
public:
	Deck();
	Deck(const Deck&);
	Deck& operator= (const Deck&);
	void setSize(int sizeDeck);
	int getSize();
	Card* draw();
	void addCard(Card* card);

	//Output stream operator for vectors
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
	Hand(const Hand&);
	Hand& operator= (const Hand&);
	void addHand(Card*);
	Card* getCardInHand(int);
	void setSize(int);
	int getSize();
	vector<Card*> getHand();
	void removeHand(int);
	bool handFull();

	//Output stream operator for vectors
	friend ostream& operator<< (ostream&, const vector<Card*>);

	//Output stream operator for a hand object
	friend ostream& operator<< (ostream&, const Hand&);

private:
	int sizeHand{};
	vector<Card*> cardsInHand;
};


//--- The following classes are only for the implementation of Assignemnt 1, they'll be removed in the future --- 
class Player {
public:
	Player();
	void issueOrder(class Order*);
	vector<class Order*> getOrders();

private:
	string name;
	vector<class Order*> orders;
};

class Order {
public:
	Order(string);

	//Output stream operator for vectors
	friend ostream& operator<< (ostream&, const vector<Order*>);

private:
	string name;
};