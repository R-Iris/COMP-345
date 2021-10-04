// MapDriver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Map.h"

using namespace std;
using namespace MapSpace;

int main()
{
	// TODO: Test MapLoader class

	//string fileName = "Assets/solar.map";
	//string fileName = "Assets/german-Empire1871.map";
	//string fileName = "Assets/solar_with_empty_continent.map";
	//string fileName = "Assets/german_with_disconnected_continent.map";
	string fileName = "Assets/solar_with_isolated_node.map";

	Map testMap = MapLoader::createMapfromFile(fileName);
	cout << endl;
	cout << "CONTINENTS" << endl;
	cout << "==========" << endl;
	cout << endl;
	for (Continent c : testMap.getContinents()) {
		cout << c.getName() << endl;
	}

	testMap.validate();
}
