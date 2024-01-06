// Alexander Shampton
// Project 4
// Header file 
#pragma once
#include <iostream>
#include <exception>
#include <vector>
#include <map>
#include "avltreenode.h"

using namespace std;

class AVLTree
{
	public:
		// CONSTRUCTORS for the AVLTree class:

	    /// @brief constructor for AVLtree 
		AVLTree();
		
		// @brief Creates a (deep) copy of the AVLTree. 
		// @param s AVLTree to be copied
		AVLTree(AVLTree& s);

		/// @brief clears the AVLtree 
		~AVLTree();

	    /// @brief clears the AVLtree 
	    /// @param current the node to be cleared
		void clear(AVLTreeNode*& current);

	    /// @brief copy's all nodes values and keys from an AVLTree
	    /// @param newTreeNode the node that copys
	    /// @param oldTreeNode the node that gets copied
	    /// @param newTreeNodeParent the parent node that gets set
		void nodeCopy(AVLTreeNode*& newTreeNode, AVLTreeNode*& oldTreeNode, AVLTreeNode*& newTreeNodeParent);

		/// @brief The current AVLTree is released and replaced by a (deep) copy of 
		/// AVLTree s. A reference to the copied AVLTree is returned.
		/// @param s the AVLTree to be copied
		/// @return *this with nodes from s copied into
		AVLTree& operator=(AVLTree& s);


		/// @brief inserts a node into the AVLTree and checks if node can be inserted
	    /// @param key the key of the node
	    /// @param value the value of the node
	    /// @return the true if the key/value pair can be inserted, or false if they cannot be inserted
		bool insert(int key, string value);

		/// @brief recursive helper function that inserts a node into the AVLTree
		/// @param current the node currently being used
		/// @param parentNode the current node's parent
	    /// @param key the key of the node
	    /// @param value the value of the node
	    /// @return the true if the key/value pair can be inserted, or false if they cannot be inserted
		bool insertHelper(AVLTreeNode*& current, AVLTreeNode*& parentNode, int key, string value);

		/// @brief rotates the problemNode left
		/// @param problemNode the node that is not balanced
    	void leftRotation(AVLTreeNode* problemNode);

		/// @brief rotates the problemNode's child right then rotates the problem node left
		/// @param problemNode the node that is not balanced
		void doubleLeftRotation(AVLTreeNode* problemNode);

		/// @brief rotates the problemNode right
		/// @param problemNode the node that is not balanced
		void rightRotation(AVLTreeNode* problemNode);

		/// @brief rotates the problemNode's child left then rotates the problem node right
		/// @param problemNode the node that is not balanced
		void doubleRightRotation(AVLTreeNode* problemNode);

		/// @brief calculates the balance of a node
		/// @param currentNode the node that has it's balance calculated
		void calculateBalance(AVLTreeNode* currentNode);

		/// @brief calculates the height of every node in the AVLTree 
	    /// @param currentNode the node being used currently 
	    /// @param leftHeight the height of the left side of the node
	    /// @param currentNode the height of the right side of the node
	    /// @return the height of the nodes
		void calculateHeight(AVLTreeNode* currentNode);

		/// @brief calculates the height of every node in the AVLTree 
	    /// @return the height of the tree
		int getHeight();

		/// @brief gets the size of the AVLTree
	    /// @return the size of the AVLtree
		int getSize();

		/// @brief helper method that outputs the AVLTree recursively
		/// @param os the output stream
		/// @param me the AVLTree
		/// @param currentNode the node that is currently in use
		/// @param depth how deep a node is
		friend ostream& outputHelper(ostream& os, const AVLTree& me,  AVLTreeNode*& currentNode, int depth);

		/// @brief outputs the AVLTree 
		/// @param os the output stream
		/// @param me the AVLTree
		friend ostream& operator<<(ostream& os, const AVLTree& me);


		/// @brief recursive helper function that finds a key and string that corresponds to one on the AVLTree 
		/// @param current the node currently being used
	    /// @param key the key of the node
	    /// @param value the value of the node
	    /// @return the true if the key/value pair are located, or false if not located
		bool findHelper(AVLTreeNode*& currentNode, int key, string& value);


		/// @brief finds a key and string that corresponds to one on the AVLTree 
	    /// @param key the key of the node
	    /// @param value the value of the node
	    /// @return the true if the key/value pair are located, or false if not located
		bool find(int key, string& value);

		/// @brief helper method that finds a range of nodes between two keys recursively
		/// @param lowkey the lowest key to be checked
		/// @param highkey the highest key to be checked
		/// @param currentNode the node currently being used
		/// @param rangeVector the vector that holds the nodes between the lowkey and high key
		vector<string> findRangeHelper(int lowkey, int highkey, AVLTreeNode* currentNode, vector<string>& rangeVector);

		/// @brief finds a range of nodes between two keys
		/// @param lowkey the lowest key to be checked
		/// @param highkey the highest key to be checked
		vector<string> findRange(int lowkey, int highkey); 

	private:
		AVLTreeNode* root; //Root node
		int size; //Size of the tree
};
