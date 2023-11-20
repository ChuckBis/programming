/*
 *  Passenger.h
 *  Charlie Biskupiak 
 *  February 13, 2023 
 *
 *  CS 15 Project One, The Metrosim 
 *  Provides a header function for the passenger class, the smallest 
 *  piece of the metrosim. The class contains an id, and a starting and 
 *  final destination for each instance. It also intiializes a print 
 *  function for the class to articulate the variables preivously mentioned 
 *
 *  Each instance is initialized using one of the two constructors, however
 * for this simulation, the basic constructor is not used, so each passenger
 * will always have an id, arrival, and departure station 
 */


#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>

struct Passenger
{

        int id, from, to;
        
        Passenger()
        {
                id   = -1;
                from = -1;
                to   = -1;
        }

        Passenger(int newId, int arrivalStation, int departureStation)
        {
                id   = newId;
                from = arrivalStation;
                to   = departureStation;
        }

        // TODO: implement the print function in Passenger.cpp
        void print(std::ostream &output);

};

#endif
