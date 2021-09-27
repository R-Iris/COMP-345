#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include "Cards.h"

using namespace std;

// Default constructor
Card::Card() : name("No name") {
    // Since the default deck has 5 cards, and we have 5 different types of cards, we'll create 1 card of each type
}

void Card::play() {
}

Bomb::Bomb() {
    name = "Bomb";
    cout << "A card of type bomb has been generated." << '\n';
}

Reinforcement::Reinforcement() {
    name = "Reinforcement";
    cout << "A card of type reinforcement has been generated." << '\n';
}

Blockade::Blockade() {
    name = "Blockade";
    cout << "A card of type blockade has been generated." << '\n';
}

Airlift::Airlift() {
    name = "Airlift";
    cout << "A card of type airlift has been generated." << '\n';
}

Diplomacy::Diplomacy() {
    name = "Diplomacy";
    cout << "A card of type diplomacy has been generated." << '\n';
}

// Default constructor
Deck::Deck() {
    cout << "\nCreating a generic deck..." << '\n';
    names.push_back("Bomb");
    names.push_back("Reinforcement");
    names.push_back("Blockade");
    names.push_back("Airlift");
    names.push_back("Diplomacy");
    cards.push_back(new Bomb());
    cards.push_back(new Reinforcement());
    cards.push_back(new Blockade());
    cards.push_back(new Airlift());
    cards.push_back(new Diplomacy());

    cout << "The generated deck has " << cards.size() << " cards." << '\n' ;
}

void Deck::setSize(int number) {
    sizeDeck = number; // sets the number of cards in the deck
}

int Deck::getSize() {
    return sizeDeck;
}

Card* Deck::draw() {
    int index{rand() % (int)cards.size()}; // index in the range of 0 and 4
    cout << "\nYou picked the " << index + 1 << " nth card from the deck." << '\n';
    Card* cardDrawn = cards[index];
    //string cardName = names[index];

    //--------------------- THIS PORTION IS JUST FOR TESTING ---------------------------------------

    cards.erase(cards.begin() + index);
    names.erase(names.begin() + index);

    cout << "The deck has " << cards.size() << " cards in it." << '\n';

    cout << "The cards left in the deck are..." << '\n';
    for (string element : names) cout << element << '\n';
    //----------------------------------------------------------------------------------------------

    return cardDrawn;
}

Hand::Hand() {
    sizeHand = 3;
    cout << "\nCreating the player's hand..." << '\n';
}

void Hand::handDrawn(Card* ptrCard) {
    cardsInHand.push_back(ptrCard);

    cout << "\nYou have " << cardsInHand.size() << " cards in your hand." << '\n';
    cout << "You have the following cards in your hand: " << '\n';

    for (vector<Card*>::iterator i = cardsInHand.begin(); i != cardsInHand.end(); ++i) {
        cout << (*i)->name << '\n';
    }
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
