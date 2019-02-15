# Assignment 3 - Hash dictionary
C# has a generic Dictionary<K,V> collection class that implements IDictionary<K,V> interface. According to MSDN: "The Dictionary class provides a mapping from a set of keys to a set of values. Each addition to the dictionary consists of a value and its associated key". The focus of this assignment is the use of generics, and the understanding of interfaces and interface inheritance by implementing and using your own `HashDictionary<K,V>` class.

This assignment consists of two parts:

### Part 1

In this part you will create your own `HashDictionary<K,V>` class that implements the IDictionary<K,V> interface. As the name suggests your implementation should be a proper hash table. In order to implement the IDictionary<K,V> interface you must understand and implement the ICollection<T> interface, and the IEnumerable<T> interface.

### Part 2

In this part you will be provided with a text file that contains a list of cities and their latitudes and longitudes. We want to use the recently created `HashDictionary<K,V>` class to map the latitude and longitude values to their corresponding locations, this helps us to easily find a city's name given its latitude and longitude.

The problem is that in this case, for every location the key is a pair of numbers. Therefore, the key itself should be a class that represents a `GeoLocation` consisting of a latitude and a longitude. Implement a class `GeoLocation` for this purpose. Make all the necessary functions and operator overloads to make it possible to use this class as a key for the `HashDictionary<K,V>` class.

The cities also contain information regarding their name and population. Therefore, another class for `City` is also needed. Implement a `City` class to encapsulate information regarding a `City`.

In the main, open the cities100000.txt file, read the information in it and add the data to the Map. Each row in the file contains the information for a city. The information is tab delimited and follows the following format:

`city name\t Lat\t Lon\t Population\n`

After creating the `HashDictionary<K,V>`, ask the user for a set of latitude and longitude. Use the `HashDictionary<K,V>` to find the location. If the location is found, print the name and population of the city otherwise print an error. Try to exchange your dictionary with the standard library Dictionary implementation. Is there any performance difference?

### Steps

To complete this assignment follow the steps below.

1. Study the interfaces you have to implement, IDictionary<K,V>, KeyValuePair<K,V>, ICollection<T>, IEnumerable<T>, and IEnumerator<T>.
2. Design your solution and discuss your solution with the assistants. The design is relatively straight forward this time, since it, to a large extent, is controlled by the demands of the interfaces.
3. Implement the assignment based on the design. Revise the design if needed - iteration may be necessary.
4. Demo your solution for one of the assistants and get an ok.
5. Send in your solution plus the class diagram on Canvas. Please package it using zip. Even though it may not be your first choice it makes it easier on my end.
6. Await feedback on your solution.

### Tips

* While IEnumerator<T> demands IDisposable it is ok to leave the Dispose method empty - whe have not talked about disposing objects. If you are interested you can read about Destructors in the programming guide.
* The Object class provides a GetHashCode method.
* You will need to use the KeyValuePair<K,V> structure to be compatible with the IDictionary<K,V> interface.
* For conflict resolving I suggest using chaining with a linked list - it's ok to use LinkedList<T>. See Hash table on Wikipedia if you need to refresh collision resolution.