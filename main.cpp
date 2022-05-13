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
    HashTable ourtable = import_hash(userCounty); //Makes a hash table using the jobs. Holds their data specifications
    std::unordered_map<std::string, std::vector<std::string> > ourmap = jobMap ("jobs_final.txt"); 
    build_list(ourlist, "questions_final.txt"); //Makes a linked list of questions to ask the user 
    questionnaire (ourlist, ourtable, ourmap); //Traverse through list of questions, printing them and taking user input
    int datasize = ourtable.size(); //Initialize integer holding the size of the hash table

    //HashNode** ptrArray = new HashNode* [datasize]; //Initialize an array of pointers
    //ptrArray = ourtable.arrayOfHashNodes(ourtable); //Populate array of pointers to nodes in hash table

    HashNode** ptrArray = ourtable.arrayOfHashNodes(ourtable); //Create an array of HashNode pointers from the hash table to the nodes can be sorted according to their counter values
    jobSort(ptrArray, datasize); //Heapsort the jobs based on counter points accumulated from questionnaire
    // testPrintHeap(ptrArray, datasize);
    topTen(ptrArray, datasize); //Print out the top ten jobs that are most relevant to the user

    // for (int i = 0; i < ourtable.size(); i++)
    // {
    //     std::cout << "Practice Output: " << std::endl;
    //     std::cout << ptrArray[i]->getHashNodeJobWage() << std::endl;
    //     std::cout << ptrArray[i]->getHashNodeJobTitle() << std::endl;
    //     std::cout << ptrArray[i]->getHashNodeCounter() << std::endl;
    // }
    
    delete[] ptrArray; //Deletes the array of pointers to nodes in hash table
    free(ourlist); //Deletes the linked list
    ourtable.deallocateHashTable(ourtable); //Deletes the hash table
    
    survey();

    return 0;
}