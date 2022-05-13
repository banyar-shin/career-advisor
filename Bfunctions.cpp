/**
 * File: functionsB.cpp
 * Programmer: Banyar Min Shin
*/ 

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <limits>
#include <fstream>
#include "Bfunctions.h"
#include "Efunctions.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "Rfunctions.h"
#include "QueueLL.h"

void output_name (std::string name)
{
    std::ofstream out("userdata.csv", std::ios::app);
    out << name << ",";
    out.close();
}

void greetings()    
{   // greets user, describes program, and invites user
    std::string name = ""; // to store
    std::cout << "\nWhat is your name? ('-' to skip): ";
    std::getline(std::cin, name);
    
    if (name == "-")
        name = "User";

    output_name(name);
    std::cout << "\nHello, " << name << ", I'm Erena, your virtual counselor! My purpose is to provide\n"
    << "guidance towards a career field in Alameda or Santa Clara county. I will be asking you\n" 
    << "for your zip code in any of these two counties so I know where to look in my binder,\n" 
    << "and you'll have to tell me how much you agree to a number of statements. Then, I'll\n"
    << "recommend you to ten jobs that suits you according to your answers.\n"
    << "\nDo you want to proceed? (y/n): ";

    std::string ans = ""; // string to store input
    do
    {
        std::cin >> ans; // gets the input
        if (ans == "y" || ans == "Y") // if input is yes
        {
            std::cout << "\nOkay! Let's get this started!\n";
            break; // end loop
        }
        else if (ans == "n" || ans == "N") // if input is no
        {
            std::cout << "\nOkay... Have a great day.\n\n";
            exit(0); // exit program
        }
        else // if invalid input
        {
            std::cin.clear(); // clears cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Invalid input, please only enter (y/n): "; // prints try again
        }
    } while (ans != "y" || ans != "Y" || ans != "n" || ans != "N");
}


std::string get_zipcode(std::unordered_map<int, std::string> zipMap)
{
    std::string zipcode; //Store user-inputted zip code
    bool foundZip; //True if inputted zip code exists. False if it does not.

    //Prompt the user to enter their zip code and store it under string variable
    std::cout << "\nPlease give me your zip code: "; 
    std::cin >> zipcode;

    //Check if the inputted zip code is inside the map
    foundZip = zipChecker(zipcode, zipMap);

    //If the zip code is found to not be in the map the first time, enter the while loop.
    //Loop until the user enters a zip code that is exists in the map.
    while (!foundZip)
    {
        //Tell user that their zip code does not exist. Prompt them to enter again.
        std::cout << "Hmm... I can't find this zip code in my binder. Please try again: ";
        std::cin >> zipcode;

        //Check if the inputted zip code is inside the map
        foundZip = zipChecker(zipcode, zipMap);
    }

    return zipcode; //Return zip code
}

//Traverses through list of questions, printing them and taking user input
void questionnaire (List& mylist, HashTable jobTable, std::unordered_map<std::string, std::vector<std::string> > jobMap)
{
    int scale; //Stores user's answer to question
    Queue queue;
    mylist.traverse = mylist.head; //Begin at head of list
    std::cout << "\nPlease answer the questions with this scale:\n1: Strongly Disagree\n2: Disagree\n3: Neutral\n4: Agree\n5: Strongly Agree\n";
    //Traverse the list until we get to the end of the list
    while (mylist.traverse != nullptr)
    {   
        //Print question and take in user's answer 
        std::cout << std::endl << mylist.traverse->question << std::endl;
        std::cout << "--> (1 - 5): ";
        std::cin >> scale;
        //Input validation for the answer
        while (scale < 1 || scale > 5)
        {
            std::cout << "Invalid! (1 - 5 only): ";
            std::cin >> scale;
        } //end of while 

        if(scale > 0 && scale < 6) //If user answers yes to the question
        {
            //Increment counters of group of jobs associated with question
            for(int i = 0; i < mylist.traverse->JobGroups.size(); i++)
            {
                //Go the job category
                std::string category = mylist.traverse->JobGroups[i];
                // std::cout << "Category in For Loop: " << category << std::endl;

                //Used to create vector holding jobs within the category
                std::vector<std::string> innerVec = returnJobs(category, jobMap);
                // for (int i = 0; i < innerVec.size(); i++)
                // {
                    // std::cout << innerVec[i] << std::endl;
                // }

                //Loops through the vector holding the jobs within the category
                for(int j = 0; j < innerVec.size(); j++)
                {
                    jobTable.incrementCounter(innerVec[j], scale);
                } //end of for
            } //end of foor
        } //end of if

        //Store answer
        // mylist.traverse->scale = scale;
        queue.push(scale);
        
        // run function
        if (mylist.traverse == mylist.tail)
            break;
        else
            mylist.traverse = mylist.traverse->next;
    } //end of while
    queue.WriteToFile();
}