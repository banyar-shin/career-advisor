/**
 * Many of the following classes were taken from the text book.
 * Some changes were applied to fit the context of the lab.
*/

#include "QueueLL.h"

Queue::Queue()
{  
	first = nullptr;
	last = nullptr;
	len = 0;
}

void Queue::push(int scale)
{  
	QueueNode* new_node = new QueueNode;
    new_node->scale = scale;
	new_node->next = nullptr;
	if (last == nullptr) 
	{
		first = new_node;
	}
	else
	{
		last->next = new_node;
	}
	last = new_node;
	len++;
}

int Queue::front() const
{
	return first->scale;
}

void Queue::pop()
{
	QueueNode* to_delete = first;
	first = first->next;
	delete to_delete;
	len--;
}

int Queue::size() const
{
	return len;
}

void Queue::WriteToFile()
{
    std::ofstream out_file("userdata.csv", std::ios::app); //Open file
    while (size() != 0) //If queue is not empty
    {
        out_file << front() << ","; //Output to file
        pop(); //Pop from queue
	}
    out_file << ","; //Output an additonal comma for csv file
    out_file.close(); //Close file
}