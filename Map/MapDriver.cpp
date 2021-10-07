/**
 * COMP 345: Advanced Program Design with C++
 * @file MapDriver.cpp
 * @author Jason Patel
 * @version 8/10/2021
 */

#include <iostream>
#include "Map.h"

using namespace std;
using namespace MapSpace;

int main()
{
	// VALID MAP FILES
	string fileName = "Assets/solar.map";
	//string fileName = "Assets/german-Empire1871.map";
	
	// INVALID MAP FILES
	//string fileName = "Assets/solar_with_empty_continent.map";
	//string fileName = "Assets/german_with_disconnected_continent.map";
	//string fileName = "Assets/solar_with_isolated_node.map";

	// Demonstrate that Player class works
	Player* p = new Player();

	Map* testMap = MapLoader::createMapfromFile(fileName);

	// Display map properties
	cout << endl;
	cout << "MAP" << endl;
	cout << "===" << endl;
	cout << endl;
	cout << *testMap << endl;
	
	// Display continents
	cout << endl;
	cout << "CONTINENTS" << endl;
	cout << "==========" << endl;
	cout << endl;

	for (Continent* c : testMap->getContinents()) {
		cout << *c << endl;
	}

	// Display countries
	cout << endl;
	cout << "TERRITORIES" << endl;
	cout << "===========" << endl;
	cout << endl;

	for (Territory* t : testMap->getTerritories()) {
		cout << *t << endl;
	}

	cout << "Map successfully generated from map file!" << endl;
	system("pause"); // Await user input before proceeding.

	testMap->validate();

	// CLEANUP
	delete testMap;
	delete p;
}
