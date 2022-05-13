#include <iostream>
#include <string>
#include <fstream>
#include "HashTable.h"
#include "LinkedList.h"
#include "Efunctions.h"
#include "Bfunctions.h"
#include "Rfunctions.h"
#include "Vfunctions.h"
#include "BinaryTree.h"
#include <unordered_map>

int main()
{
    greetings(); //Greet the User

    std::unordered_map<int, std::string> zipcodemap = storeZip(); //Store zipcodes from files to map
    std::string zipcode = get_zipcode(zipcodemap); //Gets zipcode from the user
    std::string userCounty = countyFile(zipcodemap, zipcode); //Uses user's zipcode to find county file

    List ourlist; //Initialize a linked list
    build_list(ourlist, "Questions.txt"); //Makes a linked list of questions to ask the user 

    HashTable ourtable = import_hash(userCounty); //Makes a hash table using the jobs. Holds their data specifications
    std::unordered_map<std::string, std::vector<std::string> > ourmap = jobMap ("Jobs.txt"); 
    
    questionnaire (ourlist, ourtable, ourmap); //Traverse through list of questions, printing them and taking user input
    int size = ourtable.size(); //Initialize integer holding the size of the hash table

    //HashNode** ptrArray = new HashNode* [size]; //Initialize an array of pointers
    //ptrArray = ourtable.arrayOfHashNodes(ourtable); //Populate array of pointers to nodes in hash table

    HashNode** ptrArray = ourtable.arrayOfHashNodes(ourtable); //Create an array of HashNode pointers from the hash table to the nodes can be sorted according to their counter values
    jobSort(ptrArray, size); //Heapsort the jobs based on counter points accumulated from questionnaire
    // testPrintHeap(ptrArray, size); //To test if data is correctly sorted and present
    topTen(ptrArray, size); //Print out the top ten jobs that are most relevant to the user
    
    free(ourlist); //Deletes the linked list
    ourtable.deallocateHashTable(ourtable); //Deletes the hash table
    delete[] ptrArray; //Deletes the array of pointers to nodes in hash table
    
    survey();
    
    return 0;
}