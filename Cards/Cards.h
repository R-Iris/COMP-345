#pragma once
#include <string>

using std::string;

class Deck {
    public:
        Deck();
        void shuffle();
        //Card getCard();
        void setSize(int* sizeDeck);
        int getSize();
        void draw();

    private:
        int* sizeDeck;
        string cards[5];
};

class Card {
    public:
        Card();
        string toString();
        void play();
};

// --- children of the class Card ---
class Bomb : public Card {

};

class Reinforcement : public Card {

};

class Blockade : public Card {

};

class Airlift : public Card {

};

class Diplomacy : public Card {

};
// -------------------------------

class Hand {
    public:
        Hand();
        void print() const;
        void setSize(int* sizeHand);
        int getSize();
    
    private:
        int* sizeHand;
};