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
    std::ofstream out_file("userdata.csv", std::ios::app);
    while (size() != 0)
    {
        out_file << front() << ",";
        pop();
    }
    out_file << ",";
    out_file.close();
}