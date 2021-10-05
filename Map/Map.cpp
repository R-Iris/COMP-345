#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <exception>
#include "Map.h"

using namespace std;

namespace MapSpace 
{
	// PLACEHOLDER FOR THE ACTUAL PLAYER CLASS
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
		this->adjacentCountries = nullptr;
		this->parent = 0;
		this->x = 0;
		this->y = 0;
	}

	Territory::Territory(const Territory &t) {
		this->owner = new Player(*(t.owner));
		this->numberOfArmies = t.numberOfArmies;
		this->countryIndex = t.countryIndex;
		//this->adjacentCountries = new vector<int>(*(t.adjacentCountries));
		this->name = t.name;
		this->parent = t.parent;
		this->x = t.x;
		this->y = t.y;
	}

	Territory::Territory(Player* owner, int numberOfArmies, int countryIndex, string name, int parent, int x, int y) {
		this->owner = new Player(*(owner));
		this->numberOfArmies = numberOfArmies;
		this->countryIndex = countryIndex;
		this->adjacentCountries = nullptr;
		this->name = name;
		this->parent = parent;
		this->x = x;
		this->y = y;
	}

	Territory::Territory(Player* owner, int numberOfArmies, int countryIndex, string name, int parent, vector<int>* adjacentCountries, int x, int y) {
		this->owner = new Player(*(owner));
		this->numberOfArmies = numberOfArmies;
		this->countryIndex = countryIndex;
		this->name = name;
		this->parent = parent;
		this->adjacentCountries = new vector<int>(*(adjacentCountries));
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

	Territory& Territory::operator=(const Territory& t) {
		this->owner = new Player(*(t.owner));
		this->numberOfArmies = t.numberOfArmies;
		this->countryIndex = t.countryIndex;
		this->adjacentCountries = new vector<int>(*(t.adjacentCountries));
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

	Player Territory::getOwner()
	{
		return (*this->owner);
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


	int Territory::getContinent()
	{
		return this->parent;
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
		this->owner = new Player(*(player));
	}

	void Territory::setNumberOfArmies(int numArmies)
	{
		this->numberOfArmies = numArmies;
	}

	void Territory::setName(string newName)
	{
		this->name = newName;
	}

	void Territory::setX(int newX)
	{
		this->x = newX;
	}

	void Territory::setY(int newY)
	{
		this->y = newY;
	}

	Territory::~Territory() {
		delete owner;
		owner = nullptr;
		/*delete adjacentCountries;
		adjacentCountries = nullptr;*/
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

	Map::Map() {
		this->continents = nullptr;
		this->countries = nullptr;
		//this->borders = nullptr;
	}

	Map::Map(const Map& m) {
		this->continents = new vector<Continent>(*(m.continents));
		this->countries = new vector<Territory>(*(m.countries));
		this->borders = m.borders;
	}

	Map::Map(vector<Continent>* continents, vector<Territory>* countries, vector<tuple<int, int>> borders) {
		this->continents = new vector<Continent>(*(continents));
		this->countries = new vector<Territory>(*(countries));
		this->borders = borders;
	}

	Map& Map::operator=(const Map& m) {
		this->continents = new vector<Continent>(*(m.continents));
		this->countries = new vector<Territory>(*(m.countries));
		this->borders = m.borders;

		return *this;
	}

	ostream& operator<<(ostream& out, const Map& m) {
		out << "MAP PROPERTIES : # of continents=" << m.continents->size() << ", # of countries=" << m.countries->size() << endl;
		return out;
	}

	vector<Continent> Map::getContinents() {
		return (*this->continents);
	}

	vector<Territory> Map::getTerritories()
	{
		return (*this->countries);
	}

	vector<tuple<int, int>> Map::getBorders()
	{
		return this->borders;
	}

	vector<Territory> Map::getTerritoriesByContinent(int continent)
	{
		vector<Territory> continentCountries;
		
		for (Territory t : *(this->countries)) {
			if (t.getContinent() == continent) {
				continentCountries.push_back(t);
			}
		}

		return continentCountries;
	}

	void Map::setContinents(vector<Continent>* continents)
	{
		this->continents = continents;
	}

	void Map::setTerritories(vector<Territory>* territories)
	{
		this->countries = territories;
	}

	void Map::setBorders(vector<tuple<int, int>> borders)
	{
		this->borders = borders;
	}

	void Map::addContinent(Continent continent)
	{
		(*this->continents).push_back(continent);
	}

	void Map::addTerritory(Territory territory)
	{
		(*this->countries).push_back(territory);
	}

	void Map::addBorder(tuple<int, int> border)
	{
		this->borders.push_back(border);
	}

	void Map::validate() {
		// Check if the map is a connected graph (invalid if there exists a node that is not connected to anything)
		for (Territory t : this->getTerritories()) {
			// There is an isolated node if that node does not share a border with any country.
			int borderCursor = 0;

			for (tuple<int, int> border : this->borders) {
				if (get<0>(border) == t.getIndex()) {
					// A border exists for this node! move on to the next node.
					break;
				}
				borderCursor++;
			}

			// At this point, we've gone through the entire borders collection without finding a border for our node.
			if (borderCursor == (int) this->borders.size()) {
				// Throw Invalid Map Exception - Isolated Node
				cout << "Map is invalid: Map cannot contain an isolated node." << endl;
				exit(EXIT_SUCCESS);
			}
		}

		// At this point, we can confirm that the map is a connected graph!

		// Check if continents are connected subgraphs (return a group of territories by continent index)
		// Loop through all defined continents
		for (Continent c : this->getContinents()) {

			// Return a group of countries by continent
			vector<Territory> continentCountries = this->getTerritoriesByContinent(c.getIndex());
			
			if (continentCountries.size() == 0) {
				// Throw exception, as there is a continent defined with no countries belonging to it
				cout << "Map is invalid: All continents must have at least one node." << endl;
				exit(EXIT_SUCCESS);

			}

			else if (continentCountries.size() > 1) {
				int cursor = 1;
				
				while (cursor <= (int) continentCountries.size()) {
					Territory left = continentCountries.at(cursor - 1);
					Territory right = (cursor == continentCountries.size()) ? continentCountries.at(0) : continentCountries.at(cursor);

					int borderCursor = 0;
					for (tuple<int, int> border : this->borders) {
						
						if ((get<0>(border) == left.getIndex() && get<1>(border) == right.getIndex()) ||
							(get<1>(border) == left.getIndex() && get<0>(border) == right.getIndex()))
						{
							// Break out of the loop as we have proven that the two countries are connected.
							break;
						}

						borderCursor++;
					}

					if (borderCursor == (int)this->borders.size()) {
						cout << "Territories that are not connected: " << left.getName() << " and " << right.getName() << endl;
						cout << "Map is invalid: All nodes within a continent must be connected." << endl;
						exit(EXIT_SUCCESS);
					}

					cursor++;
				}

				// At this point, we can say that all countries belonging to that continent are connected!
			}

			else {
				// If there is only one country in a continent, it technically is a connected subgraph
			}
		}

		// If the function exits without throwing an exception, we can say that the map is valid!
		cout << "This map is valid!" << endl;
	}

	Map::~Map() {
		delete continents;
		continents = nullptr;
		delete countries;
		countries = nullptr;
		/*delete borders;
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

						int index = stoi(continent);
						Continent c = tempContinents.at(stoi(continent) - 1);
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

						// TODO: Rework logic to use pointers to other countries instead of integer tuples.
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

		// Close ifstream
		mapFile.close();

		// Generate and return a map from the data received from the map file
		return Map(&tempContinents, &tempCountries, tempBorders);

		// TODO: Figure out what makes an invalid map file.
		// TODO: Implement custom Exception for Invalid Map Files
	}
}