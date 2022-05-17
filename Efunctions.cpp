/**
 * File: Efunctions.cpp
 * Programmer: Eric Clark
*/ 

#include "Efunctions.h"

std::unordered_map<std::string, std::vector<std::string> > jobMap(std::string filename)
{
    //Initialize map to be returned by function
    std::unordered_map<std::string, std::vector<std::string> > map; 

    std::ifstream in(filename); //For reading in jobs.txt
    std::string line = "", jobGroup = "", jobTitle = ""; //String variables. For holding lines in jobs.txt, job group and job title
    std::vector<std::string> jobs; //Initialize vector to store jobs

    //Loop through each line of jobs.txt
    while(std::getline(in, line))
    {
        if (line[0] == '@') //If line starts with @
        {
            for(int i = 1; i < line.length() - 1; i++) //Traverse the line
            {
                jobGroup += line[i]; //Job Group Name
            }
            line = ""; //Clear line
        }
        else if (line[0] == '-') //If line is -
        {
            map[jobGroup] = jobs; //Input into map
            jobs.clear(); //Clear jobs vector
            jobGroup = ""; //Clear job group name
        }
        else //If line is normal (job names)
        {
            jobTitle = line; //Get the name
            jobs.push_back(jobTitle); //Push back into vector
            jobTitle = ""; //Clear the variable
        }
    }
    in.close(); //Close file
    return map; //Return the map
}


//Returns a list of jobs in the form of a vector 
std::vector<std::string> returnJobs(std::string jobGroup, std::unordered_map<std::string, std::vector<std::string> > jobs)
{   
    auto job_range = jobs.find(jobGroup); //Find the jobs vector linked to a Job Group
    return job_range->second; //Return the found vector
}
