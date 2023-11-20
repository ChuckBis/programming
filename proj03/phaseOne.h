/*
 *  phaseOne.h 
 *  Charlie Biskupiak 
 *  March 30, 2023 
 *
 *  CS 15 Project Three, Zap 
 *  
 * Contains functions that help with ease of access and 
 * usability of a huffman coding tree
 * 
 */

#include "HuffmanTreeNode.h"

#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>

using namespace std; 

//void count_freqs(istream &text, ostream &output);
string serialize_tree(HuffmanTreeNode *root); 
HuffmanTreeNode *deserialize_tree_recurse(string &serial_tree); 
HuffmanTreeNode *deserialize_tree(string serial_tree);
void delete_tree(HuffmanTreeNode *root);