#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include "Map.h"

using namespace std;

namespace MapSpace 
{
	Player::Player() {

	}

	Player::~Player() {

	}

	// **************************************
	// CONTINENT IMPLEMENTATION
	// **************************************

	Continent::Continent() {
		this->continentIndex = 0;
		this->name = "";
		this->armies = 0;
	}

	Continent::Continent(const Continent &c) {
		this->continentIndex = c.continentIndex;
		this->name = c.name;
		this->armies = c.armies;
	}

	string Continent::getName() {
		return this->name;
	}

	Continent::Continent(int continentIndex, string name, int armies) {
		this->continentIndex = continentIndex;
		this->name = name;
		this->armies = armies;
	}

	Continent::~Continent() {

	}
	
	// **************************************
	// TERRITORY IMPLEMENTATION
	// **************************************

	Territory::Territory() {
		this->owner = nullptr;
		this->numberOfArmies = 0;
		this->countryIndex = 0;
		this->name = "";
		this->adjacentCountries = nullptr;
		//this->parent = nullptr;
		this->parent = 0;
		this->x = 0;
		this->y = 0;
	}

	Territory::Territory(const Territory &t) {
		this->owner = t.owner;
		this->numberOfArmies = t.numberOfArmies;
		this->countryIndex = t.countryIndex;
		this->adjacentCountries = t.adjacentCountries;
		this->name = t.name;
		this->parent = t.parent;
		this->x = t.x;
		this->y = t.y;
	}

	/*Territory::Territory(Player* owner, int numberOfArmies, int countryIndex, string name, Continent* parent, int x, int y) {
		this->owner = owner;
		this->numberOfArmies = numberOfArmies;
		this->countryIndex = countryIndex;
		this->adjacentCountries = nullptr;
		this->name = name;
		this->parent = parent;
		this->x = x;
		this->y = y;
	}

	Territory::Territory(Player* owner, int numberOfArmies, int countryIndex, string name, Continent* parent, vector<int>* adjacentCountries, int x, int y) {
		this->owner = owner;
		this->numberOfArmies = numberOfArmies;
		this->countryIndex = countryIndex;
		this->name = name;
		this->parent = parent;
		this->adjacentCountries = adjacentCountries;
		this->x = x;
		this->y = y;
	}

	Territory::Territory(int numberOfArmies, int countryIndex, string name, Continent* parent, int x, int y) {
		this->owner = nullptr;
		this->numberOfArmies = numberOfArmies;
		this->countryIndex = countryIndex;
		this->name = name;
		this->adjacentCountries = nullptr;
		this->parent = parent;
		this->x = x;
		this->y = y;
	}

	Territory::Territory(int countryIndex, string name, Continent* parent, int x, int y) {
		this->owner = nullptr;
		this->numberOfArmies = 0;
		this->countryIndex = countryIndex;
		this->name = name;
		this->parent = parent;
		this->adjacentCountries = nullptr;
		this->x = x;
		this->y = y;
	}*/

	Territory::Territory(Player* owner, int numberOfArmies, int countryIndex, string name, int parent, int x, int y) {
		this->owner = owner;
		this->numberOfArmies = numberOfArmies;
		this->countryIndex = countryIndex;
		this->adjacentCountries = nullptr;
		this->name = name;
		this->parent = parent;
		this->x = x;
		this->y = y;
	}

	Territory::Territory(Player* owner, int numberOfArmies, int countryIndex, string name, int parent, vector<int>* adjacentCountries, int x, int y) {
		this->owner = owner;
		this->numberOfArmies = numberOfArmies;
		this->countryIndex = countryIndex;
		this->name = name;
		this->parent = parent;
		this->adjacentCountries = adjacentCountries;
		this->x = x;
		this->y = y;
	}

	Territory::Territory(int numberOfArmies, int countryIndex, string name, int parent, int x, int y) {
		this->owner = nullptr;
		this->numberOfArmies = numberOfArmies;
		this->countryIndex = countryIndex;
		this->name = name;
		this->adjacentCountries = nullptr;
		this->parent = parent;
		this->x = x;
		this->y = y;
	}

	Territory::Territory(int countryIndex, string name, int parent, int x, int y) {
		this->owner = nullptr;
		this->numberOfArmies = 0;
		this->countryIndex = countryIndex;
		this->name = name;
		this->parent = parent;
		this->adjacentCountries = nullptr;
		this->x = x;
		this->y = y;
	}


	void Territory::setOwner(Player* player) {
		this->owner = player;
	}

	Territory::~Territory() {
		/*delete owner;
		owner = nullptr;
		delete parent;
		parent = nullptr;
		delete adjacentCountries;
		adjacentCountries = nullptr;*/
	}

	// **************************************
	// MAP IMPLEMENTATION
	// **************************************

	Map::Map() {
		/*this->continents = nullptr;
		this->countries = nullptr;
		this->borders = nullptr;*/
	}

	Map::Map(const Map& m) {
		this->continents = m.continents;
		this->countries = m.countries;
		this->borders = m.borders;
	}

	Map::Map(vector<Continent> continents, vector<Territory> countries, vector<tuple<int, int>> borders) {
		this->continents = continents;
		this->countries = countries;
		this->borders = borders;
	}

	vector<Continent> Map::getContinents() {
		return this->continents;
	}

	void Map::validate() {
		// TODO: Add actual validation logic!!!
	}

	Map::~Map() {
		/*delete continents;
		continents = nullptr;
		delete countries;
		countries = nullptr;
		delete borders;
		borders = nullptr;*/
	}

	// **************************************
	// MAPLOADER IMPLEMENTATION
	// **************************************

	Map MapLoader::createMapfromFile(string mapFileName) {
		// Open the file
		ifstream mapFile(mapFileName);
		string currentLine;
		string delimiter = " ";
		int currentContinent = 0;

		// Vectors to store the data retrieved from the map file
		vector<Continent> tempContinents;
		vector<Territory> tempCountries;
		vector<tuple<int, int>> tempBorders;

		// Parse the file to create the map, use the headers to jump to different points in the file
		while (getline(mapFile, currentLine)) {
			if (currentLine == "[continents]") {

				while (getline(mapFile, currentLine)) {
					// An empty line marks the end of that section
					if (currentLine == "") {
						break;
					}

					else {
						// Get continent fields
						currentContinent++;
						string name = currentLine.substr(0, currentLine.find(delimiter));
						
						int offset = name.length() + delimiter.length();

						string armyValue = currentLine.substr(offset, currentLine.find(delimiter, offset));

						// TODO: Create Continent and add it to the vector.
						Continent c(currentContinent, name, stoi(armyValue));
						tempContinents.push_back(c);
					}
				}

				cout << "Continents read!" << endl;
			}

			else if (currentLine == "[countries]") {
				// Read every line in the countries section of the text file
				while (getline(mapFile, currentLine)) {
					// An empty line marks the end of that section
					if (currentLine == "") {
						break;
					}

					else {
						// Get country fields
						int offset = 0;

						string countryNumber = currentLine.substr(0, currentLine.find(delimiter, offset)); // Number
						offset += countryNumber.length() + delimiter.length();

						string countryName = currentLine.substr(offset, currentLine.find(delimiter, offset) - offset); // Name
						offset += countryName.length() + delimiter.length();

						string continent = currentLine.substr(offset, currentLine.find(delimiter, offset) - offset); // Continent that it's on
						offset += continent.length() + delimiter.length();

						string x = currentLine.substr(offset, currentLine.find(delimiter, offset) - offset); // X position
						offset += x.length() + delimiter.length();

						string y = currentLine.substr(offset, currentLine.find(delimiter, offset) - offset); // Y position

						// TODO: Create Territory and add it to the vector
						int index = stoi(continent);
						Continent c = tempContinents.at(stoi(continent) - 1);
						//Territory t(stoi(countryNumber), countryName, &c, stoi(x), stoi(y));
						//Territory t(stoi(countryNumber), countryName, &c, stoi(x), stoi(y));
						//tempCountries.push_back(Territory(stoi(countryNumber), countryName, &(tempContinents.at(stoi(continent) - 1)), stoi(x), stoi(y)));
						tempCountries.push_back(Territory(stoi(countryNumber), countryName, stoi(continent), stoi(x), stoi(y)));
					}
				}

				cout << "Countries read!" << endl;
			}

			else if (currentLine == "[borders]") {
				while (getline(mapFile, currentLine)) {
					// An empty line marks the end of that section
					if (currentLine == "") {
						break;
					}

					else {
						// Get border fields
						int offset = 0;
						string countryNumber = currentLine.substr(0, currentLine.find(delimiter) - offset);

						offset += countryNumber.length() + delimiter.length();

						vector<string> adjCountries;

						while (offset < (int) currentLine.length()) {
							string sharedBorder = currentLine.substr(offset, currentLine.find(delimiter, offset) - offset);
							adjCountries.push_back(sharedBorder);
							offset += sharedBorder.length() + delimiter.length();
						}

						// TODO: Create an edge between the country (belonging to the number) and each adjacent country and add it to the vector
						for (string s : adjCountries)
						{
							tuple<int,int> edge = { stoi(countryNumber), stoi(s) };
							tempBorders.push_back(edge);
						}
					}
				}

				cout << "Borders read!" << endl;
			}
		}

		return Map(tempContinents, tempCountries, tempBorders);
		// TODO: Figure out what makes an invalid map file.
		// TODO: Implement custom Exception for Invalid Map Files
	}
}