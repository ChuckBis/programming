/*
 *  MetroSim.cpp
 *  Charlie Biskupiak 
 *  February 13, 2023 
 *
 *  CS 15 Project One, The Metrosim 
 *  
 * Contains the functions and their definitions for the metrosim class. 
 * The file is organized so that as the simulation/turn 
 * progresses, the file can be read from top to bottom. 
 * This file will be called by the main driver and run the entire program
 * The files will be read in, and the class will immediately set up 
 * the lists, then the board will be printed, then the user will input 
 * a command, and then the turn will commence. 
 * 
 * When instantiating this class, it is imperative that the program has 
 * an input file to go along with it. The entire program (especially its
 * data structures) relies on the amount of stations there are. 
 * In order to run a successful simulation, the input file must be readable,
 * and all user inputs from cin or a command file must be correct. 
 */

#include "MetroSim.h"
#include "Passenger.h"
#include "PassengerQueue.h"

#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std; 

/*
 * name:      readStation 
 * purpose:  read in the imput file and record the stations 
 * arguments: the name of the input file to be opened
 * returns: none
 * effects: Opens the filename storing the stations and calls
 * a helper function to intialize all of the station passenger
 * queues. Additionally, because the amount of stations should 
 * be equal to the amount of train cars, I also call another 
 * function to initialize the train cars a certain number of times
 */
void MetroSim::readStation(string fileName){
    ifstream instream; 
    instream.open(fileName); 
    if(not instream.is_open()) {
        cerr << "Error: could not open file " << fileName << endl; 
        exit(EXIT_FAILURE);
    }
    string station; 
    int numStations = 0; 
    while(getline(instream, station)) {
        initStation(station); 
        numStations++; 
    }
    for(int i = 0; i < numStations; i++) {
        initTrain(); 
    }
    instream.close(); 
}

/*
 * name:   initStation 
 * purpose: initialize a single station and add it to its vector
 * arguments: name of the station 
 * returns: none   
 * effects: creates a new instance of a station struct and adds it 
 * to the map vector
 */
void MetroSim::initStation(string name) {
    station newStation; 
    newStation.name = name; 
    PassengerQueue newPassQ;
    newStation.passQ = newPassQ; 
    map.push_back(newStation); 
}

/*
 * name:   initTrain
 * purpose: initialize a train car that correlates to a station 
 * arguments: none
 * returns: none
 * effects: makes a new train car and adds it to its vector. 
 * Additionally, it initializes two member variables that will help the 
 * train onload and offload easier, along with making new passengers 
 */
void MetroSim::initTrain(){
    PassengerQueue newTrainCar;
    train.push_back(newTrainCar); 
    currStat = 0; 
    currentID = 1; 
} 

/*
 * name:   printBoard
 * purpose: print the game board 
 * arguments: specific output stream to be outputted to 
 * returns: none
 * effects: no effects to game, just prints the board for 
 * client to see properly  
 */
void MetroSim::printBoard(ostream &output){
    ostringstream message; 
    ostringstream newMessage; 
    int size = map.size();
    output << "Passengers on the train: {";
    for(int i = 0; i < size; i++) {
        message.str("");
        train.at(i).print(message); 
        output << message.str(); 
    }
    output << "}" << endl; 
    for(int i = 0; i < size; i++) {
        newMessage.str(""); 
        if (i == currStat) { //if train is at the station 
            output << "TRAIN: "; 
        } else {
            output << "       "; 
        }
        output << "[" << i << "] ";
        output << map.at(i).name << " {"; 
        map.at(i).passQ.print(newMessage);
        output << newMessage.str(); 
        output << "}" << endl; 
    }
}

/*
 * name:   takeCommand
 * purpose: recieve command from client and call respective helper function
 * arguments: specific input and output streams
 * returns: a boolean that when false, triggers end of the simulation   
 * effects: none to simulation, unless to stop it. But calls other 
 * functions that do have effects  
 */
bool MetroSim::takeCommand(istream &input, ostream &output){
    string cmd1, cmd2;
    int arrival, departure; 
    output << "Command? "; 
    input >> cmd1; 
    if(cmd1 == "p") {
        input >> arrival;
        input >> departure; 
        makePassenger(arrival,departure); 
        return true;
    } else if (cmd1 == "mm") {
        metroMove(); 
        return true; 
    } else if (cmd1 == "mf") {
        return false; 
    //the above two are if the command is without whitespace
    //the demo worked with either case 
    } else if (cmd1 == "m") { 
        input >> cmd2; 
        if(cmd2 == "m") {
            metroMove();
            return true; 
        } else if (cmd2 == "f") {
            return false; 
        }
    } return false; 
}

/*
 * name:   makePassenger
 * purpose: make a new instance of a passenger
 * arguments: arrival and departure data for passenger
 * returns: none  
 * effects: makes a new passenger and adds them to their specific 
 * arrival passengerQueue. Additionally, increments the id member
 * variable so that the next passenger has a different id
 */
void MetroSim::makePassenger(int a, int d) {
    int size = map.size();
    if(a < 0 or a > size) {
        throw std::range_error("Arrival out of bounds");
    }
    if(d < 0 or d > size) {
        throw std::range_error("Departure out of bounds");
    }
    Passenger newPass(currentID, a, d); 
    currentID++;
    map.at(a).passQ.enqueue(newPass);
}

/*
 * name:   metroMove
 * purpose: moves the train to the next station 
 * arguments: none
 * returns: none
 * effects: picks up passengers at their stop, and places them 
 * in their respective train car. Then the train is moved to the
 * next station, and the passengers that need to get off, get off
 */
void MetroSim::metroMove() {
    int stationSize = map.at(currStat).passQ.size();
    if(stationSize > 0) {pickUp();}
    int size = map.size() - 1;
    if(currStat == size) { //if need to wrap around 
        currStat = 0; 
    } else {
        currStat++; 
    }
    dropOff();
}

/*
 * name:   pickUp
 * purpose: picks up all passengers at a station and puts them on their car
 * arguments: none
 * returns: none
 * effects: transfers all passengers from current station into the train, 
 * specifically their respective departure cars 
 */
void MetroSim::pickUp() {
    int stationSize = map.at(currStat).passQ.size(); 
    for(int i = 0; i < stationSize; i++) {
        Passenger newPassenger = map.at(currStat).passQ.front(); 
        int destination = newPassenger.to; 
        train.at(destination).enqueue(newPassenger); 
        map.at(currStat).passQ.dequeue(); 
    }
}

/*
 * name:   dropOff
 * purpose: empties the departure train cart that corresponds to the current 
 * station, also loads output file messages to the member variable
 * arguments: none
 * returns: none
 * effects: Dequeues every passenger instance from the train car that is equal
 * to the current station and adds the output print to the string stream. 
 * Finally, the string stream gets loaded into the member variable that gets
 * printed to the output file at the end of the game
 */
void MetroSim::dropOff() {
    stringstream output;
    int carSize = train.at(currStat).size();
    for(int i = 0; i < carSize; i++){
        output << "Passenger " << train.at(currStat).front().id; 
        output << " left train at station " << map.at(currStat).name; 
        output << endl; 
        train.at(currStat).dequeue(); 
        outputText += output.str(); 
        output.str("");
    }
}

/*
 * name:   toOutput
 * purpose: returns all output file text
 * arguments: none
 * returns: all of the output messages from the simulation
 * effects: none
 */
string MetroSim::toOutput() {
    return outputText; 
}