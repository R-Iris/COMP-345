#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Cards.h"

using namespace std;


// Default constructor
Card::Card() {
    return;

    // Since the default deck has 5 cards, and we have 5 different types of cards, we'll create 1 card of each type
}

string Card::toString() {
}

void Card::play() {
}

Bomb::Bomb() {
    cout << "A card of type bomb has been generated." << '\n';
}

Reinforcement::Reinforcement() {
    cout << "A card of type reinforcement has been generated." << '\n';
}

Blockade::Blockade() {
    cout << "A card of type blockade has been generated." << '\n';
}

Airlift::Airlift() {
    cout << "A card of type airlift has been generated." << '\n';
}

Diplomacy::Diplomacy() {
    cout << "A card of type diplomacy has been generated." << '\n';
}

// Default constructor
Deck::Deck() {
    cout << "\nCreating a generic deck..." << '\n';
    cards[0] = {new Bomb()};
    cards[1] = {new Reinforcement()};
    cards[2] = {new Blockade()};
    cards[3] = {new Airlift()};
    cards[4] = {new Diplomacy()};

    cout << "The generated deck has " << 5 << " cards." << '\n' ;
}
/*
void Deck::shuffle() {

}

Card Deck::getCard() {

}
*/
void Deck::setSize(int number) {
    sizeDeck = number; // sets the number of cards in the deck
}

int Deck::getSize() {
    return sizeDeck;
}

void Deck::draw() {
    srand(time(NULL)); // regenerates the seed for the rand() call below
    int index = rand() % 5; // index in the range of 0 and 4
    //int* ptrIndex{&index};
    cout << "\nYou picked the " << index + 1 << " nth card from the deck." << '\n';
    Card* cardDrawn = cards[index];

    // removing the card from the deck array by copying everything from cards[index + 1] to the end of the array, one element to the left
    for (int i = index + 1; i < 5; i++) {
        cards[i - 1] = cards[i];
    }

    /* ----
    HERE GOES CODE TO ADD TO THE HAND
    --- */
}

Hand::Hand() {
    cout << "\nCreating the player's hand..." << '\n';
}
/*
void Hand::print() const{

}
*/
void Hand::setSize(int number) {
    sizeHand = number; // sets the number of cards in the player's hand
}

int Hand::getSize() {
    return sizeHand;
}
