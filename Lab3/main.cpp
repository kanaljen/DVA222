//
//  main.cpp
//  HashDictionary
//
//  Created by Staffan Brickman & Fredrik Ginsberg on 2019-02-12.
//  Copyright © 2019 kanaljen. All rights reserved.
//

#include "Geolocation.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

GeolocationDictionary readData();

int main(int argc, const char * argv[]) {
    
    GeolocationDictionary data = readData();
    getchar();
    return 0;
}

GeolocationDictionary readData()
{
    GeolocationDictionary dict;
    string line, delimiter = "\t";
    size_t roof, floor;
    ifstream file;
    file.exceptions ( ifstream::failbit );
    try
    {
        file.open("/Users/kanaljen/Documents/Code/HashDictionary/HashDictionary/cities100000.txt");
        while(getline(file,line))
        {
            float longitude, laltitude;
            string name;
            int population;
            floor = 0;
            // Read name
            roof = line.find(delimiter,floor);
            name = line.substr(floor,roof-floor);
            floor = roof+1;
            // Read longitude
            roof = line.find(delimiter,floor);
            longitude = stod(line.substr(floor,roof-floor));
            floor = roof+1;
            // Read laltitude
            roof = line.find(delimiter,floor);
            laltitude = stod(line.substr(floor,roof-floor));
            floor = roof+1;
            // Read laltitude
            roof = line.find(delimiter,floor);
            population = stoi(line.substr(floor,roof-floor-1));
            // Store in dict
            Geolocation geoloc(longitude,laltitude);
            City city(name,population);
            dict.append(geoloc, city);
        }
    }
    catch (const std::ifstream::failure& e)
    {
        std::cerr << "exception: " << "file error" << endl;
        exit(EXIT_FAILURE);
    }
    file.close();
    return dict;
}
