/**
 * File: functionsB.h
 * Programmer: Banyar Min Shin
*/

#ifndef BFUNCTIONS_H
#define BFUNCTIONS_H

#include <unordered_map>
#include <string>
#include "LinkedList.h"
#include "HashTable.h"

void output_name(std::string name);

void greetings();
// greets user, describes program, and invites user

std::string get_zipcode(std::unordered_map<int, std::string> zipMap);

void questionnaire (List& mylist, HashTable table, std::unordered_map<std::string, std::vector<std::string> > map);

#endif