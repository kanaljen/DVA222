//
//  main.cpp
//  HashDictionary
//
//  Created by Staffan Brickman & Fredrik Ginsberg on 2019-02-12.
//  Copyright © 2019 kanaljen. All rights reserved.
//

#include <iostream>
//#include "HashDictionary.h"
#include "Geolocation.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
using namespace System;


bool readFile(GeolocationDictionary& dict)
{
	ifstream infile;
	infile.open("cities100000.txt");
	if (infile.fail())
		return false;

	string bufferStringLine;
	string bufferName;
	string bufferLongitude;
	string bufferLatitude;
	string bufferPopulation;

	
	int cities = 0;

	while (!infile.eof()) // To get you all the lines.
	{
		getline(infile, bufferStringLine); // Saves the line in STRING.
		std::stringstream ss(bufferStringLine);
		getline(ss, bufferName, '\t');
		getline(ss, bufferLongitude, '\t');
		getline(ss, bufferLatitude, '\t');
		getline(ss, bufferPopulation, '\t');


		Geolocation geoloc(stof(bufferLongitude), stof(bufferLatitude));
		City city(bufferName.c_str(), stoi(bufferPopulation));
		dict.append(geoloc, city);
		cities++;
	}

	std::cout << "Number of cities added:" << cities << std::endl;

	return true;
}

int main(int argc, const char * argv[]) {

	GeolocationDictionary dict;
	//if (!readFile(dict)) return 1; // reads file and puts content into dict
	
	City city1("Stockholm", 32);
	City city2("Goteborg", 16);

	Geolocation geoloc1(-22, -33);
	Geolocation geoloc2(-22, -3);

	dict.append(geoloc1, city1);
	dict.append(geoloc2, city2);

	dict.printAll();

	try {
	
		City city3("Stockholm 2", 3225);
		
		dict[geoloc2].setm_value(city3);  // uses the hash of geoloc2 to rewrite the city class.
		
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "exception: " << e.what() << std::endl;
	}
	

	dict.printAll(); 


	
	try {
		City testcity1 = dict.get(geoloc1);
		std::cout << "City: " << testcity1.name.c_str() << " Population: " << testcity1.population << std::endl;
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "exception: " << e.what() << std::endl;
	} // shows that stockholm is added

	Geolocation geoloctest(31.22452, 75.77387); // corresponds to a city in cities100000.txt

	// code below pops an item depending on the key (aka geolocation).
	try {
		City testcity2 = dict.pop(geoloctest);
		std::cout << "City: " << testcity2.name.c_str() << " Population: " << testcity2.population << std::endl;
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "exception: " << e.what() << std::endl;
	}

	getchar();

	return 0;
}
