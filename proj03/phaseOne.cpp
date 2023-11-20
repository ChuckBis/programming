/*
 *  phaseOne.cpp
 *  Charlie Biskupiak 
 *  March 30, 2023 
 *
 *  CS 15 Project Three, Zap
 * 
 * Defines the huffman Coding tree functions:
 * 
 * countFreqs counts the frequency of different characters in an input stream
 * serialize_tree takes a pointer to the root of a tree and summarizes it 
 * deserialize_tree takes in a summary and makes a tree out of it
 * 
 */


#include "phaseOne.h"
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>

using namespace std; 


/*
 * name:     count_freqs
 * purpose: takes in an input stream and prints out the frequency
 * of the characters of the stream 
 * arguments: input stream 
 * returns: none
 * effects: none
 
void count_freqs(istream &text, ostream &output){
    char input; 
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
        output << char(index) << ": " << freqs[index] << endl; 
        ss >> index; 
    } 
}
*/


/*
 * name:   serialize_tree
 * purpose: analyzes a huffman tree and returns its node values
 * in pre-order
 * arguments: root of huffman tree
 * returns: serialized version of the tree
 * effects: none
 */
string serialize_tree(HuffmanTreeNode *root){
    string returnable; 
    if(root == nullptr) {return "";}
    //self --> left --> right 
    if(not root->isLeaf()) {
        returnable += "I"; 
        returnable = returnable + serialize_tree(root->get_left());
        returnable = returnable + serialize_tree(root->get_right());
    } else {
        returnable += "L"; 
        returnable += root->get_val();
    }
    return returnable; 
}

/*
 * name:   deserialize_tree_recurse
 * purpose: takes in a serialized string and builds a tree out of it
 * arguments: serialized tree
 * returns: root to serialized tree 
 * effects: none
 */
HuffmanTreeNode *deserialize_tree_recurse(string &serial_tree){
    int length = serial_tree.length(); 
    if(length == 0) {return nullptr;}
    char c = serial_tree[0]; 
    serial_tree = serial_tree.substr(1, length - 1); 
    if(c == 'I') {
        HuffmanTreeNode *root = new HuffmanTreeNode('\0','\0');
        HuffmanTreeNode *left = deserialize_tree_recurse(serial_tree); 
        HuffmanTreeNode *right = deserialize_tree_recurse(serial_tree); 
        root->set_left(left);
        root->set_right(right); 
        return root; 
    } else if (c == 'L') {
        char c2 = serial_tree[0]; 
        serial_tree = serial_tree.substr(1, length - 1); 
        return new HuffmanTreeNode(c2,0); 
    } else {
        throw runtime_error("Invalid tree input"); 
    }
}

/*
 * name:   deserialize_tree
 * purpose: calls its recursive helper
 * arguments: serialized tree
 * returns: root to serialized tree 
 * effects: none
 */
HuffmanTreeNode *deserialize_tree(string serial_tree) {
    string tree = serial_tree; 
    return deserialize_tree_recurse(tree);
}

/*
 * name:   delete_tree
 * purpose: removes a binary tree from heap memory
 * arguments: root to binary tree
 * returns: none
 * effects: deletes a tree 
 */
void delete_tree(HuffmanTreeNode *root) {
    if(root != nullptr) {
        delete_tree(root->get_left()); 
        delete_tree(root->get_right());
        delete root; 
    }
}

