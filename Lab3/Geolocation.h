#pragma once
#include "HashDictionary.h"
#include <cmath>


class Geolocation
{
public:
	Geolocation(float inputLongitude, float inputLatitude) :
		longitude(inputLongitude), latitude(inputLatitude) {}
	const float longitude;
	const float latitude;
	bool operator==(const Geolocation& other) // overides the == operator ot allow for comparison between keys
	{
		return (longitude == other.longitude) && (latitude == other.latitude);
	}
};

class City
{
public:
	City(std::string nameInput, int populationInput) :
		name(nameInput), population(populationInput) {}
	 std::string name;
	 int population;
};

class GeolocationDictionary : public HashDictionary<class Geolocation, class City> // note the choice of data classes using the template is done.
{
	int hashFunction(Geolocation inputLocation) override
	{
		return abs(int(inputLocation.latitude + inputLocation.longitude)) % TABLESIZE; // simple hash function
	}

	void printItem(City city) override // Necessary to make custom print methods for different data classes.
	{
		std::cout << "City: " << city.name.c_str() << " Population: " << city.population << std::endl;
	
	}

};

