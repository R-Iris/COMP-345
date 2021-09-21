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
    srand(time(NULL)); // regenerates the seed for the rand() call below
    sizeDeck = 5;
    cout << "\nCreating a generic deck..." << '\n';
    cards[0] = {new Bomb()};
    cards[1] = {new Reinforcement()};
    cards[2] = {new Blockade()};
    cards[3] = {new Airlift()};
    cards[4] = {new Diplomacy()};

    cout << "The generated deck has " << sizeDeck << " cards." << '\n' ;
}
/*

Card Deck::getCard() {

}
*/
void Deck::setSize(int number) {
    sizeDeck = number; // sets the number of cards in the deck
}

int Deck::getSize() {
    return sizeDeck;
}

Card* Deck::draw() {
    int index{rand() % sizeDeck}; // index in the range of 0 and 4
    //int* ptrIndex{&index};
    cout << "\nYou picked the " << index + 1 << " nth card from the deck." << '\n';
    Card* cardDrawn = cards[index];

    //--------------------- THIS PORTION IS JUST FOR TESTING ---------------------------------------
    string names[sizeDeck] = {"Bomb", "Reinforcement", "Blockade", "Airlift", "Diplomacy"};

    // removing the card from the deck array by copying everything from cards[index + 1] to the end of the array, one element to the left
    for (int i = index + 1; i < sizeDeck; i++) {
        cards[i - 1] = cards[i]; // the issue is that the end of the array won't be automatically set to null
        names[i - 1] = names[i];
    }

    sizeDeck--; // to get rid of the previous issue, we shorten the size of the array by 1

    cout << "The cards left in the deck are..." << '\n';
    for (int j = 0; j < sizeDeck; j ++) {
        cout << names[j] << '\n';
    }
    //----------------------------------------------------------------------------------------------

    return cardDrawn;
}

Hand::Hand() {
    sizeHand = 3;
    cout << "\nCreating the player's hand..." << '\n';
}

void Hand::hand(Card* ptrCard) {
    int cardIndex{};
    cardsInHand[cardIndex] = ptrCard;
    cardIndex++;

    cout << "You have " << cardIndex << " cards in your hand." << '\n';
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
