/**
 * COMP 345: Advanced Program Design with C++
 * @file Map.cpp
 * @author Jason Patel
 * @version 8/10/2021
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <exception>
#include "Map.h"

using namespace std;


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

int Continent::getArmies() {
	return this->armies;
}

int Continent::getIndex()
{
	return this->continentIndex;
}

Continent::Continent(int continentIndex, string name, int armies) {
	this->continentIndex = continentIndex;
	this->name = name;
	this->armies = armies;
}

Continent& Continent::operator=(const Continent &c) {
	this->continentIndex = c.continentIndex;
	this->name = c.name;
	this->armies = c.armies;

	return *this;
}

ostream& operator<<(ostream &out, const Continent &c) {
	out << "Continent " << c.name << " with index " << c.continentIndex << " applies an army bonus of " << c.armies << " when a player controls all of its countries."  << endl;
	return out;
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

Territory::Territory(Player* owner, int numberOfArmies, int countryIndex, string name, int parent, int x, int y) {
	this->owner = owner;
	this->numberOfArmies = numberOfArmies;
	this->countryIndex = countryIndex;
	this->name = name;
	this->parent = parent;
	this->x = x;
	this->y = y;
}

Territory::Territory(Player* owner, int numberOfArmies, int countryIndex, string name, int parent, vector<Territory*> adjacentCountries, int x, int y) {
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
	this->x = x;
	this->y = y;
}

Territory& Territory::operator=(const Territory& t) {
	this->owner = t.owner;
	this->numberOfArmies = t.numberOfArmies;
	this->countryIndex = t.countryIndex;
	this->adjacentCountries = t.adjacentCountries;
	this->name = t.name;
	this->parent = t.parent;
	this->x = t.x;
	this->y = t.y;

	return *this;
}

int Territory::getIndex()
{
	return this->countryIndex;
}

Player* Territory::getOwner()
{
	return this->owner;
}

int Territory::getNumberOfArmies()
{
	return this->numberOfArmies;
}

string Territory::getName()
{
	return this->name;
}

ostream& operator<<(ostream& out, const Territory& t) {
	out << t.name << " is the country with index " << t.countryIndex << " and is located at position (" << t.x << ", " << t.y << ")." << endl;
	return out;
}

bool& operator==(const Territory& lhs, const Territory& rhs)
{
	bool toReturn = lhs.countryIndex == rhs.countryIndex;
	return toReturn;
}


int Territory::getContinent()
{
	return this->parent;
}

vector<Territory*> Territory::getAdjacentTerritories()
{
	return this->adjacentCountries;
}

int Territory::getX()
{
	return this->x;
}

int Territory::getY()
{
	return this->y;
}

void Territory::setOwner(Player* player) {
	this->owner = player;
}

void Territory::setNumberOfArmies(int numArmies)
{
	this->numberOfArmies = numArmies;
}

void Territory::setName(string newName)
{
	this->name = newName;
}

void Territory::setAdjacentTerritories(vector<Territory*> territories)
{
	this->adjacentCountries = territories;
}

void Territory::setX(int newX)
{
	this->x = newX;
}

void Territory::setY(int newY)
{
	this->y = newY;
}

void Territory::addAdjacentCountry(Territory* territory)
{
	this->adjacentCountries.push_back(territory);
}

// checks adjacency with passed territory
bool Territory::isAdjacent(Territory* territory)
{
	for (auto t : getAdjacentTerritories())
	{
		if (t == territory)
		{
			return true;
		}
	}
	return false;
}

Territory::~Territory() {
	adjacentCountries.clear();
}

// **************************************
// INVALID MAP EXCEPTION IMPLEMENTATION
// **************************************

const string InvalidMapException::error() const throw() {
	return " ";
}

// **************************************
// MAP IMPLEMENTATION
// **************************************

Map::Map() {}

Map::Map(const Map& m) {
	this->continents = m.continents;
	this->countries = m.countries;
	this->borders = m.borders;
	this->valid = m.valid;
}

Map::Map(vector<Continent*> continents, vector<Territory*> countries, vector<tuple<int, int>> borders) {
	this->continents = continents;
	this->countries = countries;
	this->borders = borders;
	this->valid = false;
}

Map& Map::operator=(const Map& m) {
	this->continents = m.continents;
	this->countries = m.countries;
	this->borders = m.borders;
	this->valid = m.valid;

	return *this;
}

ostream& operator<<(ostream& out, const Map& m) {
	out << "MAP PROPERTIES : # of continents=" << m.continents.size() << ", # of countries=" << m.countries.size() << endl;
	return out;
}

vector<Continent*> Map::getContinents()
{ 			
	return this->continents;
}

vector<Territory*> Map::getTerritories()
{
	return this->countries;
}

vector<tuple<int, int>> Map::getBorders()
{
	return this->borders;
}

bool Map::isValid()
{
	return valid;
}

vector<tuple<int, int>> Map::getBordersByCountry(Territory country)
{
	vector<tuple<int, int>> bordersByCountry;

	for (tuple<int, int> border : this->borders) {
		if (get<0>(border) == country.getIndex()) {
			bordersByCountry.push_back(border);
		}
	}

	return bordersByCountry;
}

vector<Territory*> Map::getTerritoriesByContinent(int continent)
{
	vector<Territory*> continentCountries;
		
	for (Territory* t : this->countries) {
		if (t->getContinent() == continent) {
			continentCountries.push_back(t);
		}
	}

	return continentCountries;
}

void Map::setContinents(vector<Continent*> continents)
{
	this->continents = continents;
}

void Map::setTerritories(vector<Territory*> territories)
{
	this->countries = territories;
}

void Map::setBorders(vector<tuple<int, int>> borders)
{
	this->borders = borders;
}

void Map::addContinent(Continent* continent)
{
	this->continents.push_back(continent);
}

void Map::addTerritory(Territory* territory)
{
	this->countries.push_back(territory);
}

void Map::addBorder(tuple<int, int> border)
{
	this->borders.push_back(border);
}

/**
	* FUNCTION: borderExists
	*
	* @param toCheck <vector<Territory*>>: A collection of nodes to be verified as being able to connect to the 'destination' node.
	* @param destination <Territory>: The node to connect to.
	* @param checked <vector<Territory>>: A collection of nodes which marks nodes that have already been traversed.
	* 
	* 
	* This function tests each node in toCheck to see if it can connect to the 'destination' node. If a node can connect to 'destination', then the function returns true and exits. Otherwise,
	* it is marked as traversed by being added to the 'checked' vector and then its adjacent nodes are verified. If all nodes in toCheck, as well as their adjacent nodes, fail to connect to
	* 'destination', then the function returns false.
	* 
	* @returns boolean: True if one of the nodes in 'toCheck' can connect to 'destination', false otherwise.
	*
	*/

bool Map::borderExists(vector<Territory*> toCheck, Territory destination, vector<Territory> checked)
{
	// If there are no more nodes to check, we must assume that no links to the destination exist.
	if (toCheck.size() == 0) {
		return false;
	}

	vector<Territory*> neighbours;

	// For each node in toCheck, check to see if it shares a border with the destination node
	for (Territory* t : toCheck) {
		// Only proceed if we have not checked this node already
		if (!territoryExists(checked, *t)) {
			for (tuple<int, int> border : this->getBordersByCountry(*t)) {
				if (get<1>(border) == destination.getIndex()) {
					// A border links the two nodes, hence they are connected.
					return true;
				}

				else {
					// Cross this node off our list of nodes to check
					checked.push_back(*t);

					// Add this node's neighbours to our list of nodes to check
					for (Territory* tr : t->getAdjacentTerritories()) {
						if (!territoryExists(checked, *tr)) { // If it hasn't been checked already
							neighbours.push_back(tr);
						}
					}
				}
			}
		}
	}

	return borderExists(neighbours, destination, checked);
}

/**
	* FUNCTION: validate
	*
	* This function validates the map instance it is tied to. It verifies the following: 
	* 1) The map is a connected graph.
	* 2) Each continent of the map is connected.
	*
	* Due to the format of the map files, the third requirement (that each territory belongs to a sole continent) is enforced, hence there is no need to verify this.
	* The function makes use of the helper method borderExists (see above function) to verify that the map is connected. It assumes that a map is connected if we can reach all nodes from a given
	* node, so if borderExists() returns true for each node, the map is a connected graph.
	*
	*
	* For the second requirement, the map's territories are subdivided into smaller graphs based on the continent they belong to. Then, for each subgraph, the process for 1) is applied. Unless
	* one of the borderExists() calls return false, all continents are connected subgraphs.
	*
	*
	*/
void Map::validate() {
	// This function takes a while to complete, so let the user know that things are moving along.
	cout << "Validating map..." << endl;

	if (countries.size() < 1 || continents.size() < 1 || borders.size() < 1) {
		cout << "Map cannot be empty, please ensure that the map file provided actually exists." << endl;
		return;
	}

	vector<Territory> checked;

	// Check if the map is a connected graph (invalid if there exists a node that is not connected to anything)
	Territory* node1 = this->countries.at(0);

	for (Territory* t : this->getTerritories()) {
		// We want to check all other nodes
		if (node1 != t) {
			cout << "Checking: " << node1->getIndex() << ", " << t->getIndex() << endl;
			vector<Territory*> tmp;
			tmp.push_back(node1);
			if (!borderExists(tmp, *t, checked)) {
				// Throw Invalid Map Exception - Isolated Node
				cout << "Map is invalid: Map cannot contain an isolated node." << endl;
				exit(EXIT_SUCCESS);
			}

			else {
				cout << "Link established!" << endl;
			}
		}
	}
		
	// At this point, we can confirm that the map is a connected graph!
	// Check if continents are connected subgraphs (return a group of territories by continent index)
		
	// Loop through all defined continents
	for (Continent* c : this->getContinents()) {
		cout << "Validating continent " << c->getIndex() << endl;
		vector<Territory*> continentCountries = this->getTerritoriesByContinent(c->getIndex());

		if (continentCountries.size() == 0) {
			// Throw exception, as there is a continent defined with no countries belonging to it
			cout << "Map is invalid: All continents must have at least one node." << endl;
			exit(EXIT_SUCCESS);

		}
			
		else if (continentCountries.size() > 1) {
			Territory* startNode = continentCountries.at(0);
			vector<Territory*> tmp;
			tmp.push_back(startNode);

			for (Territory* t : continentCountries) {
				vector<Territory> checked;
				if (!borderExists(tmp, *t, checked)) {
					cout << "Map is invalid: All nodes within a continent must be connected." << endl;
					cout << "Territories that are not connected: " << startNode->getName() << " and " << t->getName() << endl;
					exit(EXIT_SUCCESS);
				}
			}
		}
			
		else {
			// If there is only one country in a continent, it technically is a connected subgraph
		}
	}

	// If the function exits without throwing an exception, we can say that the map is valid!
	cout << "This map is valid!" << endl;
	valid = true;
}

int Map::calculateContinentBonus(Player* player)
{
	int continentBonus = 0;
	for (Continent* c : getContinents()) {
		bool pHasAllT = true;
		for (Territory* t : getTerritoriesByContinent(c->getIndex())) {
			if (!player->ownsTerritory(t)) {
				pHasAllT = false;
			}
		}
		if (pHasAllT) {
			continentBonus = continentBonus + c->getArmies();
		}
	}
	return continentBonus;
}

bool Map::territoryExists(vector<Territory> collection, Territory toFind)
{
	for (Territory t : collection) {
		if (t == toFind) {
			return true;
		}
	}

	return false;
}

Map::~Map() {
	for (int i = 0; i < continents.size(); i++) {
		delete continents.at(i);
		continents.at(i) = NULL;
	}
	continents.clear();

	for (int j = 0; j < countries.size(); j++) {
		delete countries.at(j);
		countries.at(j) = NULL;
	}
	countries.clear();
}

//Method for Player class
Territory* Map::getTerritoryByIndex(int index) {
    for(auto it: getTerritories()){
        if(it->getIndex() == index){
            return it;
        }
    }
    return nullptr;
}

// **************************************
// MAPLOADER IMPLEMENTATION
// **************************************

/**
	* FUNCTION: createMapfromFile
	* 
	* @param mapFileName <string>: The path to the map file to be read.
	*
	* Upon recieving a path to a map file, this function opens the file and begins parsing the file for data which it can then use to create a map. The function begins
	* by searching for a section header line (such as '[continents]', '[countries]' and '[borders]'). It then assumes every line that follows (until a blank line is read, in which case, 
	* it looks for another header line.) contains relevant data to the section it is in and reads each line before storing the object created from the data in the line in its proper vector.
	* Once all the vectors have been populated, a map is created using all of the vectors and returned upon exit.
	*
	*
	* @returns m <Map*>: The map that has been created based on the data in the provided map file.
	* 
	*/
Map* MapLoader::createMapfromFile(string mapFileName) {
	// Open the file
	ifstream mapFile(mapFileName);
	string currentLine;
	string delimiter = " ";
	int currentContinent = 0;

	// Vectors to store the data retrieved from the map file
	vector<Continent*> tempContinents;
	vector<Territory*> tempCountries;
	vector<tuple<int, int>> tempBorders;

	// Parse the file to create the map, use the headers to jump to different points in the file

	// TODO: Add try-catch block
	try {
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

						Continent* c = new Continent(currentContinent, name, stoi(armyValue));
						tempContinents.push_back(c);
					}
				}

				//cout << "Continents read!" << endl;
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

						Territory* t = new Territory(stoi(countryNumber), countryName, stoi(continent), stoi(x), stoi(y));
						tempCountries.push_back(t);
					}
				}

				//cout << "Countries read!" << endl;
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

						while (offset < (int)currentLine.length()) {
							string sharedBorder = currentLine.substr(offset, currentLine.find(delimiter, offset) - offset);
							adjCountries.push_back(sharedBorder);
							offset += sharedBorder.length() + delimiter.length();
						}

						for (string s : adjCountries)
						{
							// Add edge tuple to the map
							tuple<int, int> edge = { stoi(countryNumber), stoi(s) };
							tempBorders.push_back(edge);

							// Add territory pointer to the current node
							tempCountries.at(stoi(countryNumber) - 1)->addAdjacentCountry(tempCountries.at(stoi(s) - 1));
						}
					}
				}

				//cout << "Borders read!" << endl;
			}
		}

		// We've finished reading the file, close it.
		mapFile.close();

		// Generate and return a map from the data read from the map file
		Map* m = new Map(tempContinents, tempCountries, tempBorders);
		return m;
	}

	catch (const exception& e) {
		cout << e.what() << endl;
		exit(1);
		//return NULL;
	}
}