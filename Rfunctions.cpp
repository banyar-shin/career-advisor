/*
 * File: functionsR.cpp
 * Programmer: Ruby Huynh
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "HashTable.h"
#include "Vfunctions.h"
#include "Rfunctions.h"

//___________________________________________Zip Code Map_____________________________________________

//Creates a map with the zipcode and filename of Alameda/Santa Clara county
std::unordered_map<int, std::string> storeZip()
{
    std::unordered_map<int, std::string> zipcodes; //Map holding zipcodes under [countyname].txt
    std::string text; //Buffer for holding each line of .txt file

    std::ifstream reader; //For reading in file
    reader.open("zipcode_county_new.txt"); //Open the file, zipcode_county.txt, for reading

    //Checking if the file is opened properly
    if (reader.fail())
    {
        //If the file fails to open properly, notify user and return void
        std::cout << "Error with opening file." << std::endl;
        return zipcodes;
    }

    //Loop through each line of the .txt file
    while(std::getline(reader,text))
    {
        int zipcode_int; //Buffer storing the zipcode in integer form
        std::string zipcode_string; //Buffer storing the zipcode in string form
        std::string county; //Buffer storing the .txt file of a county

        std::istringstream sinput(text); //For reading in file and storing it under designated variables
        sinput >> zipcode_string >> county; //Read in and store zipcode under zipcode_string and .txt file name under county

        zipcode_int = stoi(zipcode_string); //Convert zipcode from string to int and store as an integer

        //zipcodes[county] = zipcode_int; //Store the zipcode into the map
        zipcodes[zipcode_int]=county;
    }
    reader.close();
    //Remove comments to print out the map if you want
    return zipcodes;
}

//Returns county's filename from user's inputted zipcode
std::string countyFile(std::unordered_map<int, std::string> zipMap, std::string zipcode)
{  
    //Converts user-inputted zipcode from string form to integer
    int zip=stoi(zipcode);

    //For iterating straight to key (user-inputted zipcode) to get filename
    auto zip_range = zipMap.find(zip);

    //If we can't find the key, say that the zipcode is not found
    if (zip_range == zipMap.end())
    {
        return "Not Found";
    }
    //If we find the zipcode key, return the county file name it is associated with
    else
    {
        return zip_range->second;
    }
}

//Checks if the zip code that the user enters exists
bool zipChecker(std::string zipcode, std::unordered_map<int, std::string> zipMap)
{
    bool zipExists=false; //Default is that zip code is not in the map. 

    //If zip code is of an inappropriately long length, return false
    if (zipcode.length() > 5)
    {
        return zipExists;
    }

    //Loops through the zipcode string
    for (int i=0; i<=zipcode.length()-1; i++)
    {
        char zipChar = zipcode[i]; //Store character in zipcode string at index i

        //If we find a character that is not a number, return false. 
        if (!isdigit(zipChar))
        {
            return zipExists;
        }
    }

    //Convert zip code from string to integer. Store under integer variable
    int zip = stoi(zipcode);

    //For iterating straight to key (user-inputted zipcode) to get filename
    auto zip_range = zipMap.find(zip);

    //If we can't find the key, set zipExists to flase to show zip code is not found
    if (zip_range == zipMap.end())
    {
        zipExists=false;
    }
    //If we find the zipcode key, set zipExists to true to show that user entered proper zip code
    else
    {
        zipExists=true;
    }

    return zipExists;
}

//_________________________________________Heapsorting Jobs___________________________________________

//Get index of left child in array of pointers
int get_left_child_index(int index)
{
    return 2 * index + 1;
}

//Get index of right child in array of pointers
int get_right_child_index(int index)
{
    return 2 * index + 2;
}

//For reheaping
void reheap(HashNode** jobArr, int root_index, int last_index)
{
    //Remove root
    HashNode* root_value = jobArr[root_index];

    int index = root_index; //Get current index of root
    bool done = false; //While loop condition

    while (!done)
    {
        int child_index = get_left_child_index(index); //Get index of left child of heap
        if (child_index <= last_index) //If we have not reached the end of the heap yet...
        {
            //Use right child instead if it is larger
            int right_child_index = get_right_child_index(index);

            if (right_child_index <= last_index && jobArr[child_index]->getHashNodeCounter() < jobArr[right_child_index]->getHashNodeCounter())
            {
                child_index = right_child_index;
            }
            if (root_value->getHashNodeCounter() < jobArr[child_index]->getHashNodeCounter())
            {
                //Promote child
                jobArr[index] = jobArr[child_index];
                index = child_index;
            }
            else
            {
                //Root is larger than both children
                done = true;
            }
        }
        else //If we have reached the end of the heap, return.
        {
            //No children
            done = true;
        }
    }

    //Store root value in vacant slot
    jobArr[index] = root_value;
}

//Uses heapsort to sort jobs by relevance to user using the counter
void jobSort(HashNode** jobArr, int size)
{
    int n = size - 1;
    for (int i = (n-1)/2; i>=0; i--)
    {
        reheap(jobArr, i, n); //Reheap
    }
    while (n>0)
    {
        //Swap root with last element
        HashNode* temp = jobArr[0];
        jobArr[0] = jobArr[n];
        jobArr[n]= temp;
        n--;
        reheap(jobArr, 0, n); //Reheap
    }
}

//Test function. Used to print the heap. 
void testPrintHeap(HashNode** jobArr, int size)
{
    std::cout << std::endl;
    for (int i=0; i < size; i++)
    {
        std::cout << jobArr[i]->getHashNodeJobTitle() << std::endl;
        std::cout << jobArr[i]->getHashNodeCounter() << std::endl; 
    }
    std::cout << std::endl;
}

//Test function. Used to print the heap. 
void topTen(HashNode** jobArr, int size)
{
    std::cout << "\nYour Top Ten results are..." << std::endl;
    int counter = 1; //For printing the index of the top ten list
    std::ofstream out_file("userdata.csv", std::ios::app);

    //Loops through the top ten jobs and prints them out from least to most relevant
    for (int i=size-1; i>=(size-10); i--)
    {
        std::cout << "\n" << counter << ". " << jobArr[i]->getHashNodeJobTitle() << std::endl;
        std::cout << "Income: " << jobArr[i]->getHashNodeJobWage() << std::endl;
        counter++;

        for (int j = 0; j < jobArr[i]->getHashNodeJobTitle().size() - 1; j++)
        {
            out_file << jobArr[i]->getHashNodeJobTitle()[j];
        }
        out_file << ",";
    }
    std::cout << std::endl;
    out_file.close();
}