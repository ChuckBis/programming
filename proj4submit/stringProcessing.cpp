/*
 *  stringProcessing.cpp
 *  Charlie Biskupiak / Jack Edwards 
 *  April 17, 2023 
 *
 *  CS 15 Project Four, Gerp
 * 
 * Implements the stripNonAlphaNum function which takes in a string 
 * and returns the shaved down version that contains the alphanumeric
 * word inside of it. 
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;


/*
 * name:  stripNonAlphaNum
 * purpose: takes in a string and returns the string with the nested alphanum
 * eric values inside 
 * arguments: string that needs to be stripped
 * returns: stripped string
 * effects: no effects to input but it basically replaces that value 
 */
string stripNonAlphaNum(string input) {
    bool frontFound = false; 
    bool backFound = false;
    int front = 0; 
    int back = 0; 
    int length = input.length(); 
    for(int i = 0; i < length; i++) {
        if(isalnum(input[i]) and not frontFound) {
            front = i; 
            frontFound = true; 
        }
    }
    for(int i = length - 1; i > -1; i--) {
        if(isalnum(input[i]) and not backFound) {
            back = i; 
            backFound = true; 
        }
    }
    int size = back - front + 1; 
    return input.substr(front, size); 
}