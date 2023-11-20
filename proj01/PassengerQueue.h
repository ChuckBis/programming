/*
 *  PassengerQueue.h 
 *  Charlie Biskupiak 
 *  February 13, 2023 
 *
 *  CS 15 Project One, The Metrosim 
 *  
 *  Header file for the passenger queue class. Declares all of the queue-like
 *  functions that the class will use. 
 *  This file interacts with the passenger class, as passengerqueue is a 
 *  linked list (acting as a queue) of passengers. 
 *  This class would work as a queue for any type of object, which could 
 *  be useful for other projects or data structures. For this project, it 
 *  is used for passengers 
 *  Each instance of a passengerQueue starts empty and is then added to or 
 *  removed from by either a client or another function, 
 * for this project, metrosim.cpp will manipulte it. 
 */

#ifndef PASSENGER_QUEUE_H
#define PASSENGER_QUEUE_H


#include "Passenger.h"
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std; 
using std::list;

class PassengerQueue {
public: 
    Passenger front();
    void dequeue(); 
    void enqueue(const Passenger &passenger); 
    int size(); 
    void print(ostream &output); 

private: 
    list <Passenger> passQ;
};


#endif