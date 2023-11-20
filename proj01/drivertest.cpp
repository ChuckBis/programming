/*
 *  drivertest.cpp
 *  Charlie Biskupiak 
 *  February 13, 2023 
 *
 *  CS 15 Project One, The Metrosim 
 *  
 * This is the driver file for the metrosim simulation testing
 * This file tests the basics of all of the functions in the metrosim 
 * simulation. For the testing, many of the functions were made public,
 * and public helper functions were added to metrosim.h to test
 * the functionality of the code as a whole 
 * 
 */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "MetroSim.h"

using namespace std;

bool testReading(MetroSim testSim, string fileName); 
bool testStation(MetroSim testSim);
bool testTrain(MetroSim testSim); 
//void testPrint(MetroSim testSim); done with diff in command line
bool testCommand(MetroSim testSim); 
bool testMove(MetroSim testSim); 
bool testPassenger(MetroSim testSim); 
bool testDropOff(MetroSim testSim); 
bool testPickUp(MetroSim testSim); 
//bool testOutput(MetroSim testSim); done with dropOff


int main(int argc, char *argv[]) {
    MetroSim testSim1; 
    if(testReading(testSim1, argv[1]) == true) {
        cout << "1. Success!" << endl; 
    } else {cout << "1. Boo!" << endl;}

    MetroSim testSim2;
    testSim2.readStation(argv[1]);
    if(testStation(testSim2) == true) {
        cout << "2. Success!" << endl; 
    } else {cout << "2. Boo!" << endl;}

    MetroSim testSim3;
    testSim3.readStation(argv[1]);
    if(testTrain(testSim3) == true) {
        cout << "3. Success!" << endl; 
    } else {cout << "3. Boo!" << endl;}

    MetroSim testSim4;
    testSim4.readStation(argv[1]);
    if(testCommand(testSim4) == true) {
        cout << "4. Success!" << endl; 
    } else {cout << "4. Boo!" << endl;}

    MetroSim testSim5;
    testSim5.readStation(argv[1]);
    if(testMove(testSim5) == true) {
        cout << "5. Success!" << endl; 
    } else {cout << "5. Boo!" << endl;}

    MetroSim testSim6;
    testSim6.readStation(argv[1]);
    if(testPassenger(testSim6) == true) {
        cout << "6. Success!" << endl; 
    } else {cout << "6. Boo!" << endl;}

    MetroSim testSim7;
    testSim7.readStation(argv[1]);
    if(testDropOff(testSim7) == true) {
        cout << "7. Success!" << endl; 
    } else {cout << "7. Boo!" << endl;}

    MetroSim testSim8;
    testSim8.readStation(argv[1]);
    if(testPickUp(testSim8) == true) {
        cout << "8. Success!" << endl; 
    } else {cout << "8. Boo!" << endl;}

    return 0; 
}

//making sure all stations are read in properly
bool testReading(MetroSim testSim, string fileName) {
    testSim.readStation(fileName);
    if(testSim.getNumStations() == 26) {
        return true;
    } 
    return false; 
}

//making sure each station is initialized by taking a random one 
bool testStation(MetroSim testSim){
    if(testSim.stationName(5) == "Brigham Circle") {
        return true;
    } 
    return false; 
}

//making sure train cars correspond to number of stations done above
bool testTrain(MetroSim testSim) {
    if(testSim.getNumCars() == 26) {
        return true;
    } 
    return false; 
}

void testPrint(MetroSim testSim) {
    //PRINTING WAS TESTED BY DIFFING WITH THE DEMO WITH SHORT_COMMANDS
}

//testing mf and m f to work 
bool testCommand(MetroSim testSim) {
    bool shouldFalse = testSim.takeCommand(cin, cout); //input mf or m f
    return not shouldFalse; 
}
//making sure metro is, in fact, moving 
bool testMove(MetroSim testSim) {
    for(int i = 0; i < 10; i++) {
        testSim.metroMove(); 
    }
    if(testSim.getCurrstat() == 10) {return true;}
    return false; 
}
//testing making a passenger and making sure everything shifts and is saved 
bool testPassenger(MetroSim testSim) {
    testSim.makePassenger(1,10);
    testSim.makePassenger(3,10);
    Passenger newPass = testSim.getPass(3); 
    if(newPass.from == 3 and newPass.to == 10 and newPass.id == 2) {
        return true;
    }
    return false; 
}

//testing drop off 
//also testing to output 
bool testDropOff(MetroSim testSim) {
    testSim.makePassenger(1,2);
    testSim.metroMove(); 
    testSim.metroMove(); 
    string output = testSim.toOutput();
    if(output == "Passenger 1 left train at station Riverway\n") {
        return true; 
    }
    return false; 
}

//testing pickup functionality
bool testPickUp(MetroSim testSim) {
    testSim.makePassenger(1,5);
    testSim.metroMove(); 
    testSim.metroMove(); 
    Passenger newPass = testSim.getTrainPass(5); 
    if(newPass.from == 1 and newPass.to == 5) {
        return true;
    }
    return false; 
}