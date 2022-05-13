/**
 * File: functionsE.h
 * Programmer: Eric Clark
*/ 

#ifndef EFUNCTIONS_H
#define EFUNCTIONS_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>

std::unordered_map<std::string, std::vector<std::string> > jobMap(std::string filename);
//creates map with job and job group
std::vector<std::string> returnJobs(std::string jobGroup, std::unordered_map<std::string, std::vector<std::string> > jobs);
//returns the job list for given job group

#endif