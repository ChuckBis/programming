/*
 *  unit_tests.h
 *  CHARLIE BISKUPIAK / Jack Edwards 
 *  April 23,2023
 *
 *  CS 15 Project Four, Gerp 
 *
 *  Supply a direct test for all public functions. 
 *  Verify all tests work properly and interact with each other properly.
 *  Test for error throwing messages 
 *  Testing for edge cases 
 * All private functions were made public for these tests 
 */

#include "HashTable.h"
#include "gerp.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std; 

//step one --> Make the file vector 
    //Tree traversal was tested in phase one with diff testing because 
    //it had its own main 
/*

//make sure the makeFile function is working properly 
void checkMakeFile() {
    Gerp gerp; 
    string s1 = "your/mom/text/";
    string s2 = "testInput.txt";
    gerp.makeFile(s1, s2); 
    //the file was read in and output was online diffed with the 
    //original file contents, both the lines and path were tested 

    SHOULD OUTPUT: 
    your/mom/text/testInput.txt
    fuisenirbfvkib
    siuevbrsiuvbrivuw
    heuirvbnsiuvbnweriuv
    eivberiusvbwu
    
}

//checks to make sure things in vector are being stored properly
void checkVector() {
    Gerp gerp; 
    string s1 = "your/mom/text/";
    string s2 = "testInput.txt";
    gerp.makeFile(s1, s2); 
    s1 = "a/new/file/";
    s2 = "testInput1.txt";
    gerp.makeFile(s1,s2); 
    gerp.printVector(); 
    SHOULD OUTPUT: 
    your/mom/text/testInput.txt
    fuisenirbfvkib
    siuevbrsiuvbrivuw
    heuirvbnsiuvbnweriuv
    eivberiusvbwu
    a/new/file/testInput1.txt
    yo mama
    
    
}
*/


/*
//do the same thing but with a real dataset 
void realData() {
    Gerp gerp;
    string s = "demo_directory";
    gerp.makeVector(s); 
    gerp.printVector(); 

    SHOULD OUTPUT
    demo_directory/input3.txt
    hola 
    soy 
    file 3
    demo_directory/input2.txt
    hello 
    im 
    file 2
    demo_directory/input1.txt   
    hi 
    im 
    file 1
    
}
*/
//Step two parse thru all files and make the hashTable

//check hashtable functions 
void checkConstructor() {
    HashTable newTable; 
    assert(newTable.getActive() == 0);
    assert(newTable.getSize() == 100); 
}

void checkIndex() {
    HashTable newTable;
    assert(newTable.getIndex("car") == newTable.getIndex("CaR")); 
    cout << newTable.getIndex("car") << endl; 
}

void checkInsert() {
    HashTable newTable;
    newTable.insert("car",0,10); 
    assert(newTable.getActive() == 1); 
    newTable.insert("CAR",0,11); 
    assert(newTable.getActive() == 2); 
    newTable.insert("CAR",0,9); 
    assert(newTable.getActive() == 2); 
    newTable.insert("CaR",0,11); 
    newTable.printTable(); 
    newTable.printVector("car");
    newTable.printVector("CAR");
    newTable.printVector("CaR");
    newTable.printVector("lol");
    assert(newTable.getActive() == 3); 
}

/*
void checkSmallInsert() {
    HashTable newTable; 
    bucket *newbucket; 
    newbucket->key = "hello"; 
    newTable.insert(newbucket); 
    newTable.printTable(); 
}
*/

void checkContains() {
    HashTable newTable;
    newTable.insert("car",0,10); 
    assert(newTable.contains("car") == true); 
}



void checkInstances() {
    HashTable newTable; 
    newTable.insert("car",0,10); 
    newTable.insert("car",2,2); 
    newTable.printVector("car");

    //should output 
    /*
    car --> (File Index, Line Number) 0, 10 --> (File Index, Line Number) 2, 2
    
    
    */
}


/*
Hash check was continuously modified to test multiple things, while it would
have been a better idea to have separate tests, the following things were 
checked: 
    - Inserting 1 thing to the hashtable, printing out the table, and 
    getting the active members
    - Inserting 50 
    - Inserting 70 and checking that size goes to 202
    - Inserting 69 --> checking each value's hash index and then adding 
    50 more and making sure the values had changed positions, but 
    words that are the same (the, THE) had stayed together 


*/
void hashCheck() {
    HashTable newTable; 
    ifstream infile; 
    infile.open("100Words.txt");
    string s; 
    for(int i = 0; i < 69; i++) {
        infile >> s; 
        newTable.insert(s,0,i); 
    }
    newTable.printTable();
    cout << newTable.getActive() << endl; 
    cout << endl << endl; 
    for(int i = 0; i < 50; i++) {
        infile >> s; 
        newTable.insert(s,0,i); 
    }
    cout << endl; 
    cout << newTable.getActive() << endl; 
    cout << newTable.getSize() << endl << endl; 
    newTable.printTable(); 
    assert(newTable.getSize() == 202); 
}


/*
the parameter for list size was changed to string in order to 
call it without making a bucket pointer and get things messy
void checkListSize() {
    HashTable newTable; 
    newTable.insert("car",0,10); 
    newTable.insert("car",2,2); 
    newTable.printVector("car");
    assert(newTable.listSize("car")); 
}
*/

void checkSend(){
    /*
    Send to hash was modified so that it returned a printed version of
    the line being saved as a vector, I wanted to make sure it was the same
    or at least repeated values, without losing words 


    Gerp newGerp;
    string line = "the cat and the dog ran through the field ";
    string s = newGerp.sendToHash(line, 0,1); 
    cout << s << endl; 
    assert(s == line); 
    */
}