/*
 *  PassengerQueue.cpp
 *  Charlie Biskupiak 
 *  February 13, 2023 
 *
 *  CS 15 Project One, The Metrosim 
 *  
 *  Implements a queue class for passenger objects, each instance of this 
 * class will be used as a station and train cars. They will hold all of the 
 * passengers and display their information. 
 * The queue is a linked list that acts like a queue, as it is 
 * "add to the back, take from the top"
 *  This class is best used as a way to store data in a line form
 *  for example, a line of items on a conveyor belt at a grocery store.
 *  This class works exceptionally well for its "add to the back, 
 * take from the top" purpose.
 *  In order to run it properly, it must be used as intended. It can only 
 * access the first element, so it should not be used in a vector or even 
 * list-like fashion 
 */

#include "Passenger.h"
#include "PassengerQueue.h"
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std; 


/*
 * name:      front  
 * purpose:  returns the passenger at the front of a queue
 * arguments: none
 * returns:  first passenger in queue
 * effects: none
 */
Passenger PassengerQueue::front() {
    return passQ.front(); 
}

/*
 * name:      dequeue  
 * purpose: removes the person at the front of the queue
 * arguments: none
 * returns:  none
 * effects: front passenger is removed from queue, others move up 
 */
void PassengerQueue::dequeue(){
    passQ.pop_front(); 
} 

/*
 * name:      enqueue
 * purpose: adds a new passenger to the queue
 * arguments: a reference to a new passenger 
 * returns: none
 * effects:  adds a person to the back of the queue 
 */
void PassengerQueue::enqueue(const Passenger &passenger){ 
    passQ.push_back(passenger); 
} 

/*
 * name:     size
 * purpose:  returns the size of the queue
 * arguments: none
 * returns:  int --> size of the queue
 * effects: none
 */
int PassengerQueue::size() {
    return passQ.size(); 
}

/*
 * name:      print  
 * purpose:  Prints out the vital information of all passengers in queue
 * arguments: output stream reference to output to 
 * returns:  none, but interacts with output reference 
 * effects:  passengers and queue do not change, but the argument will 
 */
void PassengerQueue::print(std::ostream &output) {
    list<Passenger>::iterator itr; 
    ostringstream message; 
    for(itr = passQ.begin(); itr != passQ.end(); itr++) {
        itr->print(message); 
    }
    output << message.str();
}