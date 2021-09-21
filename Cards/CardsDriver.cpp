#include <iostream>
#include "Cards.h"

using namespace std;

int main() {
    //int numberDeck{};
    int numberHand{};

    cout << "This file is just for testing at the moment." << '\n';

    Deck deck; // create an object deck
    Hand hand; // create an object hand
    /*
    cout << "Enter how many cards you wish to have in your deck. The integer must be between 15 and 25: ";
    cin >> numberDeck;
    while ((numberDeck < 15) || numberDeck > 25) {
        cout << "Please enter an integer between 15 and 25: ";
        cin >> numberDeck;
    }
    deck.setSize(ptrDeck);
    */
    cout << "Enter how many cards you wish to have in your hand. The integer must be between 2 and 3: ";
    cin >> numberHand;
    while ((numberHand < 2) || numberHand > 3)
    {
        cout << "Please enter an integer between 2 and 3: ";
        cin >> numberHand;
    }
    hand.setSize(numberHand);

    cout << "# of cards your hand can hold: " << hand.getSize() << '\n';

    deck.draw();

    return 0;
}