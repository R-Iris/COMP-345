#include <iostream>
#include "Cards.h"

using namespace std;

int main() {
    int numberDeck{};
    int numberHand{};

    int* ptrDeck{&numberDeck}; // pointer to numberDeck
    int* ptrHand{&numberHand}; // pointer to numberHand

    cout << "This file is just for testing at the moment." << '\n';

    Deck deck; // create an object deck
    Hand hand; // create an object hand

    cout << "Enter how many cards you wish to have in your deck. The integer must be between 15 and 25: ";
    cin >> numberDeck;
    while ((numberDeck < 15) || numberDeck > 25) {
        cout << "Please enter an integer between 15 and 25: ";
        cin >> numberDeck;
    }
    deck.setSize(ptrDeck);

    cout << "Enter how many cards you wish to have in your hand. The integer must be between 5 and 7: ";
    cin >> numberHand;
    while ((numberHand < 5) || numberHand > 7)
    {
        cout << "Please enter an integer between 5 and 7: ";
        cin >> numberHand;
    }
    hand.setSize(ptrHand);


    cout << "# of cards in the deck: " << deck.getSize() << '\n';
    cout << "# of cards in your hand: " << hand.getSize() << '\n';

    return 0;
}