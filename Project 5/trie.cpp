// Alexander Shampton
// Project 5
// This file defines the methods of an trie

#include "trie.h"

//this method is the trie Constructor
Trie::Trie()
{        
}

//This method creates a deep copy of a trie
Trie::Trie(Trie& s)
{
    root = new TrieNode(); //sets root to a new node
    size = s.size;
    wordCount = s.wordCount;
    copy(root, s.root); //creates deep copies of each node
}

//this method is the trie destructor which calls clear
Trie::~Trie()
{
    clear(root); //clears each node in trie
    root = nullptr; //sets root to nullptr
}

//This method creates deep copies of a node
void Trie::copy(TrieNode* currentNode, TrieNode* nodeToCopy)
{
    //loops through the children array
    for(int i = 0; i<ARRAYSIZE; i++)
    {
        //Checks if the current child node is not null ptr
        //if so, the method is called again to check its children
        if(nodeToCopy->children[i])
        {
            currentNode->children[i] = new TrieNode();
            copy(currentNode->children[i], nodeToCopy->children[i]);
        }
    }
}

//this method creates a deep copy of a trie
Trie& Trie::operator=(const Trie& s)
{
    clear(root); //clears the root
    root = nullptr; //sets root to nullptr
    root = new TrieNode(); //sets root to new node
    size = s.size;
    wordCount = s.wordCount;
    copy(root, s.root); //creates deep copies of each node
    return(*this); //returns the trie
}

//this method clears the trie recursively
void Trie::clear(TrieNode* currentNode)
{
    //loops through the children array
    for(int i = 0; i<ARRAYSIZE; i++){
        //Checks if the current child node is not null ptr
        //if so, the method is called again to check its children
        if(currentNode->children[i]){
            clear(currentNode->children[i]);
        }else{
            delete currentNode->children[i]; //deletes the child node if it does not have children
            currentNode->children[i] = nullptr; //sets node to nullptr if trie is used again
        }
    }
    delete currentNode; //deletes the currentNode after deleting its children
    currentNode = nullptr; //sets node to nullptr if trie is used again
}

//inserts a "string" into the trie
//returns true/false if the word can be inserted
bool Trie::insert(string str)
{
    TrieNode* currentNode = root; //sets currentNode to root
    const int stringLength = str.length(); //finds length of the string
    bool truth = false; //boolean that signifies whether the word can be inserted

    //loops through each character of the string
    for(int i = 0; i<stringLength; i++)
    {
        char strChar = str[i]; //the character in position i
        int indexNumber = strChar - 'a'; //the index where a new node will be created/checked

        //Checks if the character in the index is occupied, if not,
        //A new node for that character is created
        if(!currentNode->children[indexNumber])
        {
            currentNode->children[indexNumber] = new TrieNode(); //creates new node for character
            size += 1;
            truth = true; //Sets the boolean to true since the word could be inserted
        }

        currentNode = currentNode->children[indexNumber]; //Sets the current node to the character's node
    }

    if(truth == true)
    {
        wordCount += 1;
        currentNode->children[ARRAYSIZE -1] = new TrieNode(); //Sets the end word character
    }

    return(truth);
}

//This method finds a string in the trie
//If the string is found, returns true
//else returns false
bool Trie::find(string str)
{
    TrieNode* currentNode = root; //sets currentNode to root
    const int stringLength = str.length(); //finds length of the string

    //loops through the prefix
    for(int i = 0; i<stringLength; i++)
    {
        char strChar = str[i];
        int indexNumber = strChar - 'a'; //index for character being entered

        //Checks if the character in the index is occupied, if not return false
        if(!currentNode->children[indexNumber])
        {
            return(false);
        }

        currentNode = currentNode->children[indexNumber]; //Sets the current node to the character's node
    }

    //Checks if the word is in the trie by checking if there is an end character in the node
    if(currentNode->children[ARRAYSIZE - 1]){
        return(true);
    }else{
        return(false);
    }

}

//This recursive method returns the number of words after a string prefix
int Trie::completeCountHelper(int& count, TrieNode* currentNode)
{
    //loops through the whole trie
    for(int i = 0; i < ARRAYSIZE; i++)
    {
        //checks if the word consisting of all the previous pointer is in the trie
        if(currentNode->children[ARRAYSIZE - 1] && (i == 0))
        {
            count += 1;
        }

        //checks if the current pointer has children nodes
        //if so the children nodes are checked by calling the function again
        //with the currentNode's ith child
        if(currentNode->children[i])
        {
            completeCountHelper(count, currentNode->children[i]);
        }

    }

    return(count);
}

//This method returns the number of words after a string prefix
int Trie::completeCount(string str)
{
    TrieNode* currentNode = root; //sets currentNode to root
    const int stringLength = str.length(); //finds length of the string

    //loops through each character of the string and the node will point to the character
    //at the end of the string
    for(int i = 0; i<stringLength; i++)
    {
        char strChar = str[i]; //the character in position i
        int indexNumber = strChar - 'a'; //the index where the character will be followed

        //Checks if the character in the index is occupied and points to that node
        if(currentNode->children[indexNumber]){
            currentNode = currentNode->children[indexNumber];
        }else{
            return(0);
        }
    }
    int count = 0;
    return(completeCountHelper(count, currentNode));
}

//This recursive method pushes the strings, from the trie that has the prefix of the passed string
//into a vector
void Trie::completeHelper(string str, vector<string>& stringVector, TrieNode* currentNode)
{
    //loops through the array of each node
    for(int i = 0; i < ARRAYSIZE; i++)
    {
        //if the word is in the trie, by checking if the ending character is in the array,
        //the word gets pushed onto the vector
        if(currentNode->children[ARRAYSIZE - 1] && (i == 0))
        {
            stringVector.push_back(str);
        }

        //checks if the current pointer has children nodes
        //if so the children nodes are checked by calling the function again
        //with the currentNode's ith child        
        if(currentNode->children[i])
        {
            //adds the child's character to the string
            char character = 'a' + i;
            string stringToPush = str; 
            stringToPush += (character);

            completeHelper(stringToPush, stringVector, currentNode->children[i]); //recursive call
        }

    }
}

//This method returns a vector with strings with a prefix that is passed into the method
vector<string> Trie::complete(string str)
{
    TrieNode* currentNode = root; //sets currentNode to root
    const int stringLength = str.length(); //finds length of the string
    vector<string> stringVector;

    //loops through each character of the string and the node will point to the character
    //at the end of the string
    for(int i = 0; i<stringLength; i++)
    {
        char strChar = str[i]; //the character in position i
        int indexNumber = strChar - 'a'; //the index where the character will be followed

        //Checks if the character in the index is occupied and points to that node
        if(currentNode->children[indexNumber])
        {
            currentNode = currentNode->children[indexNumber];
        }else{
            return(stringVector);
        }

    }  

    completeHelper(str, stringVector, currentNode); //adds words with the prefix to the vector
    return(stringVector); //returns the vector

}

//This method returns the number of words in the trie
int Trie::count()
{
    return(wordCount);
}

//This method returns the number of nodes in the trie
 int Trie::getSize()
 {
    return(size);
 }