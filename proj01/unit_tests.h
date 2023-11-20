/*
 *  unit_tests.h
 *  CHARLIE BISKUPIAK
 *  FEB 13,2023
 *
 *  CS 15 Project One, The Metrosim 
 *
 *  Supply a direct test for all public functions. 
 *  Verify all tests work properly and interact with each other properly.
 *  Test for error throwing messages 
 *  Testing for edge cases 
 *
 */

#include "PassengerQueue.h"
#include "MetroSim.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std; 

//testing to make sure constructor and destructor work properly
void testingtoseeifitiworkslol() {
    PassengerQueue passenger; 
    assert(passenger.size() == 0); 
}

//testing to make sure the enqueue properly changes the size 
void testTheEnqueue() {
     Passenger newPassenger(1,2,3); 
     PassengerQueue newQueue; 
     assert(newQueue.size() == 0);
     newQueue.enqueue(newPassenger); 
     assert(newQueue.size() == 1);
}

//testing to make sure the dequeue decrements the size
void testTheDequeue(){
    Passenger newPassenger(1,2,3); 
    PassengerQueue newQueue; 
    newQueue.enqueue(newPassenger); 
    assert(newQueue.size() == 1);
    newQueue.dequeue();
    assert(newQueue.size() == 0);
}

//testing to make sure the first passenger's information is printed correctly
void firstAndPrint() {
    ostringstream message; 
    Passenger newPassenger(1,2,3); 
    PassengerQueue newQueue; 
    newQueue.enqueue(newPassenger); 
    Passenger thePassenger = newQueue.front();
    thePassenger.print(message); 
    assert(message.str() == "[1, 2->3]");
}

//trying to print a few passengers in a queue, to test the print function 
void printMany() {
    ostringstream message; 
    Passenger newPassenger1(1,2,3); 
    Passenger newPassenger2(2,2,3); 
    Passenger newPassenger3(3,2,3); 
    Passenger newPassenger4(4,2,3); 
    Passenger newPassenger5(5,2,3); 
    PassengerQueue newQueue; 
    newQueue.enqueue(newPassenger1); 
    newQueue.enqueue(newPassenger2); 
    newQueue.enqueue(newPassenger3); 
    newQueue.enqueue(newPassenger4); 
    newQueue.enqueue(newPassenger5); 
    newQueue.print(message); 
    assert(message.str() == "[1, 2->3][2, 2->3][3, 2->3][4, 2->3][5, 2->3]");
}

//dequeueing a lot of people to make sure that all are accounted for 
void dequeueMany() {
    PassengerQueue manyPassengers; 
    Passenger newPassenger(1,2,3); 
    for(int i = 0; i < 100; i++) {
        manyPassengers.enqueue(newPassenger);
    }
    assert(manyPassengers.size() == 100); 
    for(int i = 0; i < 100; i++) {
        manyPassengers.dequeue();
    }
    assert(manyPassengers.size() == 0); 
}

//this one doesn't fully empty the queue, just to make sure it works 
void dequeueafew() { 
    PassengerQueue manyPassengers; 
    Passenger newPassenger(1,2,3); 
    for(int i = 0; i < 20; i++) {
        manyPassengers.enqueue(newPassenger);
    }
    assert(manyPassengers.size() == 20); 
    for(int i = 0; i < 10; i++) {
        manyPassengers.dequeue();
    }
    assert(manyPassengers.size() == 10); 
}