#pragma once

#include "Player.h"; // Include player to overload its methods
#include <vector>;

// Forward declarations
class Territory;

// The issueOrder(), toDefend(), and toAttack() methods of the player do not implement behavior and
// simply delegate their call to the corresponding methods in the PlayerStrategy member of the Player.
// All classes must implement a correct copy constructor, assignment operator, and stream insertion operator.

class PlayerStrategy {
private:
	friend ostream& operator<<(ostream& out, const PlayerStrategy&); // Stream insertion operator
protected:
	Player* p;	
public:
	PlayerStrategy(Player*); // Default Constructor
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

/* Aggressive player : computer player that focuses on attack(deploys or advances armies on its strongest
country, then always advances to enemy territories until it cannot do so anymore). */
class AggressivePlayerStrategy : public PlayerStrategy {
public:
	virtual void issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
};

/* Benevolent player: computer player that focuses on protecting its weak countries (deploys or advances armies
on its weakest countries, never advances to enemy territories). */
class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	virtual void issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
};

/* Neutral player: computer player that never issues any order. If a Neutral player is attacked, it becomes an
Aggressive player. */
class NeutralPlayerStrategy : public PlayerStrategy {
public:
	virtual void issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
};

/* Cheater player: computer player that automatically conquers all territories that are adjacent to its own
territories (only once per turn). */
class CheaterPlayerStrategy : public PlayerStrategy{
public:
	virtual void issueOrder();
	virtual vector<Territory*> toAttack();
	virtual vector<Territory*> toDefend();
};