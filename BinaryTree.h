#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <string>
#include <iostream>

class TreeNode
{
private:
	std::string question;
	TreeNode* left;
	TreeNode* right;
friend class BinaryTree;
public:
	TreeNode* get_left();
	TreeNode* get_right();
};

/*
	A binary tree in which each TreeNode has two children.
*/
class BinaryTree
{
public:
	/**
		Constructs an empty tree.
	*/
	BinaryTree();

	/**
		Constructs a tree with one TreeNode and no children.
		@param root_question the question for the root
	*/
	BinaryTree(std::string root_question);

	/**
		Constructs a binary tree.
		@param root_question the question for the root
		@param left the left subtree
		@param right the right subtree
	*/
	BinaryTree(std::string root_question, BinaryTree left, BinaryTree right);

	/**
		Returns the height of this tree.
		@return the height
	*/
	int height() const;

	/**
		Checks whether this tree is empty.
		@return true if this tree is empty
	*/
	bool empty() const;

	/**
		Gets the question at the root of this tree.
		@return the root question
	*/
	std::string question() const;

	/**
		Gets the left subtree of this tree.
		@return the left child of the root
	*/
	BinaryTree left() const;

	/**
		Gets the right subtree of this tree.
		@return the right child of the root
	*/
	BinaryTree right() const;

	/**
   		Deallocates the BinaryTree to free up memory by deleting every TreeNode in BinaryTree
   		This function uses post order traversal to delete TreeNodes
   		@param current the root pointer is passed through here
	*/
	void deallocateTree(TreeNode* current);

	/**
	 	Gets the root pointer of the BinaryTree.
		@return the root pointer of BinaryTree.
	*/
	TreeNode* get_root ();

private:
	/**
		Returns the height of the subtree whose root is the given TreeNode.
		@param n a TreeNode or nullptr
		@return the height of the subtree, or 0 if n is nullptr
	*/
	int height(const TreeNode* n) const;

	TreeNode* root;
};

void survey();

#endif