// Alexander Shampton
// Project 4
// Header file  

#include <iostream>
using namespace std;

class AVLTreeNode {
	public:
		AVLTreeNode* left; 
		AVLTreeNode* right; 
		AVLTreeNode* parent; 
		int key;
		string value;
		int height;
        int balance;

        AVLTreeNode(): left(nullptr), right(nullptr), parent(nullptr)
		{};

		AVLTreeNode(int newKey, string newValue): left(nullptr), right(nullptr), parent(nullptr), key(newKey), value(newValue), height(0), balance(0)
		{};

		~AVLTreeNode() {};

	};