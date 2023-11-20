/*
 *  main.cpp
 *  Charlie Biskupiak 
 *  April 6, 2023 
 *
 *  CS 15 Project Three, Zap
 *  
 * This is the driver file for the Zap simulation
 * As a whole, this program is a simulation of a file encoder/decoder. 
 * A client can manipulate the simulation by inputting different files when 
 * calling the simulation on the commandline 
 * The driver is used to call on HuffmanCoder.cpp to handle 
 * the files and producing the outputs 
 * If your goal is to encode your files and have them also decoded, this 
 * program is the program for you!
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "HuffmanCoder.h"

using namespace std;

int main(int argc, char *argv[]) {
       HuffmanCoder huff;
        if(argc != 4) {
                cerr << "Usage: ./zap [zap | unzap] inputFile "
                "outputFile" << endl; 
                return 1; 
        } else if(argc == 4) {
            string zap = argv[1]; 
            if(zap == "zap") {huff.encoder(argv[2], argv[3]);}
            else if (zap == "unzap") {huff.decoder(argv[2], argv[3]);}
            else {
                cerr << "Usage: ./zap [zap | unzap] inputFile "
                "outputFile" << endl;
                return 1; 
                }
        } else {
                cerr << "Usage: ./zap [zap | unzap] inputFile "
                "outputFile" << endl;
                return 1; 
        }
        return 0; 
}