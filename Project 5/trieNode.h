// Alexander Shampton
// Project 5
// Header file  

#include <iostream>
using namespace std;
#define ARRAYSIZE 27 //size of array

class TrieNode {
	public:
		TrieNode* children[ARRAYSIZE]; //character nodes

        TrieNode()
		{
            //creates character nodes
            for(int i = 0; i<ARRAYSIZE; i++){
                children[i] = nullptr; 
            }
        };

		~TrieNode() 
        {
            
        };

	};