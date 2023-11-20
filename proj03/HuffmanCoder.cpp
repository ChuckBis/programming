/*
 *  HuffmanCoder.cpp
 *  Charlie Biskupiak 
 *  April 6, 2023 
 *
 *  CS 15 Project Three, Zap
 *  
 * Contains the functions and their definitions for the HuffmanCoder class. 
 * This file will be called by the main driver and run the entire program
 * The commands will be read in, and the class will respond accordingly to
 * the commands. 
 * 
 * When instantiating this class, it is imperative that the user knows for 
 * any of the commands to be useful, a file must contain chars and be valid
 * The encoder and decoder rely on reading in data. If there is no date to be 
 * read in, what's the point of the encoder?? 
 *
 */

#include "HuffmanCoder.h"
#include "phaseOne.h"
#include "HuffmanTreeNode.h"
#include "ZapUtil.h"
#include "BinaryIO.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <queue>
#include <utility>

using namespace std; 
using std::vector;
using std::priority_queue;

/*
 * name:  encoder
 * purpose: takes in a file and sends the encoded version to the outputfile 
 * arguments: input file and output file  
 * returns: none
 * effects: makes a huffman tree and manipulates the priority queue and 
 * nodes member variables 
 */
void HuffmanCoder::encoder(const string &inF, const string &outF){ 
    ifstream infile; 
    ostringstream freqs; 
    infile.open(inF); 
    if(infile.peek() == std::ifstream::traits_type::eof()) {
        cout << inF << " is empty and cannot be compressed." << endl;
        return; 
    }
    if(not infile.is_open()) {
        throw runtime_error("Unable to open file " + inF);
    } 
    countFreqs(infile); 
    infile.close(); 
    nodeMaker(); 
    HuffmanTreeNode *root = treeMaker(); 
    makeBinary(root, "");
    string serialized = serialize_tree(root); 
    int length = encodeLength(); 
    string converted = encodeString(inF); 
    BinaryIO functions; 
    functions.writeFile(outF, serialized, converted); 
    cout<< "Success! Encoded given text using " << length << " bits." << endl;
    delete_tree(root); 
    deleteBinary(); 
}


/*
 * name:     count_freqs
 * purpose: takes in an input stream and prints out the frequency
 * of the characters of the stream 
 * arguments: input stream 
 * returns: none
 * effects: none
 */
void HuffmanCoder::countFreqs(istream &text){
    char input, val; 
    int freq; 
    stringstream ss; 
    text >> noskipws; 
    int freqs[127]; 
    for(int i = 0; i < 127; i++) {freqs[i] = 0;}
    int ascii, index; 
    string order = ""; 
    text >> input; 
    while(not text.eof()) {
        ascii = (int) input; 
        freqs[ascii]++; 
        if(freqs[ascii] == 1) {
            ss << ascii;  
            ss << " ";  
        } text >> input; 
    } text >> skipws; 
    ss >> index; 
    while(not ss.eof()) {
        val = char(index); 
        freq = freqs[index]; 
        makeBinaryObject(val, freq, ""); 
        ss >> index; 
    } 
}

/*
 * name:  makeBinaryObject
 * purpose: makes a new Binary instance with some key values
 * arguments: value and frequency
 * returns: none
 * effects: makes a new object and adds it to its vector 
 */
void HuffmanCoder::makeBinaryObject(char val, int freq, string t) {
    binary *b = new binary; 
    b->val = val; 
    b->freq = freq; 
    b->binaryVal = t;
    b->length = 0;  
    binaryVect.push_back(b); 
}

/*
 * name:  deleteBinary
 * purpose: deletes all binary structs made on heap
 * arguments: none
 * returns: none
 * effects: frees heap memory 
 */
void HuffmanCoder::deleteBinary() {
    int size = binaryVect.size();
    for(int i = 0; i < size; i++) {
        delete binaryVect.at(i);
    }
}

/*
 * name:  nodeMaker
 * purpose: takes in a string full of frequencies and makes them into nodes
 * arguments: frequency string
 * returns: none
 * effects: makes new nodes and adds them to priority queue memeber variable
 */
void HuffmanCoder::nodeMaker() {
    int size = binaryVect.size(); 
    binary *b;
    int freq; 
    char val; 
    for(int i = 0; i < size; i++) {
        b = binaryVect.at(i); 
        freq = b->freq;
        val = b->val; 
        HuffmanTreeNode *newNode = new HuffmanTreeNode(val, freq); 
        pq.push(newNode); 
    }
}

/*
 * name:  treeMaker
 * purpose: takes the nodes in the priority queue and makes them into a 
 * huffman tree
 * arguments: none
 * returns: Pointer to root of tree
 * effects: empties the priority queue and turns it into a tree
 */
HuffmanTreeNode* HuffmanCoder::treeMaker(){
    HuffmanTreeNode *node1; 
    HuffmanTreeNode *node2; 
    int freq; 
    if(pq.size() == 0) {return nullptr;}
    while(pq.size() > 1) {
        node1 = pq.top();
        pq.pop();
        node2 = pq.top(); 
        pq.pop(); 
        freq = node1->get_freq() + node2->get_freq(); 
        HuffmanTreeNode *newParent = new HuffmanTreeNode('\0', freq);
        newParent->set_left(node1); 
        newParent->set_right(node2); 
        pq.push(newParent);  
    }
    HuffmanTreeNode *root = pq.top();
    pq.pop(); 
    return root; 
} 

/*
 * name:  makeBinary
 * purpose: takes in the root of a huffman tree and inputs all of 
 * the chars in the tree and their determined binary values into 
 * a vector to be read from later
 * arguments: root to binary tree
 * returns: none
 * effects: adds elements to binary vector 
 */
void HuffmanCoder::makeBinary(HuffmanTreeNode *root, string translation) {
    string left = translation + "0"; 
    string right = translation + "1";
    int length; 
    char rootVal; 
    if(root == nullptr) {return;}
    if(root->get_val() == '\0') {
        makeBinary(root->get_left(), left); 
        makeBinary(root->get_right(), right); 
    } else {
        int size = binaryVect.size(); 
        binary *b; 
        for(int i = 0; i < size; i++) {
            b = binaryVect.at(i); 
            rootVal = root->get_val(); 
            if(b->val == rootVal) {
                b->binaryVal = translation; 
                length = translation.length();
                b->length = length; 
            }
        }
    }
}

/*
 * name:  encodeLength
 * purpose: returns the length of the encoded message
 * arguments: list of all chars and their frequencies 
 * returns: number of bits needed to encode message
 * effects: none
 */
int HuffmanCoder::encodeLength() {
    int total = 0; 
    int product; 
    int size = binaryVect.size(); 
    binary *b; 
    for(int i = 0; i < size; i++) {
        b = binaryVect.at(i); 
        product = b->freq * b->length; 
        total += product; 
    }
    return total; 
}

/*
 * name:     encodeString
 * purpose: takes a message and encodes it using the huffman tree
 * arguments: input file 
 * returns: encoded message
 * effects: none
 */
string HuffmanCoder::encodeString(const string fileName) {
    ifstream infile; 
    char s; 
    string input = ""; 
    infile.open(fileName);
    infile >> noskipws; 
    infile >> s; 
    binary *b; 
    int size = binaryVect.size(); 
    while(not infile.eof()) {
        for(int i = 0; i < size; i++) {
            b = binaryVect.at(i); 
            if(b->val == s) {
                input += b->binaryVal; 
            }
        }
        infile >> s; 
    } infile >> noskipws; 
    infile.close(); 
    return input; 
}

/*
 * name:     decoder
 * purpose: takes in a file and sends the decoded version to the outputfile 
 * arguments: input file and output file  
 * returns: none
 * effects: manipulates vector member variable makes a tree and deletes it 
 */
void HuffmanCoder::decoder(const string &inF, const string &outF) {
    BinaryIO functions; 
    pair<string, string> info; 
    info = functions.readFile(inF); 
    HuffmanTreeNode *root = deserialize_tree(info.first); 
    translator(root, ""); 
    string translation = uncodeString(info.second);
    ofstream outfile; 
    outfile.open(outF);
    outfile << translation; 
    outfile.close(); 
    delete_tree(root); 
    deleteBinary();
}

/*
 * name:  translator 
 * purpose: takes in a bianry tree and gets all the 
 * binary translations of the chars
 * arguments: binary tree
 * returns: none
 * effects: adds to the binaryVect
 */
void HuffmanCoder::translator(HuffmanTreeNode *root, string binary) {
    string left = binary + "0"; 
    string right = binary + "1";
    char rootVal; 
    if(root == nullptr) {return;}
    if(root->get_val() == '\0') {
        translator(root->get_left(), left); 
        translator(root->get_right(), right); 
        return; 
    } else {
       rootVal = root->get_val(); 
       makeBinaryObject(rootVal, 0, binary); 
       return; 
    }
}

/*
 * name:     uncodeString
 * purpose: takes in a string of bits and returns what it says 
 * arguments: string of encoded message
 * returns: decoded message
 * effects: none
 */
string HuffmanCoder::uncodeString(string bits){
    string returnable = "";
    string bin = ""; 
    int length = bits.length(); 
    int size = binaryVect.size(); 
    bin += bits[0]; 
    binary *b; 
    for(int i = 1; i < length + 1; i++) {
        for(int j = 0; j < size; j++) {
            b = binaryVect.at(j); 
            if(b->binaryVal == bin) {
                returnable += b->val; 
                bin = ""; 
            }
        }
        bin += bits[i]; 
    }
    int binLength = bin.length();
    if(binLength != 1) {
        throw runtime_error("Encoding did not match Huffman tree.");
    }
    return returnable; 
}