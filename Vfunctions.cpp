/**
 * File: functionsV.cpp
 * Programmer: Vinh Pham
*/ 

#include <string> 
#include <fstream>
#include <queue>
#include "HashTable.h"

//A function to make a hash table
HashTable import_hash(std::string file)
{
    HashTable newTable(100); //create an empty hash table with size of num_of_bucket (initalized here to 100 for testing)
    
    std::ifstream in_file; //ifstream variable to be used to read a file
    std::string wage = "", title = ""; //Variable to hold the title of the job, Variable to hold the wage of the job
    std::string line; //variable to getline in file
    
    in_file.open(file); //open the county txt file
    while (getline(in_file, line)) //Get line in the county txt file
    {
        //loop to get the string before the "|" into job wage
        //loop to get the string after the "|" into job title
        int counter = 0;
        for (int i = 0; i < line.length(); i++)
        {
            char ch = line[i]; //Get the morse code in the line
            if (ch == '|')
            {
                break;
            }
            else
            {
                wage += ch;
                counter++;
            }
        }
        for (int i = counter + 1; i < line.length(); i++)
        {
            char ch = line[i]; //Get the morse code in the line
            title += ch;
        }
        newTable.insert(wage, title); //Insert the wage and job title into the hash table
        wage = "";
        title = "";
    }
    //std::string newStr = newTable.returnJobWage(title);
    //std::cout << newStr << std::endl;
    in_file.close(); // close the file

    return newTable; //returns a hash table
}