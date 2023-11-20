/*
 *  HashTable.cpp
 *  Charlie Biskupiak / Jack Edwards 
 *  April 23, 2023 
 *
 *  CS 15 Project Four, Gerp
 *  
 *  Implements a HashTable class for buckets of words, an instance of this 
 * class will be used to store instances of words in the files gerp reads in
 *  They will hold all of the words in "key based search" where in order to
 * access a word's index, the key is run thru a hash function 
 *  This class is best used as a way to store data that needs to be retrieved 
 * quickly and by its name, like how gerp wants it to be done 
 */

#include "HashTable.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <functional>
#include <algorithm>
#include <cctype>

using namespace std; 
using std::vector;

//CONSTRUCTOR 
HashTable::HashTable(){ 
    hashTable = new bucket*[100]; 
    size = 100; 
    active = 0; 
    for(int i = 0; i < 100; i++) {
        hashTable[i] = nullptr; 
    }
} 

//DESTRUCTOR
HashTable::~HashTable(){
    for(int i = 0; i < size; i++) {
        deleteLists(hashTable[i]); 
    } 
    delete [] hashTable; 
} 

/*
 * name:  deleteLists 
 * purpose: deletes the possible linked lists in the hashtable buckets
 * arguments: current bucket being worked on (recursively) 
 * returns: none
 * effects: deletes buckets 
 */
void HashTable::deleteLists(bucket *currBuck){
    if(currBuck == nullptr) {return;}
    else{deleteLists(currBuck->next);}
    delete currBuck; 
}

//returns the size --> for testing purposes
int HashTable::getSize() {return size;}

//returns the number of active slots --> for testing purposes
int HashTable::getActive() {return active;}


/*
 * name:  listSize 
 * purpose: returns the number of buckets in one hashtable index
 * arguments: first bucket in the index
 * returns: number of buckets behind it 
 * effects: none 
 * 
*/
int HashTable::listSize(bucket *b) {
    int counter = 0; 
    while(b != nullptr) {
        counter++;
        b = b->next; 
    }
    return counter;
}

/*
 * name:  getIndex 
 * purpose: returns a word's expected index
 * arguments: word 
 * returns: hashtable expected index 
 * effects: none 
 */
int HashTable::getIndex(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    int index = hash<string>{}(s) % size;
    return index; 
}

/*
 * name:  getInstancesCS 
 * purpose: returns a word's list of instances (case sensitive)
 * arguments: word
 * returns: vector of its instances 
 * effects: none
 */
vector<HashTable::instance> HashTable::getInstancesCS(string key) {
    vector<instance> empty;
    int index = getIndex(key);
    bucket *currBucket = hashTable[index]; 
    bool correctBucket = false; 
    while(not correctBucket) { //move to the correct bucket pointer
        if(currBucket == nullptr) {return empty;} //KEY DOESNT EXIST ***
        else if(currBucket->key == key) {correctBucket = true;} 
        else {currBucket = currBucket->next;}
    } 
    return currBucket->instances; 
}

/*
 * name:  getInstancesNCS 
 * purpose: returns a word's list of instances (case sensitive)
 * arguments: word
 * returns: vector of its instances 
 * effects: none
 */
vector<HashTable::instance> HashTable::getInstancesNCS(string key) {
    vector <instance> instancez; 
    int index = getIndex(key); 
    transform(key.begin(), key.end(), key.begin(), ::tolower);
    string s; 
    bucket *currBucket = hashTable[index]; 
    int length = listSize(currBucket);
    int vectSize; 
    for(int i = 0; i < length; i++) {
        s = currBucket->key;
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        if(s == key) {
            vectSize = currBucket->instances.size(); 
            for(int j = 0; j < vectSize; j++) {
                instancez.push_back(currBucket->instances.at(j));
            }
        }
        currBucket = currBucket->next; 
    }
    return instancez; 
}

/*
 * name:  contains
 * purpose: checks to see if a word exists in the hashtable 
 * arguments: word 
 * returns: boolean --> if word is in table or not  
 * effects: none
 */
bool HashTable::contains(string key) {
    bucket *currBucket = hashTable[getIndex(key)]; 
    while(currBucket != nullptr) {
        if(currBucket->key == key) {
            return true; 
        } else {
            currBucket = currBucket->next; 
        }
    }
    return false; 
}

/*
 * name:  checkHash 
 * purpose: checks load factor on array and expands if needed 
 * arguments: none
 * returns: none 
 * effects: could expand table and rehash all elements 
 */
void HashTable::checkHash() {
    float percentage = (float) active / (float) size; 
    if(percentage >= .70) {
        int oldSize = size; 
        int length; 
        size = size * 2 + 2;
        bucket* *newHash = new bucket*[size]; 
        for(int i = 0; i < size; i++) {
            newHash[i] = nullptr; 
        }
        for(int i = 0; i < oldSize; i++) {//for each index 
            length = listSize(hashTable[i]); 
            reHash(hashTable[i], 0, length, newHash); 
        }
        delete [] hashTable; 
        hashTable = newHash; 
    }
}

/*
 * name:  reHash 
 * purpose: reHashes an entire hashTable index
 * arguments: current bucket pointer in index, counter, limit to counter, 
 * hashtable to add to 
 * returns: none 
 * effects: rearranges buckets in hashtable 
 */
void HashTable::reHash(bucket *b, int counter, int length, bucket* *newHash) {
    bucket *next; 
    if(counter == length) {
        return; 
    } else {
        next = b->next; 
        insert(b, newHash); 
        counter++; 
        reHash(next, counter, length, newHash); 
    }
}

/*
 * name:  insert (bucket) 
 * purpose: adds a bucket to the hashtable
 * arguments: bucket and hashtable to send it to
 * returns: none 
 * effects: rearranges buckets in hashtable 
 */
void HashTable::insert(bucket *b, bucket* *newHash) { 
    int index = getIndex(b->key); 
    b->next = newHash[index]; 
    newHash[index] = b; 
}

/*
 * name:  insert 
 * purpose: adds a new word to the hashTable 
 * arguments: word, file where it was found and on what line 
 * returns: none 
 * effects: adds a new word to the hash table 
 */
void HashTable::insert(string s, int fileNum, int lineNum) {
    int index = getIndex(s); 
    bucket *currBucket; 
    if(contains(s)) {//word has been defined already 
        bool correctBucket = false; 
        currBucket = hashTable[index]; 
        while(not correctBucket) { //move to the correct bucket pointer
            if(currBucket == nullptr) {return;} //KEY DOESNT EXIST ***
            else if(currBucket->key == s) {correctBucket = true;} 
            else {currBucket = currBucket->next;}
        }
        instance newInstance; 
        newInstance.fileIndex = fileNum; 
        newInstance.lineNumber = lineNum; 
        currBucket->instances.push_back(newInstance); 
    } else { //new word 
        bucket *newBucket = new bucket; 
        newBucket->next = hashTable[index]; 
        hashTable[index] = newBucket;
        newBucket->key = s; 
        instance newInstance;
        newInstance.fileIndex = fileNum; 
        newInstance.lineNumber = lineNum; 
        newBucket->instances.push_back(newInstance);
        active++;
        checkHash(); 
    }
}

/*
 * name:  performSearch 
 * purpose: finds an reports instances of a given word in a directory
 * arguments: word, if the search is case sensitive
 * returns: a vector of pairs (instances) for the gerp to use 
 * effects: none
 */
vector<pair<int,int>> HashTable::search(string key, bool sensitive) {
    vector <pair<int,int>> instances;
    vector<instance> instancez; 
    if(sensitive) {instancez = getInstancesCS(key);} 
    else {instancez = getInstancesNCS(key);}
    int length = instancez.size(); 
    instance currInst; 
    for(int i = 0; i < length; i++) {
        currInst = instancez.at(i); 
        pair<int, int> newPair; 
        if(sensitive) {
            newPair.first = currInst.fileIndex; 
            newPair.second = currInst.lineNumber;
            instances.push_back(newPair); 
        } else {
            int length2 = instances.size(); 
            bool sendable = true; 
            for(int j = 0; j < length2; j++) {
                if(currInst.fileIndex == instances.at(j).first) {
                    if(currInst.lineNumber == instances.at(j).second){
                        sendable = false; 
                    }
                }
            } if(sendable) {
                newPair.first = currInst.fileIndex;
                newPair.second = currInst.lineNumber; 
                instances.push_back(newPair); 
            }
        }
    } return instances; 
}


//prints a key's instances vector --> for visual testing purposes
void HashTable::printVector(string key) {
    vector<instance> vect = getInstancesCS(key); 
    vector<instance> vect2 = getInstancesNCS(key); 
    int vectSize = vect.size(); 
    int vect2Size = vect2.size(); 
    cout << "CASE SENSITIVE:" << endl; 
    cout << key << " "; 
    for(int i = 0; i < vectSize; i++) {
        cout << " --> ";
        cout << "(File Index, Line Number) "; 
        cout << vect.at(i).fileIndex; 
        cout << ", " << vect.at(i).lineNumber; 
    }
    cout << endl << endl << endl; 
    cout << "NON CASE SENSITIVE:" << endl; 
    cout << key << " "; 
    for(int i = 0; i < vect2Size; i++) {
        cout << " --> ";
        cout << "(File Index, Line Number) "; 
        cout << vect2.at(i).fileIndex; 
        cout << ", " << vect2.at(i).lineNumber; 
    }
    cout << endl; 
}

//prints table --> for visual testing purposes
void HashTable::printTable() {
    bucket *currBuck; 
    for(int i = 0; i < size; i++) {
        currBuck = hashTable[i]; 
        cout << i << " "; 
        while(currBuck != nullptr) {
            cout << "--> " << currBuck->key << " ";
            currBuck = currBuck->next;
        }
        cout << endl; 
    }
    printVector("grep"); //ran a test on case sensitivity in terminal
}

