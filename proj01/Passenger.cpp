/*
 *  Passenger.cpp
 *  Charlie Biskupiak 
 *  February 13, 2023 
 *
 *  CS 15 Project One, The Metrosim 
 *  Provides a print function for the passenger class so that 
 * passenger information can be easily readable 
 * 
 *  A passenger, in order to use the print function, must have  
 * id, arrival, and departure data points, otherwise, the print 
 * would just spit out -1s. This class is good for articulating 
 * data points about a specific passenger, so a user might want to 
 * use it to display data about a different object for their own 
 * purposes. 
 */

#include <iostream>
#include <string>
#include "Passenger.h"

/*
 * name:      print  
 * purpose:  Prints out the vital information of a passenger 
 * arguments: output stream reference to output to 
 * returns:  none, but interacts with output reference 
 * effects:  passenger does not change, but the argument will 
 */
void Passenger::print(std::ostream &output) {
        //print out information 
        output << "[" << id << ", " << from << "->" << to << "]"; 
}
