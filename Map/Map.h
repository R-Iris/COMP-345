#pragma once

#include <iostream>
#include <vector>
#include <tuple>
#include <exception>

using namespace std;

namespace MapSpace
{
	// PLACEHOLDER FOR THE ACTUAL PLAYER CLASS
	class Player {
		public:
			Player();
			~Player();
	};

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

	class Territory // This is a node on the graph
	{
		private:
			Player* owner;
			int numberOfArmies;
			int countryIndex;
			string name;

			int parent;

			vector<Territory*> adjacentCountries; // This will store the nodes with which this node shares borders
			//vector<int> adjacentCountries;

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
			//Territory(Player* owner, int numberOfArmies, int countryIndex, string name, int parent, vector<int> adjacentCountries, int x, int y);
			Territory(int numberOfArmies, int countryIndex, string name, int parent, int x, int y);
			Territory(int countryIndex, string name, int parent, int x, int y);

			// OPERATOR OVERLOADS
			Territory &operator=(const Territory &t);

			friend ostream& operator<<(ostream& out, const Territory &t);
			friend bool& operator==(const Territory& lhs, const Territory& rhs);

			// MEMBER FUNCTIONS
			int getIndex();
			Player getOwner();
			int getNumberOfArmies();
			string getName();
			int getContinent();
			vector<Territory*> getAdjacentTerritories();
			//vector<int> getAdjacentTerritories();
			int getX();
			int getY();

			void setOwner(Player* player);
			void setNumberOfArmies(int numArmies);
			void setName(string newName);
			void setAdjacentTerritories(vector<Territory*> territories);
			//void setAdjacentTerritories(vector<int> territories);
			void setX(int newX);
			void setY(int newY);

			void addAdjacentCountry(Territory* territory);
			//void addAdjacentCountry(int territory);
			
			// DESTRUCTOR
			~Territory();
	}; 

	struct InvalidMapException : std::exception {
		const enum MAP_ERRORS {
			ISOLATED_NODE = 1,
			DISCONNECTED_SUBGRAPH = 2,
			EMPTY_CONTINENT = 3
		};
		
		const string error() const throw();
	};

	class Map // This is the graph
	{
		private:
			vector<Continent*> continents;
			vector<Territory*> countries; // Nodes
			vector<tuple<int,int>> borders; // Edges

			/* Check if continents are connected subgraphs if there exists an edge (set of borders) that contain the country number of each country belonging to a continent */
			

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

			~Map();

			bool borderExists(vector<Territory*> toCheck, Territory destination, vector<Territory> checked);
			void validate();

			static bool territoryExists(vector<Territory> collection, Territory toFind);
	};

	class MapLoader 
	{
		private:
		public:
			static Map createMapfromFile(string fileName);
	};

	// TODO: Define custom Exception for Invalid Map Files

}
