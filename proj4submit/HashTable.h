/*
 *  HashTable.h 
 *  Charlie Biskupiak / Jack Edwards 
 *  April 23, 2023 
 *
 *  CS 15 Project Four, Gerp 
 *  
 *  Header file for the HashTable class. Declares all of the 
 *  functions that the class will use. 
 *  A HashTable is an array of buckets that hold words. 
 *  This class would work as a storage for any type of object, which could 
 *  be useful for other projects or data structures. For this project, it 
 *  is used for storing words and data about those words
 *  To handle collisions, chaining is employed (pointing two objects in the 
 *  same bucket to eachother, basically creating a linked list.
 *  Each instance of a Hashtable starts empty with 100 indices 
 *  and is then added to by either a client or another function. 
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H


#include "FSTree.h"
#include "DirNode.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std; 
using std::vector;

class HashTable {
private: 
    struct instance {
        int lineNumber; 
        int fileIndex; 
    };
    struct bucket {
        string key; 
        vector <instance> instances;  
        bucket *next; 
    };
    bucket* *hashTable; 

    int size; 
    int active; 

    void containsInstance(string s, int fileNum, int lineNum);
    void deleteLists(bucket *buck); 
    void reHash(bucket *b, int i, int j, bucket* *newHash);
    int listSize(bucket *b); 
    void insert(bucket *b, bucket* *newHash); 
   

public: 
    int getSize();
    int getActive();
    void printTable();
    void printVector(string key);
    

    HashTable(); 
    ~HashTable(); 
    int getIndex(string s); 
    void checkHash(); 
    vector<instance> getInstancesCS(string key); 
    vector<instance> getInstancesNCS(string key); 
    void insert(string s, int fileNum, int lineNum); 
    bool contains(string key); 
    vector<pair<int,int>> search(string key, bool sensitive); 
};

#endif