#include <iostream>
#include <stdlib.h>
#include "Cards.h"

using namespace std;

//cards = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};

Deck::Deck() {
    cout << "Creating a deck..." << '\n';
}
/*
void Deck::shuffle() {

}

Card Deck::getCard() {

}
*/
void Deck::setSize(int* number) {
    sizeDeck = number; // sets the number of cards in the deck
}

int Deck::getSize() {
    return *sizeDeck;
}
/*
void Deck::draw() {

}

Card::Card() {

}

string Card::toString() {

}

void Card::play() {
    
}
*/

Hand::Hand() {
    cout << "Creating the player's hand..." << '\n';
}
/*
void Hand::print() const{

}
*/
void Hand::setSize(int* number) {
    sizeHand = number; // sets the number of cards in the player's hand
}

int Hand::getSize() {
    return *sizeHand;
}
