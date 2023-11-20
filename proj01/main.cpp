/*
 *  main.cpp
 *  Charlie Biskupiak 
 *  February 13, 2023 
 *
 *  CS 15 Project One, The Metrosim 
 *  
 * This is the driver file for the metrosim simulation
 * As a whole, this program is a simulation of the T green line
 * A client can manipulate the simulation in two ways: adding passengers
 * and moving the train to the next stop. The driver is used to call on 
 * MetroSim.cpp to do all of the heavy lifting when it comes to handling
 * and using the data. 
 * If your goal is to experience the greenline in a fun and interactive way,
 * this program does the job! 
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "MetroSim.h"

using namespace std;

int main(int argc, char *argv[]) {
       MetroSim theSimulation;
        if(argc < 3) {
                cerr << "Usage: ./MetroSim stationsfile outputFile "
                "[commandsFile]" << endl; 
        } ifstream instream; 
        if(argc == 4) {
                instream.open(argv[3]); 
                if(not instream.is_open()) {
                        cerr<<"Error: could not open file "<<argv[3] << endl;
                        exit(EXIT_FAILURE);
                }
                theSimulation.readStation(argv[1]);
        } else {
                theSimulation.readStation(argv[1]);
        } bool play = true;
        while (play == true) {
                theSimulation.printBoard(cout); 
                if(argc == 4) {
                        play = theSimulation.takeCommand(instream,cout); 
                } else {
                        play = theSimulation.takeCommand(cin, cout); 
                }
        } ofstream outstream; 
        outstream.open(argv[2]);
        outstream << theSimulation.toOutput(); 
        outstream.close();
        cout << "Thanks for playing MetroSim. Have a nice day!" << endl; 
        return 0; 
}