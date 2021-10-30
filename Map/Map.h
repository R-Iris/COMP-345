#pragma once

/**
 * COMP 345: Advanced Program Design with C++
 * @file Map.h
 * @author Jason Patel 
 * @version 8/10/2021
 */

#include <iostream>
#include <vector>
#include <tuple>
#include <exception>
#include "../Player/Player.h"

using namespace std;

// Forward declaration
class Player;

/**
	* Implementation of a "Continent" object to be used in Warzone.
	*
	* This class stores the data of a continent defined in the game's map file (except for the color).
	* 
	* FIELDS:
	* 
	* continentIndex <int>: Unique identifier of this continent, no two continents may have the same index.
	* name <string>: The name of this continent.
	* armies <int>: The value of the army bonus that a player can obtain once they control all territories within this continent.
	*/
class Continent 
{
	private:
		int continentIndex;
		string name;
		int armies;

	public:
		// CONSTRUCTORS
		Continent();
		Continent(int continentIndex, string name, int armies);

		// COPY CONSTRUCTOR
		Continent(const Continent &c);

		// OPERATOR OVERLOADS
		Continent &operator=(const Continent &c);

		friend ostream& operator<<(ostream& out, const Continent& c);

		// DESTRUCTOR
		~Continent();

		// MEMBER FUNCTIONS
		string getName();
		int getArmies();
		int getIndex();
};

/**
	* Implementation of a "Territory" object to be used in Warzone.
	*
	* This class stores the data of a territory/country defined in the game's map file. This object acts as a node on the game's map, which is essentially a graph.
	* Over the course of the game, players can claim ownership of this territory and assign a number of their own armies to it. Apart from the information defined in 
	* the "[countries]" section of the map file, this node also keeps track of all the other nodes that are adjacent to it.
	* 
	* FIELDS:
	* 
	* owner <Player>: The player who owns this territory.
	* numberOfArmies <int>: The amount of armies that a player had devoted to this territory.
	* countryIndex <int>: This territory's unique identifier. No two countries may have the same index.
	* name <string>: This territory's name.
	* parent <int>: The index of the continent that this territory is a part of.
	* adjacentCountries <vector<Territory*>>: A collection of pointers that point to this territory's neighbouring countries.
	* x <int>: The x component of this territory's cartesian coordinate (Normally, a circle is drawn on the map with this country's index, this field helps decide where that circle is drawn.).
	* y <int>: The y component of this territory's cartesian coordinate (Normally, a circle is drawn on the map with this country's index, this field helps decide where that circle is drawn.).
	*/
class Territory // This is a node on the graph
{
	private:
		Player* owner;
		int numberOfArmies;
		int countryIndex;
		string name;
		int parent;

		vector<Territory*> adjacentCountries; // This will store the nodes with which this node shares borders

		// Cartesian coordinates for the territory on the map
		int x;
		int y;
		
	public:
		// CONSTRUCTORS
		Territory();
		Territory(const Territory &t);

		// Implementing the parent continent as a number
		Territory(Player* owner, int numberOfArmies, int countryIndex, string name, int parent, int x, int y);
		Territory(Player* owner, int numberOfArmies, int countryIndex, string name, int parent, vector<Territory*> adjacentCountries, int x, int y);
		Territory(int numberOfArmies, int countryIndex, string name, int parent, int x, int y);
		Territory(int countryIndex, string name, int parent, int x, int y);

		// OPERATOR OVERLOADS
		Territory &operator=(const Territory &t);

		friend ostream& operator<<(ostream& out, const Territory &t);

		// Evaluates equivalency between two territories by comparing their indices. Returns 'true' if both indices are equivalent, 'false' otherwise.
		friend bool& operator==(const Territory& lhs, const Territory& rhs);

		// MEMBER FUNCTIONS
		int getIndex();
		Player getOwner();
		int getNumberOfArmies();
		string getName();
		int getContinent();
		vector<Territory*> getAdjacentTerritories();
		int getX();
		int getY();

		void setOwner(Player* player);
		void setNumberOfArmies(int numArmies);
		void setName(string newName);
		void setAdjacentTerritories(vector<Territory*> territories);
		void setX(int newX);
		void setY(int newY);

		void addAdjacentCountry(Territory* territory);
			
		// DESTRUCTOR
		~Territory();
}; 

/**
	* Custom Exception to be thrown whenever map validation detects an invalid map. (NOT FULLY IMPLEMENTED)
	*
	*/
struct InvalidMapException : std::exception {
	const enum MAP_ERRORS {
		ISOLATED_NODE = 1,
		DISCONNECTED_SUBGRAPH = 2,
		EMPTY_CONTINENT = 3
	};
		
	const string error() const throw();
};

/**
	* Implementation of the map on which the Warzone game is played on.
	*
	* This class stores all the information defined in the map file, namely all the continents, countries and the borders between those countries. It also has the capability to verify
	* its own validity (all countries are connected, all continents are connected subgraphs, etc.).
	* 
	* FIELDS:
	* 
	* continents <vector<Continent*>>: Collection of pointers to defined continents.
	* countries <vector<Territory*>>: Collection of pointers to defined countries.
	* borders <vector<tuple<int,int>>>: Collection of pairs of country indices where each pair defines the link (or shared border) between those countries.
	*/
class Map // This is the graph
{
	private:
		vector<Continent*> continents;
		vector<Territory*> countries;
		vector<tuple<int,int>> borders;

	public:
		Map();
		Map(const Map &m);
		Map(vector<Continent*> continents, vector<Territory*> countries, vector<tuple<int,int>> borders);

		// OPERATOR OVERLOADS
		Map &operator=(const Map &m);

		friend ostream &operator<<(ostream& out, const Map &m);
			
		// MEMBER FUNCTIONS
		vector<Continent*> getContinents();
		vector<Territory*> getTerritories();
		vector<tuple<int,int>> getBorders();

		vector<tuple<int, int>> getBordersByCountry(Territory country);

		vector<Territory*> getTerritoriesByContinent(int continent);

		void setContinents(vector<Continent*> continents);
		void setTerritories(vector<Territory*> territories);
		void setBorders(vector<tuple<int,int>> borders);

		void addContinent(Continent* continent);
		void addTerritory(Territory* territory);
		void addBorder(tuple<int, int> border);

		bool borderExists(vector<Territory*> toCheck, Territory destination, vector<Territory> checked);
		void validate();

		static bool territoryExists(vector<Territory> collection, Territory toFind);

		// DESTRUCTOR
		~Map();
};

/**
	* Implementation of a Map loader.
	*
	* This class is not intended to be instantiated, rather, it exposes a single function which takes in the path to the map file to be used. It then uses the path to read the file
	* and generates a map from it, which it then returns upon exit.
	*/
class MapLoader 
{
	private:
	public:
		static Map* createMapfromFile(string fileName);
};