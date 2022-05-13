#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include "LinkedList.h"

void build_list(List& mylist, std::string filename)
{
    /*
    ListNode* newListNode = new ListNode;
    newListNode->data = newdata;

    newListNode->prev = mylist.tail;
    if (mylist.tail == nullptr)
    {
        mylist.head = newListNode;
        mylist.tail = newListNode;
    }
    else
    {
        mylist.tail->next = newListNode;
        mylist.tail = newListNode;
    } 
    */

    std::ifstream in_file;
    std::string fileLine = "", ListNodeQuestion = "", ListNodeJobGroup = ""; 

    in_file.open(filename);

    while(getline(in_file, fileLine))
    {
        ListNode* newListNode = new ListNode;
        char lastCh = fileLine[fileLine.size() - 2];
        // std::cout << fileLine[fileLine.size() - 2] << std::endl;

        if(lastCh == '.')
        {
            newListNode->question = fileLine;
            
            getline(in_file, fileLine);
            for(int i = 0; i < fileLine.length() - 1; i++)
            {
                char ch = fileLine[i];
                if(ch == '|')
                {
                    // std::cout << ListNodeJobGroup << std::endl;
                    newListNode->JobGroups.push_back(ListNodeJobGroup);
                    ListNodeJobGroup = "";
                }
                else
                {
                    ListNodeJobGroup += ch;
                } //end of if else
            } //end of for
            // std::cout << ListNodeJobGroup << std::endl;
            newListNode->JobGroups.push_back(ListNodeJobGroup);
            ListNodeJobGroup = "";
            
            if (mylist.tail == nullptr)
            {
                mylist.head = newListNode;
                mylist.tail = newListNode;
            }
            else
            {
                newListNode->prev = mylist.tail;
                mylist.tail->next = newListNode;
                mylist.tail = newListNode;
            } //end of if else
        }
    } //end of while
}

void display (List& mylist) // displays list for testing
{
    ListNode* temp = new ListNode();
    temp = mylist.head;
    while (temp != nullptr)
    {
        std::cout << temp->question << " ";
        temp = temp->next;
    }
}

void free(List& mylist)
{   // deletes ListNodes of a list to prevent memory leaks
    ListNode* to_delete = mylist.head;
    while (to_delete != nullptr)
    {
        ListNode* next_to_delete = to_delete->next;
        delete to_delete;
        to_delete = next_to_delete;
    }
    mylist.head = nullptr;
    mylist.tail = nullptr;
}
