// MapDriver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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

	Map testMap = MapLoader::createMapfromFile(fileName);

	// Display map properties
	/*cout << endl;
	cout << "MAP" << endl;
	cout << "===" << endl;
	cout << endl;
	cout << testMap << endl;
	
	// Display continents
	cout << endl;
	cout << "CONTINENTS" << endl;
	cout << "==========" << endl;
	cout << endl;

	for (Continent c : testMap.getContinents()) {
		cout << c << endl;
	}

	// Display countries
	cout << endl;
	cout << "TERRITORIES" << endl;
	cout << "===========" << endl;
	cout << endl;

	for (Territory t : testMap.getTerritories()) {
		cout << t << endl;
	}*/

	// TODO: Refine and test map validation
	testMap.validate();

	// CLEANUP
}
