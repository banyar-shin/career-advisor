/**
 * Many of the following classes were taken from the text book.
 * Some changes were applied to fit the context of the lab.
*/

#ifndef QUEUELL_H
#define QUEUELL_H
#include <iostream>
#include <string>
#include <fstream>
#include "HashTable.h"

class QueueNode
{
private:
	int scale;
	QueueNode* next;
friend class Queue;   
};

/**
	An implementation of a queue as a sequence of QueueNodes.
*/
class Queue
{
public:   
	/** 
		Constructs an empty queue.
	*/
	Queue();

	/**
		Adds an element to the tail of the queue.
		@param element the element to add
	*/
	void push(int scale);

	/**
		Yields the element from the head of the queue.
		@return the head element
	*/
	int front() const;

	/**
		Removes the element from the head of the queue.
	*/
	void pop();

	/**
		Yields the number of elements in this queue.
		@return the size
	*/
	int size() const;

	/**
		Outputs the contents of a queue to userdata.csv
	*/
    void WriteToFile();

private:
	QueueNode* first;
	QueueNode* last;
	int len;
};

#endif