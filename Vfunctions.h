/**
 * File: functionsV.h
 * Programmer: Vinh Pham
*/ 

#ifndef VFUNCTIONS_H
#define VFUNCTIONS_H
#include "HashTable.h"

//This function determines the number of buckets to make based on the lines of cipher.txt
//int getBucket(std::string file);

//A function to make a hash table based on a text file 
//The text file that should be passed is one that that contains a county-type .txt file with the wages and occupations
HashTable import_hash(std::string file);


#endif