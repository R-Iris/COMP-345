#include "PlayerStrategies.h" // Include header file

// Gets the pointer pointing to the player
Player* PlayerStrategy::getPlayer()
{
	return p;
}

// Sets the player attributed to the strategy
void PlayerStrategy::setPlayer(Player* player)
{
	p = player;
}

// Default parametrized constructor
PlayerStrategy::PlayerStrategy(Player* player, strategyName strategyName) : p(player), strN(strategyName) { }

// Copy constructor
PlayerStrategy::PlayerStrategy(const PlayerStrategy& ps) : p(ps.p), strN(ps.strN) { }

// Overloading the assignment operator
PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& ps)
{
	p = ps.p;
	strN = ps.strN;
	return *this;
}

// Overloading the output stream operator for the PlayerStrategy
ostream& operator<<(ostream& out, const PlayerStrategy&)
{
	return out << "Abstract Player Strategy";
}

// Overloading the output stream operator for the HumanPlayerStrategy
ostream& operator<<(ostream& out, const HumanPlayerStrategy&)
{
	return out << "Human Player Strategy";
}

// Default constructor
HumanPlayerStrategy::HumanPlayerStrategy(Player* player) : PlayerStrategy(player, Human) { }

// Copy constructor
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& hps) : PlayerStrategy(hps) { }

// Overloading the assignment operator
HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy& hps)
{
	p = hps.p;
	strN = hps.strN;
	return *this;
}

// The human player issues its orders through the three phases (deploy, advance, cards)
void HumanPlayerStrategy::issueOrder()
{
	GameEngine* game = p->getGameEngine();
	Hand* hand = p->getHand();
	Deck* deck = game->getDeck();
	OrdersList* orders = p->getOrdersList();

	// Introduction message for each player
	cout << "\nIssuing orders for player " << p->getName() << ":" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

	cout << "#--- Deploying Phase ---#" << endl;

	// Prints out the list of territories to defend
	cout << "\nTerritories to defend: (Index : Name)" << endl;
	for (auto it : toDefend()) {
		cout << it->getIndex() << " : " + it->getName() << " , Armies: " << it->getNumberOfArmies() << endl;
	}
	cout << endl;

	// While the player still has armies to deploy (reinforcement pool is not empty)
	while (p->getReinforcementPool() > 0) {

		// Announce how big the reinforcement pool is
		cout << "Player " << p->getName() << "'s number of armies left in the reinforcement pool: " << p->getReinforcementPool() << endl << endl;

		// Prompt the user to choose index of territory to defend
		cout << "Input the index of the defending territory you want to deploy armies to: ";
		int tIndex;
		cin >> tIndex;
		cout << endl;

		// If player owns territory (found by index)
		if (p->ownsTerritory(tIndex)) {

			// Prompt the user to input number of armies to deploy
			cout << "Input how many armies you wish to deploy to that territory: ";
			int deployNo;
			cin >> deployNo;
			cout << endl;

			// If the user enters a number that is less than the total number of armies in the reinforcement pool 
			if (deployNo <= p->getReinforcementPool()) {

				// Negative input
				if (deployNo <= 0) {
					cout << "Cannot input a negative number!" << endl;
				}

				// Non-negative input that is less or equal to number of armies available
				else {

					// Add a deploy order to the player's list of orders
					orders->addOrders(new Deploy(p, deployNo, game->getMap()->getTerritoryByIndex(tIndex), game));
					
					// Sets the reinforcement pool with whatever is left after the user's input
					p->setReinforcementPool(p->getReinforcementPool() - deployNo);
					cout << deployNo << " armies will been deployed!" << endl;
				}
			}

			// If the user's input is bigger than the reinforcement pool
			else {
				cout << "Insufficient number of armies available in reinforcement pool, you can deploy at most " << p->getReinforcementPool() << " armies!" << endl;
			}
		}

		// If player does not own territory or it does not exist
		else {
			cout << "Wrong input: You do not own this territory or it does not exist" << endl;
		}
	}

	cout << "\n#--- Deploying Phase OVER ---#" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

	// All deploy orders have been issued at this point!

	// Now issuing advance orders
	cout << "\n#--- Advancing Phase ---#" << endl;

	// Advance orders are optional, ask user whether they want to issue any
	cout << "Do you wish to issue any advance orders?" << endl
		<< "Reply with \"y\" if you wish to do so, any other input will be assumed to be a no : ";

	string answer;
	cin >> answer;
	cout << endl;

	// "y" as input for yes
	while (answer == "y") {

		// Two options to choose from
		cout << "Do you wish to :" << endl;
		cout << "1. (DEFENSE) : Move armies from their own territories to defend another?" << endl;
		cout << "OR" << endl;
		cout << "2. (ATTACK) : Move armies from their own territories to a neighboring enemy territory to attack?" << endl;
		cout << "Reply with either number 1 or 2 : ";
		int ans;
		cin >> ans;
		cout << endl;

		// Option 1 (DEFENSE)
		if (ans == 1) {

			// List of territories to defend
			cout << "\nTerritories to defend: (Index : Name)" << endl;
			for (auto it : toDefend()) {
				cout << it->getIndex() << " : " + it->getName() << " , Armies: " << it->getNumberOfArmies() << endl;
			}
			cout << endl;

			// Accept input for source territory's index (where armies originate)
			cout << "Input the souce territory's index: ";
			int sourceIndex;
			cin >> sourceIndex;
			cout << endl;

			// Check if player owns this territory or if it doesn't exist
			if (p->ownsTerritory(sourceIndex)) {
				// Accept input for target territory's index (where armies go to)
				cout << "Input the target territory's index: ";
				int targetIndex;
				cin >> targetIndex;
				cout << endl;

				// Check if player owns this territory or if it doesn't exist
				if (p->ownsTerritory(targetIndex)) {
					// Accept input for number of armies to move
					cout << "Finally, input the number of armies you wish to move: ";
					int army;
					cin >> army;
					cout << endl;

					// Convert the territory index's to territory pointers
					Territory* source = game->getMap()->getTerritoryByIndex(sourceIndex);
					Territory* target = game->getMap()->getTerritoryByIndex(targetIndex);

					// Check if input is valid (source territory has enough armies)
					if (army <= source->getNumberOfArmies()) {
						cout << "Advancing from " << source->getName() << " to "
							<< target->getName() << " " << army << " armies!" << endl;

						// Adds the advance order to the player's list of order
						orders->addOrders(new Advance(p, army, source, target, game));
					}

					// Input number of armies to move is bigger than number of armies in source territory
					else {
						cout << "Wrong input: You do not have this many armies in the source territory!" << endl;
					}
				}

				// Player does not own this territory or it does not exist
				else {
					cout << "Wrong input: You do not own this territory or it does not exist!" << endl;
				}
			}

			// Player does not own this territory or it does not exist
			else {
				cout << "Wrong input: You do not own this territory or it does not exist!" << endl;
			}
		}

		// Option 2 (ATTACK)
		else if (ans == 2) {
			// List of territories to defend
			cout << "\nTerritories to defend: (Index : Name)" << endl;
			for (auto it : toDefend()) {
				cout << it->getIndex() << " : " + it->getName() << " , Armies: " << it->getNumberOfArmies() << endl;
			}
			cout << endl;

			// List of territories to attack
			cout << "\nTerritories to attack: (Index : Name)" << endl;
			for (auto it : toAttack()) {
				cout << it->getIndex() << " : " + it->getName() << " , Armies: " << it->getNumberOfArmies() << endl;
			}
			cout << endl;

			// Accept input for source territory's index (where armies originate)
			cout << "Input the souce territory's index: ";
			int sourceIndex;
			cin >> sourceIndex;
			cout << endl;

			// Check if player owns this territory or if it doesn't exist
			if (p->ownsTerritory(sourceIndex)) {
				// Accept input for target territory's index (where armies go to)
				cout << "Input the target territory's index: ";
				int targetIndex;
				cin >> targetIndex;
				cout << endl;

				// Convert source and targert territories from index to a territory pointer
				Territory* source = game->getMap()->getTerritoryByIndex(sourceIndex);
				Territory* target = game->getMap()->getTerritoryByIndex(targetIndex);

				// Check if target is adjacent to any of the player's owned territories
				bool targetCanBeAttacked = false;
				for (auto it : toAttack()) {
					if (it == target) {
						targetCanBeAttacked = true;
					}
				}

				// If the target territory can be attacked
				if (targetCanBeAttacked) {
					// Accept input for number of armies to move
					cout << "Finally, input the number of armies you wish to move: ";
					int army;
					cin >> army;
					cout << endl;

					// Check if input is valid (source territory has enough armies)
					if (army <= source->getNumberOfArmies()) {
						cout << "Advancing from " << source->getName() << " to "
							<< target->getName() << " " << army << " armies!" << endl;

						//Takes care of what happens if diplomacy was used last turn
						Advance* advance = new Advance(p, army, source, target, game);
						for (auto it : p->cannotAttack) {
							if (it == target->getOwner()) {
								advance->cannotBeAttacked = true;
							}
						}

						// Add the advance order to the player's list of orders
						orders->addOrders(advance);
					}

					// Input number of armies to move is bigger than number of armies in source territory
					else {
						cout << "Wrong input: You do not have this many armies in the source territory!" << endl;
					}
				}

				// Target territory cannot be attacked
				else {
					cout << "Wrong input: The target territory is not adjacent to one you own or it does not exist!" << endl;
				}
			}

			// Player does not own this territory or it does not exist
			else {
				cout << "Wrong input: You do not own this territory or it does not exist!" << endl;
			}
		}

		// Wrong input (not 1 or 2)
		else {
			cout << "Wrong input, try again (Input only 1 or 2)" << endl;
		}

		// Issue another advance order
		cout << "\nDo you wish to issue another advance order? " << endl;
		cout << "Reply with \"y\" if you wish to do so, any other input will be assumed to be a no : ";
		cin >> answer;
		cout << endl;
	}

	cout << "\n#--- Advancing Phase OVER ---#" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

	// All advance orders have been issued at this point!

	// Clearing the cannotAttack vector for Negotiate order
	p->cannotAttack.clear();

	// Now playing a card, Player plays one card per turn
	cout << "\n#--- Card Playing Phase ---#" << endl << endl;

	// Check if player has any cards in hand
	if (hand->getSize() > 0) {
		// Print the player's hand
		cout << "Printing all the cards in player's hand" << endl;
		if (hand->getSize() > 0) {
			for (int i = 0; i < hand->getSize(); i++) {
				cout << "Card index : " << i << ", Type: " << hand->getCardInHand(i)->getCardTypeName() << endl;
			}
		}

		// Ask input for the index of the card to play
		cout << "Select the index of the card you want to use : ";

		int cardIndex;
		cin >> cardIndex;
		cout << endl;

		// If input index is wrong, ask for input again
		while (cardIndex < 0 || cardIndex >= hand->getSize()) {
			cout << "Wrong index selected, please input another index : ";
			cin >> cardIndex;
			cout << endl;
		}

		// Convert input index to a card pointer
		Card* card = hand->getCardInHand(cardIndex);

		string cardName = card->getCardTypeName();

		// Cases for each type of card to be played and its required input
		if (cardName == "Bomb") {
			cout << "Bomb card selected:" << endl;

			cout << "Which territory should be bombed? Input the index from the list: " << endl;

			// List of territories to attack
			cout << "\nTerritories to attack: (Index : Name)" << endl;
			for (auto it : toAttack()) {
				cout << it->getIndex() << " : " + it->getName() << " , Armies: " << it->getNumberOfArmies() << endl;
			}
			cout << endl;

			// Input enemy territory index
			int territoryIndex;
			cin >> territoryIndex;
			cout << endl;

			// Convert territory index to territory pointer
			Territory* enemyT = game->getMap()->getTerritoryByIndex(territoryIndex);

			card->play(cardIndex, 0, p, nullptr, nullptr, enemyT, game);

			cout << "Bomb order will be issued!";
		}
		else if (cardName == "Reinforcement") {
			cout << "Reinforcement card selected --> Will be played immediately below: " << endl;
			card->play(cardIndex, 0, p, nullptr, nullptr, nullptr, game);
		}
		else if (cardName == "Blockade") {
			cout << "Blockade card selected:" << endl;

			cout << "Which territory should receive a blockade? Input the index from the list: " << endl;

			// List of territories to defend
			cout << "\nTerritories to defend: (Index : Name)" << endl;
			for (auto it : toDefend()) {
				cout << it->getIndex() << " : " + it->getName() << " , Armies: " << it->getNumberOfArmies() << endl;
			}
			cout << endl;

			// Input enemy territory index
			int territoryIndex;
			cin >> territoryIndex;
			cout << endl;

			// Convert territory index to territory pointer
			Territory* ownT = game->getMap()->getTerritoryByIndex(territoryIndex);

			card->play(cardIndex, 0, p, nullptr, nullptr, ownT, game);

			cout << "Blockade order will be issued!";
		}
		else if (cardName == "Airlift") {
			cout << "Airlift card selected:" << endl;

			cout << "Where should the airlift start? Input the index from the list: " << endl;

			// List of territories to defend
			cout << "\nTerritories to defend: (Index : Name)" << endl;
			for (auto it : toDefend()) {
				cout << it->getIndex() << " : " + it->getName() << " , Armies: " << it->getNumberOfArmies() << endl;
			}
			cout << endl;

			// Input enemy territory index
			int territoryIndex;
			cin >> territoryIndex;
			cout << endl;

			// Convert territory index to territory pointer
			Territory* ownT = game->getMap()->getTerritoryByIndex(territoryIndex);

			cout << "Where should the airlift head to? Input the index from the list: " << endl;

			// List of territories to defend
			cout << "\nTerritories to defend: (Index : Name)" << endl;
			for (auto it : toDefend()) {
				cout << it->getIndex() << " : " + it->getName() << " , Armies: " << it->getNumberOfArmies() << endl;
			}
			cout << endl;

			// Input enemy territory index
			int territoryIndex2;
			cin >> territoryIndex2;
			cout << "Input no of armies: " << endl;
			int army; cin >> army;
			cout << endl;

			// Convert territory index to territory pointer
			Territory* otherOwnT = game->getMap()->getTerritoryByIndex(territoryIndex2);

			card->play(cardIndex, army, p, nullptr, ownT, otherOwnT, game);

			cout << "Airlift order will be issued!";
		}
		else if (cardName == "Diplomacy") {
			cout << "Diplomacy card selected:" << endl;

			cout << "Who should Diplomacy be used on? Input the index from the list: " << endl;

			// List of players in the game
			cout << "\nList of players in the game: (Index : Name)" << endl;
			for (int i = 0; i < game->players.size(); i++) {
				cout << i << " : " + game->players.at(i)->getName() << endl;
			}
			cout << endl;

			// Input other player's index
			int playerIndex;
			cin >> playerIndex;
			cout << endl;

			Player* otherP = game->players.at(playerIndex);

			card->play(cardIndex, 0, p, otherP, nullptr, nullptr, game);

			cout << "Diplomacy order will be issued!";
		}
	}

	// Player has no cards in their hand
	else {
		cout << "Player " << p->getName() << " has no cards in their hand, skipping the card playing phase!" << endl;
	}

	cout << "\n#--- Card Playing Phase OVER ---#" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;
}

// toAttack() method for the HumanPlayerStrategy. It returns a vector of all territories that can be attacked
vector<Territory*> HumanPlayerStrategy::toAttack()
{

	// Vector containing all the territories that can be attacked
	vector<Territory*> attackableTerritories;

	// Double for-loop that adds the attackable territory to the vector
	for (Territory* t : p->getOwnedTerritories()) {
		for (Territory* a : t->getAdjacentTerritories()) {
			// Excluding owned territories
			if (!p->ownsTerritory(a)) {
				// Add territory to attack list
				attackableTerritories.push_back(a);
			}
		}
	}

	// Remove duplicates
	for (Territory* t : attackableTerritories) {
		attackableTerritories.erase(unique(attackableTerritories.begin(), attackableTerritories.end()), attackableTerritories.end());
	}
	return attackableTerritories;
}

// toDefend() method for the HumanPlayerStrategy. It returns a vector of all the territories owned by the player
vector<Territory*> HumanPlayerStrategy::toDefend() {
	return p->getOwnedTerritories();
}

// Overloading the output operator for the AggressivePlayerStrategy
ostream& operator<<(ostream& out, const AggressivePlayerStrategy&)
{
	return out << "Aggressive Player Strategy";
}

// Default constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player) : PlayerStrategy(player, Aggressive) { }

// Copy constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& hps) : PlayerStrategy(hps) { }

// Overloading the assignment operator
AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& hps)
{
	p = hps.p;
	strN = hps.strN;
	return *this;
}

// The aggressive player issues its orders through the three phases (deploy, advance, cards) by focusing on attacking
void AggressivePlayerStrategy::issueOrder() {
	GameEngine* game = p->getGameEngine();
	Hand* hand = p->getHand();
	Deck* deck = game->getDeck();
	OrdersList* orders = p->getOrdersList();

	// Introduction message for each player
	cout << "\nIssuing orders for player " << p->getName() << ":" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

	cout << "#--- Deploying Phase ---#" << endl;

	// List of territories to defend
	cout << "\nTerritories to defend: (Index : Name)" << endl;
	for (auto it : toDefend()) {
		cout << it->getIndex() << " : " + it->getName() << " , Armies: " << it->getNumberOfArmies() << endl;
	}
	cout << endl;

	// Deploy all to strongest territory
	while (p->getReinforcementPool() > 0) {
		// Announce how big the reinforcement pool is
		cout << "Player " << p->getName() << "'s number of armies left in the reinforcement pool: " << p->getReinforcementPool() << endl << endl;
		cout << "Player " << p->getName() << " has chosen territory " << p->toDefend().at(0)->getName() << " to defend with " << p->getReinforcementPool() << " armies." << endl;;
		
		// Adds a deploy order to the strongest owned country to the player's list of orders
		orders->addOrders(new Deploy(p, p->getReinforcementPool(), p->toDefend().at(0), game));

		// Since the whole reinforcement pool was used for the deploy order, we set it to 0
		p->setReinforcementPool(0);
	}

	cout << "\n#--- Deploying Phase OVER ---#" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

	// All deploy orders have been issued at this point

	// Now issuing advance orders
	cout << "\n#--- Advancing Phase ---#" << endl;

	// List of territories to attack
	cout << "\nTerritories to attack: (Index : Name)" << endl;
	for (auto it : toAttack()) {
		cout << it->getIndex() << " : " + it->getName() << " , Armies: " << it->getNumberOfArmies() << endl;
	}
	cout << endl;

	// Check if there are any countries to attack
	if (toAttack().size() > 0) {
		Territory* source = toDefend().at(0); // The source is the strongest owned territory
		Territory* target = toAttack().at(0); // The target is the first attackable territory
		int army = source->getNumberOfArmies(); // Every attack will use all the armies from the source

		cout << "Advancing from " << source->getName() << " to "
			<< target->getName() << " " << army << " armies!" << endl;
		//Takes care of what happens if diplomacy was used last turn
		Advance* advance = new Advance(p, army, source, target, game);
		for (auto it : p->cannotAttack) {
			if (it == target->getOwner()) {
				advance->cannotBeAttacked = true;
			}
		}
		orders->addOrders(advance);
	}

	cout << "Sending all armies from weaker countries to strongest country!" << endl;
	// Advance all armies from weaker countries to strongest country
	for (int i = 1; i < toDefend().size() - 1; i++) {
		Territory* source = toDefend().at(i);
		Territory* target = toAttack().at(0);
		int army = source->getNumberOfArmies();

		cout << "Advancing from " << source->getName() << " to "
			<< target->getName() << " " << army << " armies!" << endl;
		//Takes care of what happens if diplomacy was used last turn
		Advance* advance = new Advance(p, army, source, target, game);
		orders->addOrders(advance);
	}

	cout << "\n#--- Advancing Phase OVER ---#" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

	// All advance orders have been issued at this point!

	//Clearing the cannotAttack vector for Negotiate order
	p->cannotAttack.clear();

	// Now playing a card, Player plays one card per turn. The aggressive player cannot play blockade nor diplomacy cards
	cout << "\n#--- Card Playing Phase ---#" << endl << endl;

	if (hand->getSize() > 0)
	{
		int handSize = p->getHand()->getSize();
		for (int i = 0; i < handSize; ++i)
		{
			Card* currentCard = p->getHand()->getCardInHand(i);
			string cardName = currentCard->getCardTypeName();
			// Cases for each type of card that could be played
			if (cardName == "Bomb") {
				cout << "Bomb card selected:" << endl;
				Territory* enemyT = toAttack().at(0);
				currentCard->play(i, 0, p, nullptr, nullptr, enemyT, game);
				cout << "Bomb order will be issued on !" << enemyT->getName() << endl;
				break;
			}
			else if (cardName == "Reinforcement") {
				cout << "Reinforcement card selected: " << endl;
				currentCard->play(i, 0, p, nullptr, nullptr, nullptr, game);
				break;
			}
			else if (cardName == "Airlift") {
				if (toDefend().size() > 1) {
					cout << "Airlift card selected:" << endl;
					Territory* ownT = toDefend().at(1);
					Territory* otherOwnT = toDefend().at(0);
					currentCard->play(i, ownT->getNumberOfArmies(), p, nullptr, ownT, otherOwnT, game);
					cout << "Airlift order will be issued!";
					break;
				}
			}

			// In case the player has no cards in their hand that they can play
			if (i == handSize - 1) {
				cout << "Player " << p->getName() << " has no cards in their hand they should play, skipping the card playing phase!" << endl;
			}
		}
	}

	// If the player has no cards in their hand at all
	else {
		cout << "Player " << p->getName() << " has no cards in their hand, skipping the card playing phase!" << endl;
	}

	cout << "\n#--- Card Playing Phase OVER ---#" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;
}

// toAttack() method for the AggressivePlayerStrategy. It returns a vector of all territories that can be attacked
vector<Territory*> AggressivePlayerStrategy::toAttack() {
	vector<Territory*> attackableTerritories;
	for (Territory* t : p->getOwnedTerritories()) {
		for (Territory* a : t->getAdjacentTerritories()) {
			// Excluding owned territories
			if (!p->ownsTerritory(a)) {
				// Add territory to attack list
				attackableTerritories.push_back(a);
			}
		}
	}
	// Remove duplicates
	for (Territory* t : attackableTerritories) {
		attackableTerritories.erase(unique(attackableTerritories.begin(), attackableTerritories.end()), attackableTerritories.end());
	}
	sort(attackableTerritories.begin(), attackableTerritories.end(), weakestTerritory);
	return attackableTerritories;
}

// toDefend() method for the AggressivePlayerStrategy. It returns a vector of all the territories owned by the player
vector<Territory*> AggressivePlayerStrategy::toDefend() {
	vector<Territory*> OwnedTerritories = p->getOwnedTerritories();
	sort(OwnedTerritories.begin(), OwnedTerritories.end(), strongestTerritory);
	return OwnedTerritories;
}

// Overloading the output operator
ostream& operator<<(ostream& out, const BenevolentPlayerStrategy&)
{
	return out << "Benevolent Player Strategy";
}

// Default constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* player) : PlayerStrategy(player, Benevolent) { }

// Copy constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& hps) : PlayerStrategy(hps) { }

// Overloading the assignment operator
BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& hps)
{
	p = hps.p;
	strN = hps.strN;
	return *this;
}

// The benevolent player issues its orders through the three phases (deploy, advance, cards) by focusing on defending
void BenevolentPlayerStrategy::issueOrder() {
	GameEngine* game = p->getGameEngine();
	Hand* hand = p->getHand();
	Deck* deck = game->getDeck();
	OrdersList* orders = p->getOrdersList();

	// Introduction message for each player
	cout << "\nIssuing orders for player " << p->getName() << ":" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

	cout << "#--- Deploying Phase ---#" << endl;

	// List of territories to defend
	cout << "\nTerritories to defend: (Index : Name)" << endl;
	for (auto it : toDefend()) {
		cout << it->getIndex() << " : " + it->getName() << " , Armies: " << it->getNumberOfArmies() << endl;
	}
	cout << endl;

	// Deploy all the reinforcement pool to its weakest country
	while (p->getReinforcementPool() > 0) {
		// Announce how big the reinforcement pool is
		cout << "Player " << p->getName() << "'s number of armies left in the reinforcement pool: " << p->getReinforcementPool() << endl << endl;
		cout << "Player " << p->getName() << " has chosen territory " << p->toDefend().at(0)->getName() << " to defend with " << p->getReinforcementPool() << " armies." << endl;
		orders->addOrders(new Deploy(p, p->getReinforcementPool(), p->toDefend().at(0), game));
		p->setReinforcementPool(0);
	}

	cout << "\n#--- Deploying Phase OVER ---#" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

	// Now issuing advance orders
	cout << "\n#--- Advancing Phase ---#" << endl;

	cout << "\nThe Benevolent Player has no advances to make." << endl;

	cout << "\n#--- Advancing Phase OVER ---#" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

	// All advance orders have been issued at this point!

	//Clearing the cannotAttack vector for Negotiate order
	p->cannotAttack.clear();

	// Now playing a card, Player plays one card per turn
	cout << "\n#--- Card Playing Phase ---#" << endl << endl;

	// The benevolent player cannot use the bomb card
	if (hand->getSize() > 0)
	{
		int handSize = p->getHand()->getSize();
		for (int i = 0; i < handSize; ++i)
		{
			Card* currentCard = p->getHand()->getCardInHand(i);
			string cardName = currentCard->getCardTypeName();
			// Cases for each type of card that could be played

			if (cardName == "Blockade") {
				cout << "Blockade card selected:" << endl;
				Territory* target = toDefend().at(0);
				currentCard->play(i, 0, p, nullptr, nullptr, target, game);
				cout << "Blockade order will be issued on !" << target->getName() << endl;
				break;
			}
			else if (cardName == "Reinforcement") {
				cout << "Reinforcement card selected: " << endl;
				currentCard->play(i, 0, p, nullptr, nullptr, nullptr, game);
				break;
			}
			else if (cardName == "Airlift") {
				if (toDefend().size() > 1) {
					cout << "Airlift card selected:" << endl;
					Territory* ownT = toDefend().at(1);
					Territory* otherOwnT = toDefend().at(0);
					currentCard->play(i, ownT->getNumberOfArmies(), p, nullptr, ownT, otherOwnT, game);
					cout << "Airlift order will be issued!";
					break;
				}
			}
			else if (cardName == "Diplomacy")
			{
				Player* otherP;
				if (game->players.at(0) == p)
				{
					otherP = game->players.at(1);
				}
				else
				{
					otherP = game->players.at(0);
				}
				cout << "Diplomacy card selected. " << endl;
				cout << "Diplomacy order will be issued!" << endl;
				currentCard->play(i, 0, p, otherP, nullptr, nullptr, game);
			}

			// If the player has cards that cannot be played
			if (i == handSize - 1) {
				cout << "Player " << p->getName() << " has no cards in their hand they should play, skipping the card playing phase!" << endl;
			}
		}
	}

	// If the player has no cards whatsoever to play
	else {
		cout << "Player " << p->getName() << " has no cards in their hand, skipping the card playing phase!" << endl;
	}

	cout << "\n#--- Card Playing Phase OVER ---#" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;
}

// Since the benevolent player never attacks, we return an empty vector
vector<Territory*> BenevolentPlayerStrategy::toAttack() {
	vector<Territory*> empty;
	return empty;
}

// toDefend() method that returns a vector of territories pointers sorted from the weakest territory first
vector<Territory*> BenevolentPlayerStrategy::toDefend() {
	vector<Territory*> sortedOwnedTerritories = p->getOwnedTerritories();
	sort(sortedOwnedTerritories.begin(), sortedOwnedTerritories.end(), weakestTerritory); // Sorting the vector
	return sortedOwnedTerritories;
}

// Overloading the output operator
ostream& operator<<(ostream& out, const NeutralPlayerStrategy&)
{
	return out << "Neutral Player Strategy";
}

// Default constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(Player* player) : PlayerStrategy(player, Neutral) { }

// Copy constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& hps) : PlayerStrategy(hps) { }

// Overloading the assignment operator
NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& hps)
{
	p = hps.p;
	strN = hps.strN;
	return *this;
}

/* The neutral player issues its orders through the three phases(deploy, advance, cards) by not issuing any order until it is attacked.
At which point, the neutral player becomes an aggressive player */
void NeutralPlayerStrategy::issueOrder() {
	//- Implemented in Advance::execute() and Bomb::execute() -//

	GameEngine* game = p->getGameEngine();
	Hand* hand = p->getHand();
	Deck* deck = game->getDeck();
	OrdersList* orders = p->getOrdersList();

	// Introduction message for each player
	cout << "\nIssuing orders for player " << p->getName() << ":" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

	cout << "#--- Deploying Phase ---#" << endl;

	// List of territories to defend
	cout << "\nTerritories to defend: (Index : Name)" << endl;
	for (auto it : toDefend()) {
		cout << it->getIndex() << " : " + it->getName() << " , Armies: " << it->getNumberOfArmies() << endl;
	}
	cout << endl;

	// Deploy all to weakest territory
	while (p->getReinforcementPool() > 0) {
		// Announce how big the reinforcement pool is
		cout << "Player " << p->getName() << "'s number of armies left in the reinforcement pool: " << p->getReinforcementPool() << endl << endl;
		cout << "Player " << p->getName() << " has chosen territory " << p->toDefend().at(0)->getName() << " to defend with " << p->getReinforcementPool() << " armies." << endl;;
		orders->addOrders(new Deploy(p, p->getReinforcementPool(), p->toDefend().at(0), game));
		p->setReinforcementPool(0);
	}

	cout << "\n#--- Deploying Phase OVER ---#" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

	// All deploy orders have been issued at this point!

	// Now issuing advance orders
	cout << "\n#--- Advancing Phase ---#" << endl;

	cout << "\nPlayer " << p->getName() << " has chosen not to advance." << endl;

	cout << "\n#--- Advancing Phase OVER ---#" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

	// All advance orders have been issued at this point!

	//Clearing the cannotAttack vector for Negotiate order
	p->cannotAttack.clear();

	// Now playing a card, Player plays one card per turn
	cout << "\n#--- Card Playing Phase ---#" << endl << endl;
	
	// The neutral player cannot use the bomb card
	if (hand->getSize() > 0)
	{
		int handSize = p->getHand()->getSize();
		for (int i = 0; i < handSize; ++i)
		{
			Card* currentCard = p->getHand()->getCardInHand(i);
			string cardName = currentCard->getCardTypeName();
			if (cardName == "Reinforcement")
			{
				cout << "Reinforcement card selected --> Will be played immediately below: " << endl;
				cout << "Reinforcement order will be issued!" << endl;
				currentCard->play(i, 0, p, nullptr, nullptr, nullptr, game);
				break;
			}
			else if (cardName == "Diplomacy")
			{
				Player* otherP;
				if (game->players.at(0) == p)
				{
					otherP = game->players.at(1);
				}
				else
				{
					otherP = game->players.at(0);
				}
				cout << "Diplomacy card selected. " << endl;
				cout << "Diplomacy order will be issued!" << endl;
				currentCard->play(i, 0, p, otherP, nullptr, nullptr, game);
			}
			else if (cardName == "Airlift") {
				if (toDefend().size() > 1) {
					cout << "Airlift card selected:" << endl;
					Territory* ownT = toDefend().at(1);
					Territory* otherOwnT = toDefend().at(0);
					currentCard->play(i, ownT->getNumberOfArmies(), p, nullptr, ownT, otherOwnT, game);
					cout << "Airlift order will be issued!";
					break;
				}
			}
			else if (cardName == "Blockade") {
				cout << "Blockade card selected:" << endl;
				Territory* target = toDefend().at(0);
				currentCard->play(i, 0, p, nullptr, nullptr, target, game);
				cout << "Blockade order will be issued on !" << target->getName() << endl;
				break;
			}

			// If the player has no cards that can be played in their hand
			if (i == handSize - 1) {
				cout << "Player " << p->getName() << " has no cards in their hand they should play, skipping the card playing phase!" << endl;
			}
		}
	}

	// If the player has no cards whatsoever to play
	else {
		cout << "Player " << p->getName() << " has no cards in their hand, skipping the card playing phase!" << endl;
	}

	cout << "\n#--- Card Playing Phase OVER ---#" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

}

// A neutral player never attacks, so we return an empty vector of territories
vector<Territory*> NeutralPlayerStrategy::toAttack() {
	vector<Territory*> empty;
	return empty;
}

// toDefend() methods that returns a vector of territories pointers sorted by the weakest territories first
vector<Territory*> NeutralPlayerStrategy::toDefend() {
	vector<Territory*> OwnedTerritories = p->getOwnedTerritories();
	sort(OwnedTerritories.begin(), OwnedTerritories.end(), weakestTerritory); // Sorting the vector
	return OwnedTerritories;
}

// Overloading the output operator
ostream& operator<<(ostream& out, const CheaterPlayerStrategy&)
{
	return out << "Cheater Player Strategy";
}

// Default constructor
CheaterPlayerStrategy::CheaterPlayerStrategy(Player* player) : PlayerStrategy(player, Cheater) { }

// Copy constructor
CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy& hps) : PlayerStrategy(hps) { }

// Overloading the assignment operator
CheaterPlayerStrategy& CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy& hps)
{
	p = hps.p;
	strN = hps.strN;
	return *this;
}

// The cheater player issues its orders through the three phases(deploy, advance, cards) and wins all adjacent territories once per turn
void CheaterPlayerStrategy::issueOrder() {
	GameEngine* game = p->getGameEngine();
	Hand* hand = p->getHand();
	Deck* deck = game->getDeck();
	OrdersList* orders = p->getOrdersList();

	// Introduction message for each player
	cout << "\nIssuing orders for player " << p->getName() << ":" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

	cout << "#--- Deploying Phase ---#" << endl;

	// List of territories to defend
	cout << "\nTerritories to defend: (Index : Name)" << endl;
	for (auto it : toDefend()) {
		cout << it->getIndex() << " : " + it->getName() << " , Armies: " << it->getNumberOfArmies() << endl;
	}
	cout << endl;

	// While the player still has armies to deploy (reinforcement pool is not empty)
	while (p->getReinforcementPool() > 0) {
		// Announce how big the reinforcement pool is
		cout << "Player " << p->getName() << "'s number of armies left in the reinforcement pool: " << p->getReinforcementPool() << endl << endl;


		Territory* chosenTerritory = p->toDefend().at(0);
		// Choose index of territory to defend
		cout << "Player " << p->getName() << " has chosen to defend territory " << p->toDefend().at(0)->getName() << " with " << p->getReinforcementPool() << " armies." << endl;

		int deployNo = p->getReinforcementPool();
		orders->addOrders(new Deploy(p, deployNo, chosenTerritory, game));
		p->setReinforcementPool(0);

	}

	cout << "\n#--- Deploying Phase OVER ---#" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

	// All deploy orders have been issued at this point!

	// Now issuing advance orders
	cout << "\n#--- Advancing Phase ---#" << endl;

	vector<int> territoryPositions;

	// For each attackable territory, adding its index in the territoryPositions vector
	for (auto t : toAttack())
	{
		territoryPositions.push_back(t->getIndex());
	}

	cout << "\nCheater issuing advance orders on adjacent territories." << endl;

	// Cheater conquers all ajacent territories by using the territoryPositions vector
	for (auto d : toDefend())
	{
		for (auto t : toAttack())
		{
			if (find(territoryPositions.begin(), territoryPositions.end(), t->getIndex()) != territoryPositions.end())
			{
				// Adding the advance order to the player's list of orders
				orders->addOrders(new Advance(p, 1, d, t, game));

				// Removing the territory conquered from the territoryPositions vector
				territoryPositions.erase(remove(territoryPositions.begin(), territoryPositions.end(), t->getIndex()), territoryPositions.end());
			}
		}
	}

	cout << "\n#--- Advancing Phase OVER ---#" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

	// All advance orders have been issued at this point!

	//Clearing the cannotAttack vector for Negotiate order
	p->cannotAttack.clear();

	// Now playing a card, Player plays one card per turn
	cout << "\n#--- Card Playing Phase ---#" << endl << endl;
	cout << "\nThe cheater doesn't want to follow the rules, they don't play any cards." << endl;
	cout << "\n#--- Card Playing Phase OVER ---#" << endl;
	cout << "/*-------------------------------------------------------------------*/" << endl;

}

// toAttack() method that returns all attackable territories in a vector of territories pointers, sorted by weakest territories
vector<Territory*> CheaterPlayerStrategy::toAttack() {
	vector<Territory*> attackableTerritories;
	for (Territory* t : p->getOwnedTerritories()) {
		for (Territory* a : t->getAdjacentTerritories()) {
			// Excluding owned territories
			if (!p->ownsTerritory(a)) {
				// Add territory to attack list
				attackableTerritories.push_back(a);
			}
		}
	}

	// Remove duplicates
	for (Territory* t : attackableTerritories) {
		attackableTerritories.erase(unique(attackableTerritories.begin(), attackableTerritories.end()), attackableTerritories.end());
	}
	sort(attackableTerritories.begin(), attackableTerritories.end(), weakestTerritory);
	return attackableTerritories;
}

// toDefend() that returns a sorted vector of territories pointers. The weakest territories are first
vector<Territory*> CheaterPlayerStrategy::toDefend() {
	vector<Territory*> OwnedTerritories = p->getOwnedTerritories();
	sort(OwnedTerritories.begin(), OwnedTerritories.end(), weakestTerritory);
	return OwnedTerritories;
}

// Comparator for weakest territory
bool weakestTerritory(Territory* territory1, Territory* territory2)
{
	return (territory1->getNumberOfArmies() < territory2->getNumberOfArmies());
}

// Comparator for strongest territory
bool strongestTerritory(Territory* territory1, Territory* territory2)
{
	return (territory1->getNumberOfArmies() > territory2->getNumberOfArmies());
}