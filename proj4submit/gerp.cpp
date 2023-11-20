/*
 *  gerp.cpp
 *  Charlie Biskupiak / Jack Edwards 
 *  April 23, 2023 
 *
 *  CS 15 Project Four, gerp
 *  
 * Contains the functions and their definitions for the gerp class. 
 * The file is organized so that as the program 
 * progresses, the file can be read from top to bottom. 
 * This file will be called by the main driver and run the entire program
 * The files will be read in, and the class will immediately set up 
 * the vector and hashtable, then the user will input 
 * a command, and then the turn will commence. 
 * 
 * When instantiating this class, it is imperative that the program has 
 * an input directory to go along with it. The entire program (especially its
 * data structures) relies on the amount of file there are. 
 * In order to run a successful search, the input directory must be readable,
 * and all user inputs from cin or a command file must be correct. 
 */

#include "gerp.h"
#include "HashTable.h"
#include "stringProcessing.h"

#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <utility>


using namespace std; 

/*
 * name:  makeVector 
 * purpose: takes all files from a given directory and puts them into a vector
 * arguments: name of the directory
 * returns: none 
 * effects: none 
 */
void Gerp::makeVector(string directory, string file) {
    outputFile = file; 
    FSTree direct(directory); 
    DirNode *root = direct.getRoot(); 
    string name = root->getName(); 
    name += "/";
    treeTraversal(root, name); 
    makeHash(); 
}

/*
 * name:  treeTraversal 
 * purpose: finds files in a directory
 * arguments: primary directory, the printable handle
 * returns: none (technically) 
 * effects: none 
 */
void Gerp::treeTraversal(DirNode *root, string handle) {
    string newHandle; 
    string name; 
    for(int i = 0; i < root->numSubDirs(); i++) {
        newHandle = handle; 
        newHandle += root->getSubDir(i)->getName(); 
        newHandle += "/"; 
        treeTraversal(root->getSubDir(i), newHandle); 
    } 
    for(int i = 0; i < root->numFiles(); i++) {
        name = root->getFile(i); 
        makeFile(handle, name);
    }
}

/*
 * name:  makeFile 
 * purpose: makes a new instance of a file and pushes it onto the vector
 * arguments: the path of the file and its name to be read into infile
 * returns: none (technically) 
 * effects: adds to the file vector  
 * 
 * Commented out lines are for the unit tests 
 */
void Gerp::makeFile(string path, string name) {
    file newFile; 
    ifstream infile; 
    newFile.path = path + name; 
    //cout << newFile.path << endl; --> unit testing 
    vector<string> lines; 
    infile.open(newFile.path); 
    if(not infile.is_open()) {
        cerr<<"Error: could not open file "<< endl;
        exit(EXIT_FAILURE);
    }
    string currLine; 
    while(not infile.eof()) {
        getline(infile, currLine);
        //cout << currLine << endl; --> unit testing 
        lines.push_back(currLine);
    }
    newFile.lines = lines; 
    fileVect.push_back(newFile);
}

/*
 * name:  makeHash 
 * purpose: adds all words from files to the hashTable 
 * arguments: none
 * returns: none 
 * effects: fills hash table  
 */
void Gerp::makeHash(){
    int size = fileVect.size(); //for each file...
    int size2; 
    string s; 
    stringstream ss; 
    for(int i = 0; i < size; i++) {// i = fileNum 
        size2 = fileVect.at(i).lines.size(); 
        for(int j = 0; j < size2; j++) { //j = lineNum
            if(fileVect.at(i).lines.at(j) != "") {
                sendToHash(fileVect.at(i).lines.at(j), i, j + 1); 
            } 
        }
    }
}

//NOTE: FILE LINES START AT INDEX TWO ON DEMO --> ADD ONE 
/*
 * name:  sendToHash 
 * purpose: adds all words from line to the hashTable 
 * arguments: line, index of file that word was taken from, linenumber of word
 * returns: none 
 * effects: fills hash table  
 */
void Gerp::sendToHash(string line, int fileNum, int lineNum) {
    vector<string> words; 
    int size;
    string s; 
    bool sendable;
    stringstream ss(line); 
    while(not ss.eof()) {
        sendable = true; 
        ss >> s; 
        s = stripNonAlphaNum(s);
        words.push_back(s);
        size = words.size(); 
        for(int i = 0; i < size - 1; i++) {
            if(s == words.at(i)) {
                sendable = false; 
            }
        }
        if(sendable) {
            table.insert(s,fileNum,lineNum); 
        }
    }
}

/*
 * name:  callQuery 
 * purpose: opens the filestream 
 * arguments: none
 * returns: none 
 * effects: adds or modifies output file
 */
void Gerp::callQuery() {
    ofstream outfile; 
    outfile.open(outputFile); 
    query(outfile); 
}

/*
 * name:  query 
 * purpose: asks a client for their command
 * arguments: output stream for file output
 * returns: none 
 * effects: adds or modifies output file
 */
void Gerp::query(ofstream &output) {
    string q, s;
    cout << "Query? "; 
    cin >> q; 
    vector<pair <int,int>> instances; 
    if(q == "@q" or q == "@quit") {return;}
    else if (q == "@i" or q == "@insensitive") {
        cin >> s; 
        s = stripNonAlphaNum(s); 
        s = specialCases(s);
        instances = table.search(s, false); 
        if(instances.size() == 0) {
            toOutputNone(output, s, false); 
        } else {report(instances, output);}
    } else if (q == "@f"){ 
        cin >> s; 
        outputFile = s; 
        output.close();
        output.open(outputFile); 
    } else {
        q = stripNonAlphaNum(q); 
        q = specialCases(q);
        instances = table.search(q, true); 
        if(instances.size() == 0) {
            toOutputNone(output, q, true);
        } else {report(instances, output);}
    } query(output); 
    return; 
}



/*
 * name:  specialCases 
 * purpose: modifies a word that strip alphanum might miss
 * arguments: string
 * returns: modified string 
 * effects: modifies a string
 */
string Gerp::specialCases(string s) {
    if(not isalnum(s[0])) {
        return " ";  
    } else {
        return s; 
    }
}

/*
 * name:  toOutputNone
 * purpose: outputs the stuff
 * arguments: output stream for file output, string, if it is sensitive or not
 * returns: none 
 * effects: none
 */
void Gerp::toOutputNone(ofstream &output, string s, bool sensitive) {
    int length = s.length();
    if(sensitive) {
        if(length <= 1) {
            output << " Not Found. Try with @insensitive or @i." << endl; 
        } else {
            output << s << " Not Found. Try with @insensitive or @i." << endl;
        }
    } else {
        if(length <= 1) {
            output << " Not Found." << endl;
        } else {
            output << s << " Not Found." << endl;
        }
    }
}

/*
 * name:  report 
 * purpose: sends report lines to output file
 * arguments: arrayList of instances output stream for file output
 * returns: none 
 * effects: modifies outputfile contents
 */
void Gerp::report(vector<pair<int, int>> instances, ofstream &output) {
    int size = instances.size(); 
    int fileIndex; 
    int lineNum; 
    for(int i = 0; i < size; i++) {
        fileIndex = instances.at(i).first; 
        lineNum = instances.at(i).second; 
        output << fileVect.at(fileIndex).path << ":" << lineNum;
        output << ": " << fileVect.at(fileIndex).lines.at(lineNum - 1);
        output << endl; 
    }
}

//testing function for unit tests to assert contents
void Gerp::printInstances(vector<pair<int,int>> instances) {
    int size = instances.size();
    pair<int,int> pairing;
    for(int i = 0; i < size; i++) {
        pairing = instances.at(i); 
        cout << "FILE: " << pairing.first << endl;
        cout << "LINE: " << pairing.second << endl; 
    }
}

//testing function for unit tests to assert contents 
void Gerp::printVector() {
    int size = fileVect.size(); 
    int size2; 
    file currFile; 
    for(int i = 0; i < size; i++) {
        currFile = fileVect.at(i);
        cout << currFile.path << endl;
        size2 = currFile.lines.size();
        for(int j = 0; j < size2; j++) {
            cout << currFile.lines.at(j) << endl; 
        }
    }
}