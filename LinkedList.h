#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "HashTable.h"

struct ListNode //ListNode struct
{
    std::string question = "";
    int scale  = 0;
    std::vector<std::string> JobGroups;
    ListNode* next = nullptr;   // initializes the next pointer
    ListNode* prev = nullptr;   // initializes the prev pointer
};

struct List
{
    ListNode* traverse = nullptr;
    ListNode* head = nullptr;   // initializes head pointer
    ListNode* tail = nullptr;   // initializes tail pointer
};

void build_list(List& mylist, std::string filename);
// to add a ListNode at the end of a linked list

void display (List& mylist);
// displays the contents of a linked list for testing purposes

void free(List& mylist);
// deallocates the list by deleting every ListNode, prevent mem leak

#endif