/**
 * Many of the following classes were taken from the text book.
 * Some changes were applied to fit the context of the lab.
*/

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

//User takes post-program survey
void survey()
{
	std::ofstream out("userdata.csv", std::ios::app); //Open userdata.csv to write to it
    std::string prompt; //Store's user input
    std::cout << "Would you like to provide feedback for the program? (y/n): ";
    std::cin >> prompt;

	//Input validation for user's input to do survey or not
	while (prompt != "N" && prompt != "n" && prompt != "Y" && prompt != "y")
    {
		std::cout << "Invalid input, please only enter (y/n): ";
		std::cin >> prompt;
	}
	//End the program if user doesn't want to take the survey
	if (prompt == "N" || prompt == "n")
	{
		out << std::endl;
		std::cout << std::endl;
	}
	//If user wants to take the survey, use binary tree to let them take the survey
    else if (prompt == "Y" || prompt == "y")
    {
		//Construct Binary Tree with the questions and responses to user
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
			//Make subtree for the left and subtree for the right of root
	    	BinaryTree left = question_tree.left();
	    	BinaryTree right = question_tree.right();

			//If we reach leaf node, print out program's response to user's input to survey and end
	    	if (left.empty() && right.empty())
	    	{
	    		std::cout << question_tree.question() << std::endl;
	    		done = true;
	    	}
			//If we have not reached a leaf node yet, ask questions and take in user input
	    	else
	    	{
	    		std::string response;
				//Print question in node of tree to user and take in user's response to it
	    		std::cout << std::endl << question_tree.question() << " (y/n): ";
	    		std::cin >> response;

				//Input validation for user's response to question
	    		while (response != "y" && response != "n" && response != "Y" && response != "N")
				{
					std::cout << "Invalid input, please only enter (y/n): ";
					std::cin >> response;
				}

				//If user says yes to question, go to left subtree
	    		if (response == "y" || response == "Y")
	    		{
	    			question_tree = left;
					out << "," << response;
	    		}
				//If user says no to question, go to right subtree
	    		else
	    		{
	    			question_tree = right;
					out << "," << response;
	    		}         
	    	}
	    }
		out << std::endl;

		//Delete the tree 
		question_tree.deallocateTree(pointer);
    }
}