#pragma once

#include "Player.h" // Include player to overload its methods
#include <vector>
#include <algorithm>

// Forward declaration
class Territory;

// Abstract parent class, inherited by all children
class PlayerStrategy {
private:
	friend ostream& operator<<(ostream& out, const PlayerStrategy&); // Stream insertion operator
protected:
	Player* p;	
public:
	enum strategyName { Human, Aggressive, Benevolent, Neutral, Cheater};
	strategyName strN;
	PlayerStrategy(Player*, strategyName); // Default Constructor
	PlayerStrategy(const PlayerStrategy&); // Copy Constructor
	PlayerStrategy& operator =(const PlayerStrategy&); // Assignment operator
	Player* getPlayer();
	void setPlayer(Player*);
	virtual void issueOrder() = 0;
	virtual vector<Territory*> toAttack() = 0;
	virtual vector<Territory*> toDefend() = 0;
};

// Human player: requires user interactions to make decisions.
class HumanPlayerStrategy : public PlayerStrategy {
private:
	friend ostream& operator<<(ostream& out, const HumanPlayerStrategy&);
public:
	HumanPlayerStrategy(Player*);
	HumanPlayerStrategy(const HumanPlayerStrategy&);
	HumanPlayerStrategy& operator =(const HumanPlayerStrategy&);
	virtual void issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
};

// Aggressive player : computer player that focuses on attack
class AggressivePlayerStrategy : public PlayerStrategy {
private:
	friend ostream& operator<<(ostream& out, const AggressivePlayerStrategy&);
public:
	AggressivePlayerStrategy(Player*);
	AggressivePlayerStrategy(const AggressivePlayerStrategy&);
	AggressivePlayerStrategy& operator =(const AggressivePlayerStrategy&);
	virtual void issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
};

// Benevolent player: computer player that focuses on protecting its weak countries
class BenevolentPlayerStrategy : public PlayerStrategy {
private:
	friend ostream& operator<<(ostream& out, const BenevolentPlayerStrategy&);
public:
	BenevolentPlayerStrategy(Player*);
	BenevolentPlayerStrategy(const BenevolentPlayerStrategy&);
	BenevolentPlayerStrategy& operator =(const BenevolentPlayerStrategy&);
	virtual void issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
};

/* Neutral player: computer player that never issues any order. If a Neutral player is attacked, it becomes an
Aggressive player. */
class NeutralPlayerStrategy : public PlayerStrategy {
private:
	friend ostream& operator<<(ostream& out, const NeutralPlayerStrategy&);
public:
	NeutralPlayerStrategy(Player*);
	NeutralPlayerStrategy(const NeutralPlayerStrategy&);
	NeutralPlayerStrategy& operator =(const NeutralPlayerStrategy&);
	virtual void issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
};

// Cheater player: computer player that automatically conquers all territories that are adjacent to its own territories
class CheaterPlayerStrategy : public PlayerStrategy{
private:
	friend ostream& operator<<(ostream& out, const CheaterPlayerStrategy&);
public:
	CheaterPlayerStrategy(Player*);
	CheaterPlayerStrategy(const CheaterPlayerStrategy&);
	CheaterPlayerStrategy& operator =(const CheaterPlayerStrategy&);
	virtual void issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
};

bool weakestTerritory(Territory*, Territory*); // Compares two territories and returns a boolean signifiying the weakest one
bool strongestTerritory(Territory*, Territory*); // Compares two territories and returns a boolean signifiying  the strongest one