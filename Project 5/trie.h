// Alexander Shampton
// Project 5
// Header file  

#pragma once
#include <iostream>
#include <vector>
#include "TrieNode.h"
using namespace std;

class Trie{

	public:
		// CONSTRUCTORS for the Trie class:

	    /// @brief constructor for Trie 
		Trie();
		
		/// @brief Creates a (deep) copy of the Trie. 
		/// @param s Trie to be copied
		Trie(Trie& s);

		/// @brief clears the Trie 
		~Trie();

		/// @brief clears the Trie
		/// @param currentNode node to be deleted
        void clear(TrieNode* currentNode);

		/// @brief copies all the nodes in the Trie
		/// @param currentNode node that copies
		/// @param nodeToCopy node that is copied
		void copy(TrieNode* currentNode, TrieNode* nodeToCopy);

		/// @brief Creates a (deep) copy of the Trie.
		/// @param s The trie to be copied
		/// @return Returns the copied trie
		Trie& operator=(const Trie& s); 

		/// @brief inserts a string into the trie
		/// @param str the string to be inserted into the trie
		/// @returns true if the string can be inserted and false if the string cannot be inserted 
        bool insert(string str);

		/// @brief returns the number of words in the trie
        int count();

		/// @brief returns the number of nodes in the trie
        int getSize();

		/// @brief finds a string in the trie
		/// @returns true if the string is inside the trie and false if the string is not inside the trie
        bool find(string str); 

		/// @brief recursive function that returns the number of words that starts with the prefix passed
		/// @param count keeps track of the number of words that have the prefix
		/// @param currentNode node that is currently being pointed to
		/// @return 
		int completeCountHelper(int& count, TrieNode* currentNode);

		/// @brief returns the number of words that starts with the prefix passed
		/// @param str the prefix that wants searched
		/// @return returns the number of words that starts with the prefix passed
        int completeCount(string str); 
		
		/// @brief a recursive method that computes a vector of words starting with the prefix passed
		/// @param str the prefix that wants searched
		/// @param stringVector the vector that has words pushed onto it
		/// @param currentNode the node currently being pointed to
		void completeHelper(string str, vector<string>& stringVector, TrieNode* currentNode);

		/// @brief returns a vector of words starting with the prefix passed
		/// @param str the prefix that wants searched
		/// @return a vector of words starting with the prefix passed
        vector<string> complete(string str);
	private:
		TrieNode* root = new TrieNode(); //Root node
		int size = 0;
        int wordCount = 0;
};