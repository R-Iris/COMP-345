#pragma once

#include <iostream>
#include <vector>
#include <tuple>
#include <exception>

using namespace std;

namespace MapSpace
{
	class Player {
		// PLACEHOLDER FOR THE ACTUAL PLAYER CLASS
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
			int numberOfArmies; // QUESTION: Is a territory supposed to have a number of armies by default, or is this the number of armies that a player is devoting to it?
			int countryIndex;
			string name;
			//Continent* parent;

			int parent;

			vector<int>* adjacentCountries; // This will store the nodes with which this node shares edges

			// These determine where the circle of the country will go on the map
			int x;
			int y;
		
		public:
			// CONSTRUCTORS
			Territory();
			Territory(const Territory &t);

			// Implementing the parent continent as an object
			/*Territory(Player* owner, int numberOfArmies, int countryIndex, string name, Continent* parent, int x, int y);
			Territory(Player* owner, int numberOfArmies, int countryIndex, string name, Continent* parent, vector<int>* adjacentCountries, int x, int y);
			Territory(int numberOfArmies, int countryIndex, string name, Continent* parent, int x, int y);
			Territory(int countryIndex, string name, Continent* parent, int x, int y);*/

			// Implementing the parent continent as a number
			Territory(Player* owner, int numberOfArmies, int countryIndex, string name, int parent, int x, int y);
			Territory(Player* owner, int numberOfArmies, int countryIndex, string name, int parent, vector<int>* adjacentCountries, int x, int y);
			Territory(int numberOfArmies, int countryIndex, string name, int parent, int x, int y);
			Territory(int countryIndex, string name, int parent, int x, int y);

			// OPERATOR OVERLOADS
			Territory &operator=(const Territory &t);

			friend ostream& operator<<(ostream& out, const Territory &t);

			// MEMBER FUNCTIONS
			int getIndex();
			Player getOwner();
			int getNumberOfArmies();
			string getName();
			int getContinent();
			int getX();
			int getY();

			void setOwner(Player* player);
			void setNumberOfArmies(int numArmies);
			void setName(string newName);
			void setX(int newX);
			void setY(int newY);
			
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
			vector<Continent> continents;
			vector<Territory> countries; // Nodes
			vector<tuple<int,int>> borders; // Edges

			/* Check if continents are connected subgraphs if there exists an edge (set of borders) that contain the country number of each country belonging to a continent */
			

		public:
			Map();
			Map(const Map &m);
			Map(vector<Continent> continents, vector<Territory> countries, vector<tuple<int,int>> borders);

			// OPERATOR OVERLOADS
			Map &operator=(const Map &m);

			friend ostream &operator<<(ostream& out, const Map &m);
			
			// MEMBER FUNCTIONS
			vector<Continent> getContinents();
			vector<Territory> getTerritories();
			vector<tuple<int,int>> getBorders();

			vector<Territory> getTerritoriesByContinent(int continent);

			void setContinents(vector<Continent> continents);
			void setTerritories(vector<Territory> territories);
			void setBorders(vector<tuple<int,int>> borders);

			void addContinent(Continent continent);
			void addTerritory(Territory territory);
			void addBorder(tuple<int, int> border);

			~Map();

			void validate();
	};

	class MapLoader 
	{
		private:
		public:
			static Map createMapfromFile(string fileName);
			~MapLoader();
	};

	// TODO: Define custom Exception for Invalid Map Files

}
