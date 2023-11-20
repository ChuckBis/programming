/*
 *  unit_tests.h
 *  CHARLIE BISKUPIAK
 *  March 2,2023
 *
 *  CS 15 Project Three, Zap 
 *
 *  Supply a direct test for all public functions. 
 *  Verify all tests work properly and interact with each other properly.
 *  Test for error throwing messages 
 *  Testing for edge cases 
 *
 */

#include "phaseOne.h"
#include "ZapUtil.h"
#include "BinaryIO.h"
#include "HuffmanCoder.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std; 

//testing count freqs with the spec examples
/*
void test() {
    string a = "BaNana";
    istringstream iss(a); 
    count_freqs(iss, cout); 

    string b = "hi hi\nhi"; 
    istringstream iss2(b);
    count_freqs(iss2, cout); 
}
*/

//testing serialize with spec example
void test2() {
   string str = "IIILaLbILeLfILeLd"; 
   HuffmanTreeNode *node = deserialize_tree(str); 
   string str2 = serialize_tree(node);
   cout << str2 << endl; 
   assert(str2 == "IIILaLbILeLfILeLd");
   delete_tree(node);
}

//testing deserialize with spec example
void test3() {
    HuffmanTreeNode *node = makeFigure1Tree('\0');
    printTree(node, '\0'); 
    string str2 = serialize_tree(node);
    HuffmanTreeNode *node2 = deserialize_tree(str2); 
    cout << endl << endl; 
    printTree(node2, '\0');
    bool equal = treeEquals(node, node2, false); 
    cout << "EQUAL? " << equal << endl; 
    assert(equal);
    delete_tree(node);
    delete_tree(node2);
}

//prints some stuff out but also makes sure forward and backward work
void test4() {
    HuffmanTreeNode *root = deserialize_tree("IIILaLbILeLfILcLd");
    HuffmanTreeNode *root2 = deserialize_tree("ILaLb");

    printTree(root, '\0');
    cout << endl << endl; 
    printTree(root2, '\0');

    string str = serialize_tree(root); 
    string str2 = serialize_tree(root2);

    assert(str == "IIILaLbILeLfILcLd");
    assert(str2 == "ILaLb"); 

    delete_tree(root);
    delete_tree(root2);
}

//tests full functionality of forward and backward
void test5() {
    HuffmanTreeNode *node = makeFigure1Tree('\0'); 
    HuffmanTreeNode *node2 = deserialize_tree("IIILaLbILeLfILcLd");
    string str = serialize_tree(node); 
    HuffmanTreeNode *node3 = deserialize_tree(str); 
    printTree(node, '\0');
    cout << endl << endl; 
    printTree(node2, '\0');
    cout << endl << endl; 
    printTree(node3, '\0');
    cout << endl << endl; 

    assert(treeEquals(node, node2, false));
    assert(treeEquals(node2, node3, false));
    assert(treeEquals(node, node3, false));
    delete_tree(node);
    delete_tree(node2);
    delete_tree(node3);
}

//tests empty string on deserialize
void test6() {
    HuffmanTreeNode *node = deserialize_tree("");
    assert(node == nullptr); 
}

//tests nullptr on serialize 
void test7() {
    string str = serialize_tree(nullptr); 
    assert(str == ""); 
}
