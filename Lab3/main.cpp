//
//  main.cpp
//  HashDictionary
//
//  Created by Staffan Brickman on 2019-02-12.
//  Copyright © 2019 kanaljen. All rights reserved.
//

#include <iostream>
#include "HashDictionary.h"
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, const char * argv[]) {
    HashDictionary<vector<int>, vector<char>> dict;
    vector<int> g1;
    for (int i = 1; i <= 5; i++)g1.push_back(i);
    vector<int> g2;
    for (int i = 1; i <= 5; i++)g2.push_back(i+1);
    vector<char> a;
    a.push_back('a');
    vector<char> b;
    b.push_back('b');
    dict.append(g1, a);
    dict.append(g1, a);
    dict.append(g2, b);
    dict.get(g2);
//    HashDictionary<char, int> dict;
//    dict.append('a', 1);
//    dict.append('b', 2);
//    dict.append('b', 0);
//    dict.append('d', 4);
//    dict.append('c', 3);
//
//    cout << dict.get('a') << endl;
//    cout << dict.get('d') << endl;
//    cout << dict.get('e') << endl;
//
//    dict.set('a',111);
//    dict.set('d',444);
//    dict.set('e',0);
//
//    dict.pop('b');
//    cout << dict.pop('a') << endl;
//    cout << dict.pop('d') << endl;
//    cout << dict.pop('e') << endl;
    
    return 0;
}
