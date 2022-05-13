#include <algorithm>
#include <iostream>
#include "BinaryTree.h"
#include <fstream>

/**
   Gets the left pointer variable of the TreeNode
   @return left pointer stored in TreeNode
*/
TreeNode* TreeNode::get_left()
{
    return left;
}

/**
   Gets the right pointer variable of the TreeNode
   @return right pointer stored in TreeNode
*/
TreeNode* TreeNode::get_right()
{
    return right;
}

BinaryTree::BinaryTree()
{
	root = nullptr;
} 

BinaryTree::BinaryTree(std::string root_question) 
{
	root = new TreeNode;
	root->question = root_question;
	root->left = nullptr;
	root->right = nullptr;
}

BinaryTree::BinaryTree(std::string root_question, BinaryTree left, BinaryTree right)
{
	root = new TreeNode;
	root->question = root_question;
	root->left = left.root;
	root->right = right.root;
}
	
int BinaryTree::height(const TreeNode* n) const
{
	if (n == nullptr) { return 0; }
	else { return 1 + std::max(height(n->left), height(n->right)); }
}

int BinaryTree::height() const { return height(root); }

bool BinaryTree::empty() const { return root == nullptr; }

std::string BinaryTree::question() const { return root->question; }
	
BinaryTree BinaryTree::left() const
{ 
	BinaryTree result;
	result.root = root->left; 
	return result;
}

BinaryTree BinaryTree::right() const
{ 
	BinaryTree result;
	result.root = root->right; 
	return result;
}

TreeNode* BinaryTree::get_root()
{
	return this->root;
}

void BinaryTree::deallocateTree(TreeNode* current)
{
    if (current == nullptr) // if the current pointer is null
        return; // ends function
    deallocateTree(current->get_left()); // gets left pointer and recurses
    deallocateTree(current->get_right()); // gets right pointer and recurses
    delete current; // deletes the TreeNode
}

void survey()
{
	std::ofstream out("userdata.csv", std::ios::app);
    std::string prompt;
    std::cout << "Would you like to provide feedback for the program? (y/n): ";
    std::cin >> prompt;

	while (prompt != "N" && prompt != "n" && prompt != "Y" && prompt != "y")
    {
		std::cout << "Invalid input, please only enter (y/n): ";
		std::cin >> prompt;
	}
	if (prompt == "N" || prompt == "n")
	{
		out << std::endl;
		std::cout << "\nThank you for coming by!\n\n";
	}
    else if (prompt == "Y" || prompt == "y")
    {
        BinaryTree question_tree(
	    	"Were the jobs relevant to you?",
	    	BinaryTree("Can you see this being useful to others?",
	    		BinaryTree("Would you recommend this to your friends?",
	    			BinaryTree("\nThank you for your positive feedback!\n"),
	    			BinaryTree("\nSorry to hear that. Thank you for the feedback.\n")),
	    		BinaryTree("\nSorry to hear that. Thank you for the feedback.\n")),
	    	BinaryTree("Were we far off the mark?",
	    		BinaryTree("Is is close enough for us to possibly reach it by adjusting the system?",
	    			BinaryTree("\nThank you for your feedback!\n"),
	    			BinaryTree("\nSorry to hear that. Thank you for the feedback.\n")),
	    		BinaryTree("If we made improvements, would you try again?",
	    			BinaryTree("\nThank you for your feedback!\n"),
	    			BinaryTree("\nSorry to hear that. Thank you for the feedback.\n"))));

		TreeNode* pointer;
		pointer = question_tree.get_root();

        bool done = false;
	    while (!done)
	    {
	    	BinaryTree left = question_tree.left();
	    	BinaryTree right = question_tree.right();
	    	if (left.empty() && right.empty())
	    	{
	    		std::cout << question_tree.question() << std::endl;
	    		done = true;
	    	}
	    	else
	    	{
	    		std::string response;
	    		std::cout << std::endl << question_tree.question() << " (y/n): ";
	    		std::cin >> response;

	    		while (response != "y" && response != "n" && response != "Y" && response != "N")
				{
					std::cout << "Invalid input, please only enter (y/n): ";
					std::cin >> response;
				}

	    		if (response == "y" || response == "Y")
	    		{
	    			question_tree = left;
					out << "," << response;
	    		}
	    		else
	    		{
	    			question_tree = right;
					out << "," << response;
	    		}         
	    	}
	    }
		out << std::endl;
		question_tree.deallocateTree(pointer);
    }
}