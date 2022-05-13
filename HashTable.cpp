/**
 * The following classes were taken from the text book.
 * Minor changes were applied to fit the context of the lab.
*/

#include <iostream>
#include "HashTable.h"

//Hash code to be tested on 
int hash_code(const std::string& jobName)
{
   int h = 0;
   h = (jobName[0] + jobName[1] + jobName[2]) % 100; //originally % 26
   return h; //return the hash code
} //end of int

HashTable::HashTable(int nbuckets)
{
   for (int i = 0; i < nbuckets; i++)
   {
      buckets.push_back(nullptr);
   }
   current_size = 0; 
} //end of HashTable constructor

int HashTable::count(const std::string& y)
{
   //Get the hash code of the a string (which is the occupational title)
   int h = hash_code(y);
   h = h % buckets.size();
   if (h < 0) { h = -h; } //If the hash code ends up being a negative, returns the positive version
      
   HashNode* current = buckets[h]; //Goes to the bucket that contains that occupational title
   while (current != nullptr) //If the HashNode in the bucket is not empty
   {
      if (current->jobTitle == y) //If the current HashNode's job title is equal to the job title searched for
      { 
		  return 1; //return 1 if the job is in the hash table; for testing the presence of the job
	  }
      current = current->next; //move to the next node if the current node is not the one being searched for
   }
   return 0; //return 0 if the job is not present in the hash table; for testing the presence of the job
} //end of int


void HashTable::insert(const std::string& x, const std::string& y)
{
   //Get the hash code of the a string (which is the occupational title)
   int h = hash_code(y);
   h = h % buckets.size();
   if (h < 0) { h = -h; } //If the hash code ends up being a negative, returns the positive version
      
   HashNode* current = buckets[h]; //Goes to the bucket that contains that occupational title
   while (current != nullptr) //If the HashNode in the bucket is not empty
   {
      if (current->jobWage == x && current->jobTitle == y ) //if the current node's wage and job title matches with the one being inserted
      { 
		  return; //ignores inserted node so no dublicate
	   }
      // Already in the set
      current = current->next;
   }
   //setting the wage and job title of a new node and then insert that node into the hash table
   HashNode* new_HashNode = new HashNode;
   new_HashNode->jobWage = x;
   new_HashNode->jobTitle = y;
   new_HashNode->next = buckets[h];
   buckets[h] = new_HashNode;
   current_size++;
} //end of void


void HashTable::erase(const std::string& y)
{
   //Get the hash code of the a string (which is the occupational title)
   int h = hash_code(y);
   h = h % buckets.size();
   if (h < 0) { h = -h; } //If the hash code ends up being a negative, returns the positive version
      
   HashNode* current = buckets[h]; //Goes to the bucket that contains that occupational title
   HashNode* previous = nullptr; //Set the previous pointer of the node to null to eliminate the connection with the node before it 
   while (current != nullptr) //If the HashNode in the bucket is not empty
   {
      if (current->jobTitle == y) //If the current HashNode's job title is equal to the job title searched for
      {
         if (previous == nullptr) 
         {
            buckets[h] = current->next;
         }
         else
         {
            previous->next = current->next;
         }
         delete current; //delete that node from the hash table
         current_size--; //decrement the size of the hash table
         return; //return to function declaration
      }
      previous = current;
      current = current->next; //moving to the next node if the current job title is not the one to be deleted
   } //end of while
} //end of void


int HashTable::size() const
{
   return current_size;
} //end of int


std::string HashTable::returnJobWage(const std::string& y)
{
   //Get the hash code of the a string (which is the occupational title)
   int h = hash_code(y);
   h = h % buckets.size();
   if (h < 0) { h = -h; } //If the hash code ends up being a negative, returns the positive version
   
   HashNode* current = buckets[h]; //Goes to the bucket that contains that occupational title
   
   while (current != nullptr) //If the HashNode in the bucket is not empty
   {
      if (current->jobTitle == y) //If the current HashNode's job title is equal to the job title searched for
      { 
          return current->jobWage; //Return the wage associated with that job
      }
         // Already in the set
      current = current->next; //If the job title is not found, move to the next HashNode in the bucket
   } //end of while

   return current->jobWage; //Return the wage associated with that job
} //end string


int HashTable::returnCounter(const std::string& y)
{
   //Get the hash code of the a string (which is the occupational title)
   int h = hash_code(y);
   h = h % buckets.size();
   if (h < 0) { h = -h; } //If the hash code ends up being a negative, returns the positive version
   
   HashNode* current = buckets[h]; //Goes to the bucket that contains that occupational title
   
   while (current != nullptr) //If the HashNode in the bucket is not empty
   {
      if (current->jobTitle == y) //If the current HashNode's job title is equal to the job title searched for
      { 
          return current->counter; //to retrieve the counter that gauges the job's capability with the user
      }
         // Already in the set
      current = current->next; //If the job title is not found, move to the next HashNode in the bucket
   } //end of while

   return current->counter; //to retrieve the counter that gauges the job's capability with the user
} //end of int


void HashTable::incrementCounter(const std::string& y, int scale)
{
   //Get the hash code of the a string (which is the occupational title)
   int h = hash_code(y); 
   h = h % buckets.size(); 
   if (h < 0) { h = -h; } //If the hash code ends up being a negative, returns the positive version
   
   HashNode* current = buckets[h]; //Goes to the bucket that contains that occupational title
   
   while (current != nullptr) //If the HashNode in the bucket is not empty
   {
      if (current->jobTitle == y) //If the current HashNode's job title is equal to the job title searched for
      {
         current->counter += (scale - 3); //Increment or decrement the counter based on the user's input
         // std::cout << current->jobTitle << std::endl;
         // std::cout << current->counter << std::endl;
      }
         // Already in the set
      current = current->next; //If the job title is not found, move to the next HashNode in the bucket
   } //end of while
   // std::cout << current->jobTitle << ": " << current->counter;
} //end of void


void HashTable::deallocateHashTable(HashTable& myTable)
{
   Iterator iter = myTable.begin(); //set the iterator at the beginning of the hash table to start iterating
   
   int i = 0;
   while(iter.current != nullptr)
   {
      HashNode* temp = iter.current; //set the pointer of a HashNode to where the iterator is currently pointing in the hash table
      iter.next(); //point iterator to next element
      delete temp; //delete pointer
   }
} //end of void


HashNode** HashTable::arrayOfHashNodes(HashTable& myTable)
{
   Iterator iter = myTable.begin(); //set the iterator at the beginning of the hash table to start iterating
   HashNode** newTable = new HashNode*[myTable.size()]; //create a dynamically allocated array of pointers to HashNodes based on size of hash table

   int i = 0; //to start insertion at the first position of the dynamically allocated array
   while(iter.current != nullptr)
   {
      HashNode* temp = iter.current; //set the pointer of a HashNode to where the iterator is currently pointing in the hash table
      iter.next(); //point iterator to next element
      newTable[i] = temp; //put the element pointed in the hash table to the array
      i++; //increment to the next position in newTable

      // delete temp; // PUT THIS HERE??? IF PROBLEM IN VALGRIND, LOOK HERE
   }
   return newTable;
} //end of HashNode 


std::string HashNode::getHashNodeJobWage() const
{
   return jobWage;
} //end of string


std::string HashNode::getHashNodeJobTitle() const
{
   return jobTitle;
} //end of string


int HashNode::getHashNodeCounter() const
{
   return counter;
} //end of int


Iterator HashTable::begin() const
{
   Iterator iter;
   iter.current = nullptr;
   iter.bucket_index = -1;
   iter.container = this;
   iter.next();
   return iter;
} //end of Iterator


Iterator HashTable::end() const
{
   Iterator iter;
   iter.current = nullptr;
   iter.bucket_index = buckets.size();
   iter.container = this;
   return iter;
} //end of Iterator


bool Iterator::equals(const Iterator& other) const
{
   return current == other.current;
} //end of bool


void Iterator::next()
{
   if (bucket_index >= 0 && current->next != nullptr)
   {
      // Advance in the same bucket
      current = current->next;
   }   
   else 
   {
      // Move to the next bucket
      do
      {
         bucket_index++;
      }
      while (bucket_index < container->buckets.size() && container->buckets[bucket_index] == nullptr);
      if (bucket_index < container->buckets.size())
      {
         // Start of next bucket
         current = container->buckets[bucket_index];         
      }
      else 
      {
         // No more buckets
         current = nullptr;
      } //end of if/else
   } //end of if/else
} //end of while