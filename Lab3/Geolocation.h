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
    bool operator==(const Geolocation& other) {
        return (longitude == other.longitude) && (latitude == other.latitude);
    }
};

class GeolocationDictionary : public HashDictionary<class Geolocation, class City>
{
    int hashFunction(Geolocation inputLocation) override
    { return abs(int(inputLocation.latitude + inputLocation.longitude))%127; }
};

class City
{
public:
    City(std::string nameInput, int populationInput) :
    name(nameInput), population(populationInput) {}
    const std::string name;
    const int population;
};
