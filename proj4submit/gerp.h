/*
 *  gerp.h
 *  Charlie Biskupiak / Jack Edwards 
 *  April 23, 2023 
 *
 *  CS 15 Project Four, gerp 
 *  
 *  Implements all neccesary functions for the gerp class
 *  All functions will work together to make a functioning 
 *  file searcher. 
 *  This class interacts with both the HashTable and FSTree classes
 *  gerp.h combines and manipulates the two to make the searching 
 * possible
 *  As previously stated, this class does the "heavy lifting".
 *  It takes in all of the data and uses its functions to 
 *  perform all neccesary actions 
 *  The class has member variables for handling the files in a given
 * directory.
 * It relies heavily on an object of the hashtable class to store 
 * its data
 *  An instance of a "gerp" starts completely barren, there is 
 *  no constructor for it. Only when runGerp is called, then the 
 *  simulation begins and its member variables are initialized. 
 */

#ifndef _GERP_H_
#define _GERP_H_

#include "HashTable.h"
#include "FSTree.h"
#include "DirNode.h"
#include "stringProcessing.h"


#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <utility>

using namespace std; 

class Gerp
{
public:
    void makeVector(string name, string file); 
    void callQuery(); 
    
private: 
    void query(ofstream &output); 
    void treeTraversal(DirNode *root, string name);
    void makeHash();
    void sendToHash(string line, int fileNum, int lineNum);
    void report(vector <pair<int,int>> instances, ofstream &output); 
    void printInstances(vector<pair<int,int>> instances);
    void output();
    void runGerp(string name, string outputFile); 
    void makeFile(string path, string name); 
    void printVector(); 
    string specialCases(string s); 
    void toOutputNone(ofstream &output, string s, bool sensitive);

    struct file
    {
        string path; 
        vector<string> lines; 
    };
    string outputFile; 
    HashTable table; 
    vector <file> fileVect;
};

#endif