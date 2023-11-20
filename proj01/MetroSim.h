/*
 *  MetroSim.h
 *  Charlie Biskupiak 
 *  February 13, 2023 
 *
 *  CS 15 Project One, The Metrosim 
 *  
 *  Implements all neccesary functions for the metrosim class
 *  All functions will work together to make a functioning 
 *  train simulation. 
 *  This class interacts with both the passengerqueue and passenger class
 *  metrosim.h combines and manipulates the two to make the train simulation
 *  work. 
 *  As previously stated, this class does the "heavy lifting" of the 
 *  simulation. It takes in all of the data and uses its functions to 
 *  perform all neccesary actions 
 *  The class has member variables for both the train and 
 *  the stations along the map. The size will match the amount 
 *  of names inputted by the stations file 
 *  An instance of a "simulation" starts completely barren, there is 
 *  no constructor for it. Only when readStation is called, then the 
 *  simulation begins and its member variables are initialized. 
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"
#include "PassengerQueue.h"

#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>

class MetroSim
{
public:
    void readStation(string filename); 
    void printBoard(ostream &output); 
    bool takeCommand(istream &input, ostream &output); 
    string toOutput(); 

    //testing functions for drivertest
    int getNumStations(){return map.size();}
    string stationName(int i) {return map.at(i).name;}
    int getNumCars(){return train.size();}
    int getCurrstat() {return currStat;}
    Passenger getPass(int statNum) {return map.at(statNum).passQ.front();}
    Passenger getTrainPass(int trainNum) {return train.at(trainNum).front();}

private:
    //private functions
    void initStation(string name);
    void initTrain(); 
    void metroMove();
    void dropOff(); 
    void pickUp(); 
    void makePassenger(int a, int d); 

    struct station
    {
        string name; 
        PassengerQueue passQ; 
    };
    vector <PassengerQueue> train;
    vector <station> map;
    int currStat; 
    int currentID; 
    string outputText;
};

#endif
