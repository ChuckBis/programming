/*
 *  main.cpp
 *  Charlie Biskupiak / Jack Edwards 
 *  April 17, 2023 
 *
 *  CS 15 Project Four, Gerp
 *  
 * This is the driver file for gerp
 * As a whole, this program is a simulation of a file searcher
 * A client can manipulate the simulation by asking different queries
 * The driver is used to call on gerp.cpp to handle 
 * the files and producing the outputs to files 
 * If your goal is to search your files for specific key words, this 
 * program is the program for you!
 */

#include "gerp.h"
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile";
        exit(EXIT_FAILURE); 
    } else {
        Gerp gerp;
        gerp.makeVector(argv[1], argv[2]);
        gerp.callQuery(); 
        cout << "Goodbye! Thank you and have a nice day." << endl;
    }
    return 0; 
    
}