/**
 * Many of the following classes were taken from the text book.
 * Some changes were applied to fit the context of the lab.
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>

//A function to return the hash code of a string
int hash_code(const std::string& letter);

class HashTable;
class Iterator;

class HashNode
{
private:  
   std::string jobWage; //String variable to hold the wage of a job
   std::string jobTitle; //String variable to hold the title of the job
   int counter = 0; //A counter to represent the user's suitability to the job
   HashNode* next; //A pointer variable to represent the next node in the hash table

public:
   std::string getHashNodeJobWage() const; //A function to get the jobWage inside a node
   std::string getHashNodeJobTitle() const; //A function to get the jobTitle inside a node
   int getHashNodeCounter() const; //A function to get the counter inside a node

friend class HashTable;
friend class Iterator;
};

class Iterator
{
public:
   void next(); //A function to point the iterator to the next node
   bool equals(const Iterator& other) const; //Checking if the iterator points to the current node
   
private:
   const HashTable* container;
   int bucket_index;
   HashNode* current;
   
friend class HashTable;
};

class HashTable
{
public:
   //Functions from the textbook; modified slightly
   HashTable(int nbuckets); //Constructor to create a hash table with specified amount of buckets
   int count (const std::string& y); //A function to check if a HashNode is present or not (returns 1 if yes, returns 0 if no)
   void insert(const std::string& x, const std::string& y); //A function to insert a new HashNode into the hash table
   void erase(const std::string& y); //A function to erase a node from the hash table
   Iterator begin() const; //Set the iterator to the beginning of the hash table
   Iterator end() const; //Set the iterator to the end of the hash table
   int size() const; //Get the size of the hash table/number of elements 
   
   //Functions that were made to suit the program
   std::string returnJobWage(const std::string& y); //Returns the jobWage from a node based on the inputted job title
   int returnCounter(const std::string& y); //Returns the counter from a node based on the inputted job title
   void incrementCounter(const std::string& y, int scale); //Increment the counter in a node based on the inputted job title and user's selection
   HashNode** arrayOfHashNodes(HashTable& myTable); //A function to create an array of HashNode pointers
   void deallocateHashTable(HashTable& myTable); //Function created to deallocate the hash table to free memory
private:
   std::vector<HashNode*> buckets;
   int current_size;   

friend class Iterator;
};

#endif