/**
 * File: functionsR.h
 * Programmer: Ruby Huynh
 * Note: Use storeZip before using countyFile
*/ 

#ifndef RFUNCTIONS_H
#define RFUNCTIONS_H
#include <unordered_map>


//_________________________________Zip Code Map___________________________________
//Creates a map with the zipcode and filename of Alameda/Santa Clara county
std::unordered_map<int, std::string> storeZip();

//Returns county's filename from user's inputted zipcode
std::string countyFile(std::unordered_map<int, std::string> zipMap, std::string zipcode);

//Checks if the zip code that the user enters exists
bool zipChecker(std::string zipcode, std::unordered_map<int, std::string> zipMap);


//_______________________________Heapsorting Jobs_________________________________

//Get index of left child in array of pointers
int get_left_child_index(int index);

//Get index of right child in array of pointers
int get_right_child_index(int index);

//For reheaping
void reheap(HashNode** jobArr, int root_index, int last_index);

//Uses heapsort to sort jobs by relevance to user using the counter
void jobSort(HashNode** jobArr, int size);

//Prints out top ten results for user using sorted heap
void topTen(HashNode** jobArr, int size);

//Test function. Used to print the heap. 
void testPrintHeap(HashNode** jobArr, int size);

#endif