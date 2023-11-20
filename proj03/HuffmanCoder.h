/*
 *  HuffmanCoder.h 
 *  Charlie Biskupiak 
 *  April 6, 2023 
 *
 *  CS 15 Project Three, Zap 
 *  
 *  Implements all neccesary functions for the HuffmanCoder class
 *  All functions will work together to make a functioning 
 *  Encoder/decoder with extra functionality. 
 *  This class interacts with both the HuffmantreeNode, phaseOne and 
 *  Binary.IO class
 *  HuffmanCoder.h combines and manipulates HuffmantreeNodes into 
 *  Huffman Coding trees with the help of priority queues, pairs, 
 *  etc. to make a fully functioning encoding and decoding program 
 *  As previously stated, this class does the "heavy lifting" of the 
 *  encoding and decoding. It takes in all of the files and uses its 
 *  functions and helper functions from the smaller files. 
 *  The class relies on the huffman coding tree to encode the texts 
 *  and then also uses it to decode. In order to make these trees 
 *  Priority queues (where frequency is the comparator) are used 
 *  to manage the HuffmanTreeNodes and their frequencies. 
 *  An instance of a "Zapper" starts as an tree, which 
 *  can be added to from the client by inputting different files
 * 
 */


#ifndef HUFFMAN_CODER_H
#define HUFFMAN_CODER_H


#include "phaseOne.h"
#include "BinaryIO.h"
#include "HuffmanTreeNode.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <queue>
#include <string>
#include <sstream>

using namespace std; 
using std::vector;
using std::priority_queue;

class HuffmanCoder {
    public:
        void encoder(const string &input_file, const string &output_file);
        void decoder(const string &input_file, const string &output_file); 
    private: 
        void countFreqs(istream &input); 
        void nodeMaker(); 
        HuffmanTreeNode *treeMaker(); 
        void makeBinary(HuffmanTreeNode *root, string translation);
        int encodeLength(); 
        string encodeString(string fileName);
        void deleteBinary(); 

        string uncodeString(string bits);
        void translator(HuffmanTreeNode *root, string t); 

        void makeBinaryObject(char val, int freq, string t);
        
        struct binary {
            char val; 
            string binaryVal; 
            int length; 
            int freq; 
        };

        vector <binary*> binaryVect; 
        priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, 
            NodeComparator> pq;
};

#endif