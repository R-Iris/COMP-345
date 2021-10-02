#pragma once

#include <iostream>
#include <vector>
#include <tuple>
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

			// DESTRUCTOR
			~Continent();

			// MEMBER FUNCTIONS
			string getName();
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

			/*Territory(Player* owner, int numberOfArmies, int countryIndex, string name, Continent* parent, int x, int y);
			Territory(Player* owner, int numberOfArmies, int countryIndex, string name, Continent* parent, vector<int>* adjacentCountries, int x, int y);
			Territory(int numberOfArmies, int countryIndex, string name, Continent* parent, int x, int y);
			Territory(int countryIndex, string name, Continent* parent, int x, int y);*/

			Territory(Player* owner, int numberOfArmies, int countryIndex, string name, int parent, int x, int y);
			Territory(Player* owner, int numberOfArmies, int countryIndex, string name, int parent, vector<int>* adjacentCountries, int x, int y);
			Territory(int numberOfArmies, int countryIndex, string name, int parent, int x, int y);
			Territory(int countryIndex, string name, int parent, int x, int y);

			// MEMBER FUNCTIONS
			void setOwner(Player* player);
			
			// DESTRUCTOR
			~Territory();
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
			vector<Continent> getContinents();
			Map(vector<Continent> continents, vector<Territory> countries, vector<tuple<int,int>> borders);
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
