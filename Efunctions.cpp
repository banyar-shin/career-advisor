/**
 * File: functionsE.cpp
 * Programmer: Eric Clark
*/ 

#include "Efunctions.h"

/*
std::unordered_map<std::string, std::vector<std::string> > jobMap(std::string filename)
{
    //Initialize map to be returned by function
    std::unordered_map<std::string, std::vector<std::string> > map; 

    std::ifstream in("jobs.txt"); //For reading in jobs.txt
    std::string line, jobGroup, jobTitle; //String variables. For holding lines in jobs.txt, job group and job title
    std::vector<std::string> jobs; //Initialize vector to store jobs

    //Loop through each line of jobs.txt
    while(std::getline(in, line))
    {
        if (line == ",") //If we meet the "," partition...
        {
            if (!jobs.empty()) //If jobs vector is not empty...
            {
                map[jobGroup] = jobs; //Add jobs vector holding job titles to respective job group(key) in map
                jobGroup = ""; //Clear the variable holding the job group
                jobs.clear(); //Clear the vector holding the job title
            }
            std::getline(in, jobGroup); //Get line holding the job group
            std::getline(in, line); //Get the next line holding the job title
            continue; //Move on to next line (Do we need this? We skip else if anyways.)
        }
        else if(line != ",") //If we are on a line that is not the "," partition...
        {
            jobTitle = line; //Store the line as a string in jobTitle. The line is the job title
            jobs.push_back(jobTitle); //Add the job title to the jobs vector
        }
    }
    map[jobGroup] = jobs; //Add jobs vector holding job titles to respective job group(key) in map
    jobGroup = ""; //Clear string variable holding the job group
    jobs.clear(); //Clear jobs vector
    in.close();
    return map; //Return the map that we had filled
}
*/


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
        if (line[0] == '@')
        {
            for(int i = 1; i < line.length() - 1; i++)
            {
                jobGroup += line[i];
            }
            line = "";
        }
        else if (line[0] == '-')
        {
            // std::cout << std::endl;
            // std::cout << jobGroup << std::endl;
            // std::cout << jobGroup.length() << std::endl;
            // for(int i = 0; i < jobs.size(); i++)
            // {
            //     std::cout << jobs[i] << std::endl;
            // }
            map[jobGroup] = jobs;
            jobs.clear();
            jobGroup = "";
        }
        else
        {
            jobTitle = line;
            // std::cout << jobTitle << std::endl;
            jobs.push_back(jobTitle);
            jobTitle = "";
        }
    }
    in.close();
    return map;
}


//Returns a list of jobs in the form of a vector 
std::vector<std::string> returnJobs(std::string jobGroup, std::unordered_map<std::string, std::vector<std::string> > jobs)
{   
    // std::vector<std::string> jobList;
    // for (auto x : jobs)
    // {
    //     for(int j = 0; j < x.second.size(); j++)
    //     {
    //         jobList.push_back(x.second[j]);
    //     }
    // }

    // return jobList;

    auto job_range = jobs.find(jobGroup);
    return job_range->second;
}
