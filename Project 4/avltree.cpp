// Alexander Shampton
// Project 4
// This file defines the methods of an AVLTree

#include "avltree.h"

//this method is the AVLTree Constructor
AVLTree::AVLTree()
{        
    //initially set to nullptr and 0
    root = nullptr;
    size = 0;
}

//this method is the AVLTree Copy Constructor
AVLTree::AVLTree(AVLTree& s)
{
    //clears tree before copying
    root = nullptr;
    size = 0;    

    //if there root is not nullptr, the size, root,
    //and all node values are copied
    if(s.root != nullptr){
        size = s.size;
        root = new AVLTreeNode(s.root->key,s.root->value);
        root->parent = nullptr;
        root->height = s.root->height;
        nodeCopy(root, s.root, root);
    }   
}

//this method is a destructor for avltree
AVLTree::~AVLTree()
{
    //clears the tree
    clear(root);
    root = nullptr;
    size = 0;
}

//recursive method for copying node keys and values
void AVLTree::nodeCopy(AVLTreeNode*& newTreeNode,  AVLTreeNode*& oldTreeNode, AVLTreeNode*& newTreeNodeParent)
{
    //checks if oldTreeNode is not null
    if(oldTreeNode){
        //checks if the oldTreeNode has a parent
        if(oldTreeNode->parent){
            //creates node and copies the values from the oldtreenode
            newTreeNode = new AVLTreeNode(oldTreeNode->key,oldTreeNode->value);
            newTreeNode->parent = newTreeNodeParent;
            newTreeNode->balance = oldTreeNode->balance;
            newTreeNode->height = oldTreeNode->height;
        }

        //checks if the oldTreeNode->right, if so
        //it recursively calls the function with the right of both nodes
        if(oldTreeNode->right){
            nodeCopy(newTreeNode->right, oldTreeNode->right, newTreeNode);
        }
        
        //checks if the oldTreeNode->left, if so
        //it recursively calls the function with the left of both nodes
        if(oldTreeNode->left){
            nodeCopy(newTreeNode->left, oldTreeNode->left, newTreeNode);
        }
    }
}

//this method copys a trees values into another tree
AVLTree& AVLTree::operator=(AVLTree& s)
{
    //Clears the current tree
    clear(root);
    root = nullptr;
    size = 0;

    //if there root is not nullptr, the size, root,
    //and all node values are copied
    if(s.root){
        size = s.size;
        root = new AVLTreeNode(s.root->key,s.root->value);
        root->parent = nullptr;
        root->height = s.root->height;
        nodeCopy(root, s.root, root);
    }
    // //Returns the copied list
    return *this;
}

//this method clears a tree
void AVLTree::clear(AVLTreeNode*& currentNode)
{
    //checks if the node is not nullptr
    if(currentNode){

        //checks if the currentNode->right, if so
        //it recursively calls the function with the right of current
        if(currentNode->right){
            clear(currentNode->right);
        }

        //checks if the currentNode->left, if so
        //it recursively calls the function with the left of current
        if(currentNode->left){
            clear(currentNode->left);
        }

        //once current has reached the leafnode, the node gets deleted
        if(currentNode){
            delete currentNode;
            currentNode = nullptr;
        }
    }
}

void AVLTree::calculateHeight(AVLTreeNode* currentNode)
{
        //tracks the left and right heights
        int leftHeight = 0;
        int rightHeight = 0;

        //checks if there is a currentNode->left, if so,
        // the left height is 1 and is incremented by the left node's height
        if(currentNode->left)
        {
            leftHeight = 1;
            leftHeight += currentNode->left->height;
        }
        
        //checks if there is a currentNode->right, if so,
        // the reight height is 1 and is incremented by the right node's height
        if(currentNode->right)
        {
            rightHeight = 1;
            rightHeight += currentNode->right->height;
        }

        //sets the currentNode's height by calcualting the max of the left and right height
        currentNode->height = max(leftHeight, rightHeight);
}

void AVLTree::calculateBalance(AVLTreeNode* currentNode)
{
    //rules for balancing
    if(currentNode->left && currentNode->right) {
        currentNode->balance = currentNode->left->height - currentNode->right->height;

    }else if(currentNode->left != nullptr){
        currentNode->balance = currentNode->left->height - (-1);

    }else if(currentNode->right != nullptr){
        currentNode->balance = -1 - currentNode->right->height;

    }else{
        currentNode->balance = -1 - (-1); //if there is not leftHeight or rightHeight
    }

    //Checks if node is balanced
    if(currentNode->balance == -2)
        {
            if(currentNode->right->balance == -1){
                leftRotation(currentNode); //does left rotation on node
            }else if(currentNode->right->balance == 1){
                doubleLeftRotation(currentNode); //does double left rotation on node
            }
        }

    //Checks if node is balanced
    else if(currentNode->balance == 2)
        {
            if(currentNode->left->balance == 1){
                rightRotation(currentNode); //does right rotation on node
            }else if(currentNode->left->balance == -1){
                doubleRightRotation(currentNode); //does right rotation on node
            }      
        }
}

//does left rotation on node
void AVLTree::leftRotation(AVLTreeNode* problemNode)
{

    AVLTreeNode* hookNode = problemNode->right; //hook node
    AVLTreeNode* problemNodeTemp = problemNode; //temporary node that equals the problem node

    //Checking if the hook has a left child node
    if(hookNode->left){
        problemNode->right = hookNode->left;
        problemNode->right->parent = problemNode;
    }else{
        problemNode->right = nullptr;
    }

    //Checks if the problem node is root
    if(problemNodeTemp == root){
        root = hookNode;
        hookNode->parent = nullptr;
    }else{
        //sets hook's parent to the problemNode's parent and sets the parent's right to the hooknode
        hookNode->parent = problemNodeTemp->parent; 
        if(hookNode->parent->right == problemNodeTemp){
            problemNodeTemp->parent->right = hookNode;
        }else{
            problemNodeTemp->parent->left = hookNode;
        }
    }
    
    problemNode->parent = hookNode; //make's the problem node's parent equal the hook node    

    hookNode->left = problemNode; //sets the problem node to the left child of hook node

    // //recalculates heights, balances
    calculateHeight(hookNode->left);
    calculateHeight(hookNode->right);
    calculateHeight(hookNode);
    calculateBalance(hookNode->left);
    calculateBalance(hookNode->right);
    calculateBalance(hookNode);
}

//does double left rotation on node
void AVLTree::doubleLeftRotation(AVLTreeNode* problemNode)
{
    //First right Rotation

    //creates the hook and problem node's child
    AVLTreeNode* problemNodeChild = problemNode->right;
    AVLTreeNode* hookNode = problemNode->right->left;

    //sets problemnode's right to the hook and sets the hook's parent to problemNode
    problemNode->right = hookNode;
    hookNode->parent = problemNode;

    //checks if hooknode has a child, if it does it gets moved to the left of the problem child node
    if(hookNode->right){
        problemNodeChild->left = hookNode->right;
        problemNodeChild->left->parent = problemNodeChild;
    }else{
        problemNodeChild->left = nullptr;
    }

    //sets the hooknode's right to the problemnode child and the problemnode's child's parent to hooknode
    hookNode->right = problemNodeChild;
    problemNodeChild->parent = hookNode;

    //Left Rotation

    //checks if the problem node has a parent
    //sets problem node's parent to hookNode's
    //and set's the parent's left to hookNode
    if(problemNode == root){
        hookNode->parent = nullptr;
        root = hookNode;
    }else{ 
        hookNode->parent = problemNode->parent;
        if(hookNode->parent->right == problemNode){
            hookNode->parent->right = hookNode;
        }else{
            hookNode->parent->left = hookNode;
        }
    }

    problemNode->parent = hookNode;

    //checks if hookNode has a child, if so,
    //problemNode's right is set to that child
    if(hookNode->left){
        problemNode->right = hookNode->left;
        problemNode->right->parent = problemNode;
    }else{
        problemNode->right = nullptr;
    }

    //sets hooknode's left to problemNode
    hookNode->left = problemNode;

    // //recalculates heights and balances
    calculateHeight(hookNode->left);
    calculateHeight(hookNode->right);
    calculateHeight(hookNode);
    calculateBalance(hookNode->left);
    calculateBalance(hookNode->right);
    calculateBalance(hookNode);
}

//does right rotation on node
void AVLTree::rightRotation(AVLTreeNode* problemNode)
{
    //sets up hook and problemnode
    AVLTreeNode* hookNode = problemNode->left;
    AVLTreeNode* problemNodeTemp = problemNode;

    //checks if hook node has a child, if so
    //the child is set to problemNodes left
    if(hookNode->right){
        problemNode->left = hookNode->right;
        problemNode->left->parent = problemNode;
    }else{
        problemNode->left = nullptr;
    }
    
    //sets the hook node's right to problem node
    hookNode->right = problemNode;

    //checks if problem node has a parent,if so
    //hookNode's parent is set to problem's parent
    //and the parent's left is set to hook node
    if(problemNodeTemp == root){
        root = hookNode;
        hookNode->parent = nullptr;
    }else{
        hookNode->parent = problemNodeTemp->parent;
        if(hookNode->parent->right == problemNodeTemp){
            hookNode->parent->right = hookNode;
        }else{
            hookNode->parent->left = hookNode;
        }
    }

    //sets problemNode's parent as hooknode
    problemNode->parent = hookNode;

    // //recalculates heights and balances
    calculateHeight(hookNode->left);
    calculateHeight(hookNode->right);
    calculateHeight(hookNode);
    calculateBalance(hookNode->left);
    calculateBalance(hookNode->right);
    calculateBalance(hookNode);    
}

//does double right rotation on node
void AVLTree::doubleRightRotation(AVLTreeNode* problemNode)
{

    //First Left Rotation

    //Sets up the problemNodeChild and hook node pointers
    AVLTreeNode* problemNodeChild = problemNode->left;
    AVLTreeNode* hookNode = problemNode->left->right;

    //moves hook node up
    problemNode->left = hookNode;
    hookNode->parent = problemNode;
    problemNodeChild->parent = hookNode;

    //checks if hookNode has left and if so it is set to 
    //problemNodeChild->right
    if(hookNode->left){
        problemNodeChild->right = hookNode->left;
        problemNodeChild->right->parent = problemNodeChild;
    }else{
        problemNodeChild->right = nullptr;
    }

    //sets hooknode's left to problemNodeChild
    hookNode->left = problemNodeChild;

    //Second Rotation

    //Checks if problemNode is root to see if problem node has a parent
    //if problemNode has a parent, hookNode's parent is set to it
    if(problemNode == root){
        hookNode->parent = nullptr;
        root = hookNode;
    }else{
        hookNode->parent = problemNode->parent;
        //checks which side hookNode is on
        if(hookNode->parent->right == problemNode){
            hookNode->parent->right = hookNode;
        }else{
            hookNode->parent->left = hookNode;
        }
    }

    //sets problemNode's parent to hookNode
    problemNode->parent = hookNode;

    //checks if hookNode has a right, if so
    //it is set to problem node's left
    if(hookNode->right){
        problemNode->left = hookNode->right;
        problemNode->left->parent = problemNode;
    }else{
        problemNode->left = nullptr;
    }

    hookNode->right = problemNode;

    //recalculates heights, and balances of moved nodes
    calculateHeight(hookNode->left);
    calculateHeight(hookNode->right);
    calculateHeight(hookNode);
    calculateBalance(hookNode->left);
    calculateBalance(hookNode->right);
    calculateBalance(hookNode);
}

//recursive helper method that inserts a key and value into a node and other pointers are ser 
bool AVLTree::insertHelper(AVLTreeNode*& currentNode, AVLTreeNode*& parentNode, int newKey, string newValue)
{
    bool truth;
    
    //checks if the node is nullptr so that the node can be inserted
    if (currentNode == nullptr)
    {
        currentNode = new AVLTreeNode(newKey,newValue); //creates new node with key and value
        size += 1; //adds to the size of the tree

        //checks if the node is not root so it set the parentnode
        if(currentNode->key != root->key){
            currentNode->parent = parentNode;
        }

        calculateHeight(currentNode); //calculates the height of the node
        calculateBalance(currentNode); //calculates balance of node
        truth = true;  //since the method sucessfully inserted, it returns true
        return truth;
    }

    //Checks if the inputted key is less than the currentNode's key
    else if (newKey < currentNode->key)
    {
        //recursively calls the function with currentNode->left since 
        //the inputted key is less than current's key
        truth = insertHelper(currentNode->left, currentNode, newKey, newValue); 

        calculateHeight(currentNode); //calculates height of node
        calculateBalance(currentNode); //calculates balance of node
    }
    else if (newKey > currentNode->key)
    {
        //recursively calls the function with currentNode->right since 
        //the inputted key is greater than current's key
        truth = insertHelper(currentNode->right, currentNode, newKey, newValue);
        calculateHeight(currentNode); //calculates height of node
        calculateBalance(currentNode); //calculates balance of node

    }else{
        truth = false; //since the method unsucessfully inserted, it returns false
        return truth;
    }
    return truth;
}

//inserts a key and value into a AVLTree
//returns true if key is inserted
//returns false if key is already in the tree
bool AVLTree::insert(int key, string value)
{
    return insertHelper(root, root, key, value);
}

//Returns the height of the tree
int AVLTree::getHeight()
{
    if(root){
          return(root->height);
    }else{
        return(0);
    }
}

//returns the size of the tree
int AVLTree::getSize()
{
    return(size);
}

//recursive method that finds a key in the tree
//returns true or false if the key/value are not in there
bool AVLTree::findHelper(AVLTreeNode*& currentNode, int key, string& value)
{
    //makes sure the node is not nullptr
    if (currentNode != nullptr)
    {

        //if the key is in the tree the function returns true
        if (key == currentNode->key) 
        {
            value = currentNode->value;
            return true;
        }

        //if the inputted key is less than the current key
        //the recursive call uses currentNode->left
        if (key < currentNode->key)
        {
            return(findHelper(currentNode->left, key, value));
        }

        //if the inputted key is more than the current key
        //the recursive call uses currentNode->right
        if (key > currentNode->key)
        {  
            return(findHelper(currentNode->right, key, value));
        }

    }
    //returns false if the key is not in the AVLTree
    return false;
}

//finds a key and value in a tree
//returns true or false if the key/value are not in there
bool AVLTree::find(int key, string& value)
{
    if(root){
        AVLTreeNode* currentNode = root;
        return findHelper(currentNode, key, value);    
    }
    else{
        return(false);
    }
}

//returns a vector with a range of nodes between lowkey and highkey
vector<string> AVLTree::findRangeHelper(int lowkey, int highkey, AVLTreeNode* currentNode, vector<string>& rangeVector)
{
    //checks if the currentNode's key is between the lowkey and highkey
    if(lowkey<=currentNode->key && highkey>=currentNode->key)
    {
        //checks if there is a left pointer, if so,
        //there is a recursive call on the function with currentNode->left
        if (currentNode->left)
        {
            findRangeHelper(lowkey,highkey, currentNode->left, rangeVector);
        } 
        
        //checks if the currentNode's key is between the lowkey and highkey
        //if it is, it gets pushed onto the vector
        if (lowkey<=currentNode->key && highkey>=currentNode->key)
        {
            rangeVector.push_back(currentNode->value);
        }

        //checks if there is a right pointer, if so,
        //there is a recursive call on the function with currentNode->right
        if (currentNode->right)
        {
            findRangeHelper(lowkey,highkey, currentNode->right, rangeVector);
        }

    }

    //checks if the low bound is greater than the current key
    else if(lowkey>currentNode->key)
    {
        //checks if there is a right pointer, if so,
        //there is a recursive call on the function with currentNode->right
        if (currentNode->right)
        {
            findRangeHelper(lowkey,highkey, currentNode->right, rangeVector);
        }
    }

    //checks if the highbound is less than the current key
    else if(highkey<currentNode->key)
    {
        //checks if there is a left pointer, if there is
        //there is a recursive call on the function with currentNode->left
        if(currentNode->left)
        {
            findRangeHelper(lowkey,highkey, currentNode->left, rangeVector);
        }
    }
    return(rangeVector); //returns the range of nodes in a vector
}

//returns a vector with a range of nodes between lowkey and highkey
vector<string> AVLTree::findRange(int lowkey, int highkey)
{
    vector<string> vectorRange;
    if(root){
        return(findRangeHelper(lowkey, highkey,root ,vectorRange));  
    }else{
        return(vectorRange);
    }
}

//A recursive helper function to output the tree
ostream& outputHelper(ostream& os, const AVLTree& me,  AVLTreeNode*& currentNode, int depth)
{
    //checks if currentNode->right, if so
    //it recursively calls the function with currentNode->right
    if(currentNode->right){
        outputHelper(os, me, currentNode->right, depth+1);
    }

    //loop for spaces before keys and values acoording to depth
    for(int i = 0; i < depth; i++)
        {
            os << "\t";
        }

    os << currentNode->key << ", " << currentNode->value << endl; //outputs the key and value of the node

    //checks if currentNode->left, if so
    //it recursively calls the function with currentNode->left
    if(currentNode->left){
        outputHelper(os, me, currentNode->left, depth+1);
    }

    return os;
}

//returns an output stream of the tree
ostream& operator<<(ostream& os, const AVLTree& me)
{
    //makes the currentnode the tree's root
    AVLTreeNode* currentNode = me.root;

    //checks if the currentnode is not null
    if(currentNode){
        outputHelper(os,me,currentNode, 0); //recursive outputstream function
    }
    return(os);
}
