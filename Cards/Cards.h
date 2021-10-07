#pragma once
#include <string>
#include <vector>
#include <type_traits>

using namespace std;

class Card {
public:
	enum class cardType { Bomb, Reinforcement, Blockade, Airlift, Diplomacy };
	Card();
	Card(cardType);
	Card(const Card&);
	Card& operator= (const Card&);
	virtual void play(class Hand*, int, class Deck*, class Player*);
	bool validateIndex(vector<Card*>, int);
	string getCardTypeName();

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
	void setSize(int);
	int getSize();
	vector<Card*> getHand();
	void removeHand(int);
	bool handFull();
	~Hand();

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
	~Player();

private:
	string name;
	vector<class Order*> orders;
};

class Order {
public:
	Order(string);

	//Output stream operator for vectors containing pointers to order objects
	friend ostream& operator<< (ostream&, const vector<Order*>);

private:
	string name;
};