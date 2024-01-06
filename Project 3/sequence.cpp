// Alexander Shampton
// Project 3
// This file defines the methods of a Sequence
#include "sequence.h"

//Creates the sequence with a size determined by input
Sequence::Sequence(size_type sz): numElts(sz)
{
    head = new SequenceNode(); //Creates new sequence node for head
    SequenceNode* currentNode = head;
    int size = sz; //Sets sz to int so it can be maniputlated

    //Loops the amount the size is -1
    for(int i = 0; i<size-1; i++)
    {
        //Creates new sequence node for the next node
        //Sets the current node to the next node
        //and sets previous node to the previous node
        currentNode->next = new SequenceNode();
        SequenceNode* previousNode = currentNode;
        currentNode = currentNode->next;
        currentNode->prev = previousNode;
    }

    //Sets the tail to the current node
    //because current node is pointing at the end
    //Tail's next is set to null pointer
    tail = currentNode;
    currentNode->next = nullptr;
}

//This method replaces a list with a deep copy of another list
Sequence::Sequence(const Sequence& s)
{
    //Makes sure the list is empty by setting head and tail to nullptr
    //And setting the number of element to 0
    head = nullptr;
    tail = nullptr;
    numElts = 0;

    //Checks if the list being copied is empty or not
    if (s.head != nullptr)
    {
        SequenceNode* nodeToCopy = s.head;

        //Loops through every node in the list being copied
        //and adds copies element to the copied list
        //until the copied list's node's next is nullptr
        while (nodeToCopy != nullptr)
        {
            push_back(nodeToCopy->elt);
            nodeToCopy = nodeToCopy->next;
        }
    }
}

//This method deletes the list and frees any memory associated
Sequence::~Sequence()
{
    //Clears the list
    clear();
}

//This method replaces a list with a deep copy of another list
Sequence& Sequence::operator=(const Sequence& s)
{
    //Clears the current list
    clear();

    //Checks if the list being copied is empty or not
    if (s.head != nullptr)
    {
        SequenceNode* nodeToCopy = s.head;

        //Loops through every node in the list being copied
        //and adds copies element to the copied list
        //until the copied list's node's next is nullptr
        while (nodeToCopy != nullptr)
        {
            push_back(nodeToCopy->elt);
            nodeToCopy = nodeToCopy->next;
        }

    }
    //Returns the copied list
    return *this;
}

//This method either returns the element at the position or sets the element at the position
Sequence::value_type& Sequence::operator[](size_type position)
{
    //Sets size type variables to integers so they can be manipulated with integers
    int positionInt = position;
    int numEltsInt = numElts;

    //Checks if the postion inputed is within the bounds of the list
    if(positionInt>=0 && positionInt<=(numEltsInt-1))
    {
        SequenceNode* currentNode = head;

        //Loops through the list until reaching the position
        for(int i = 0; i<positionInt; i++)
        {
            currentNode = currentNode->next;
        }

        //Returns the element at position inputed
        return(currentNode->elt);

    }

    //Throws exception if the position is out of the bounds of the list
    else{
        throw exception();
    }
}

//adds an element to the end of the list
void Sequence::push_back(const value_type& value)
{
    //If the list is not empty
    //The tail's next is set to a new node with a value
    //The tail is set to it's next 
    //The tail's previous is set to the previous tail
    //The tail's next is set to nullptr
    if(numElts!=0){
        SequenceNode* currentNode = tail;
        currentNode->next = new SequenceNode(value);
        tail = currentNode->next;
        tail->prev = currentNode;
        tail->next = nullptr;

    //If the list is empty
    //The node inserted is the new tail and head
    }else{
        head = new SequenceNode(value);
        head->next = nullptr;
        tail = head;
    }

    numElts+=1; //Increments the size of the list by 1
}

//Removes the last Sequence node on the list, 
//if tail = head then the head and tail are deleted and set to nullptr
void Sequence::pop_back()
{
    if(numElts>0){
        SequenceNode* nodeToDelete = tail;

        //If previous node is not nullptr
        //The tail is deleted and set to its previous node
        if(nodeToDelete->prev != nullptr){
            SequenceNode* newTail = nodeToDelete->prev;
            delete nodeToDelete;
            tail = newTail;
            tail->next = nullptr;

        //Checks if previous node is null pointer
        //If it is, the node needed removing is the head/tail
        //And they need set to nullptr to make empty list
        }else{
            delete nodeToDelete;
            tail = nullptr;
            head = nullptr;
        }

        numElts -=1; //Subtracts total number of elements by one
    
    //Throws exception if list is empty
    }else{
        throw exception();
    }
}

//Inserts a value into the list at a position and pushes other elements to the right
void Sequence::insert(size_type position, value_type value)
{   
    //Sets size type variables to integers so they can be manipulated with integers
    int positionInt = position;  
    int numEltsInt = numElts; 

    //Checks if the insertion is within the bounds of the list
    if(positionInt>=0 && positionInt<numEltsInt){
            SequenceNode* currentNode = head;

            //Loops through the nodes until reaching the insertion position
            for(int i = 0; i<positionInt; i++)
            {
                currentNode = currentNode->next;
            }

            //If inserting at 0, the head needs reset to the first node
            if(positionInt == 0) 
            { 
                currentNode->prev = new SequenceNode(value);
                SequenceNode* newHead = currentNode->prev; //Node that sets the head
                newHead->next = currentNode;
                head = newHead;

            //Inserting anywhere else moves nodes to the right
            }else{ 
                SequenceNode* previousNode = currentNode->prev;
                previousNode->next = new SequenceNode(value);
                previousNode = previousNode->next;
                previousNode->next = currentNode;
                currentNode->prev = previousNode;
            }

            numElts +=1; //adds one to the number of elements

        //Throws exception if the position is out of the bounds of the list
        }else{
            throw exception();
        }
}

//Returns the head's element
const Sequence::value_type& Sequence::front() const
{   
    //Returns the head's element
    if(numElts>0) 
    {
        return(head->elt);
    }

    //If the list is empty an exception will be thrown
    else { 
        throw exception();
    }
    
}

//Returns the tail's element
const Sequence::value_type& Sequence::back() const
{
    //Returns's the tail's element
    if(numElts>0)
    {
        return(tail->elt);
    }

    //Throws exception if the list is empty
    else{
        throw exception();
    }
}

//Checks if the list is empty, returns 0 if it is not empty
//Returns 1 if empty
bool Sequence::empty() const
{
    if(numElts != 0){
        return(false);
    }
    return true;
}

//Returns the size of the list
Sequence::size_type Sequence::size() const
{
    return numElts;
}

//Clears the list and sets the head and tail to null ptr
void Sequence::clear()
{
    //Only clears list if the head is not == to nullptr
    if (head != nullptr)
        {
        SequenceNode* nodeToDelete = head;

        //Loops through entire list and remove each node until the node's next is nullptr
        while (nodeToDelete != nullptr)
        {
            SequenceNode* nextNodeToDelete = nodeToDelete->next;
            delete nodeToDelete;
            nodeToDelete = nextNodeToDelete;
        }

        //Sets head and tail to nullptr and resets the size
        head = nullptr;
        tail = nullptr;
        numElts = 0;
    }

}

//This method erases nodes at a starting postion plus the number inputed
void Sequence::erase(size_type position, size_type count)
{
    //Sets size type variables to integers so they can be manipulated with integers
    int positionInt = position;  
    int countInt = count;
    int numEltsInt = numElts; 

    //Checks if deletion is in the bounds of the list
    if(positionInt>=0 && ((positionInt+countInt-1))<numEltsInt){
            SequenceNode* currentNode = head;

            //Loops through list until reaching the position starting deletion
            for(int i = 0; i<positionInt; i++)
            {
                currentNode = currentNode->next;
            }

            //Checks if the deletion point does not start at 0
            if(positionInt != 0)
            {
                SequenceNode* nodeBeforeDeletion = currentNode->prev; //Node before deletion starts

                //Loops through list and deletes the current node until it reaches the deletion end point
                for(int i = 0; i < countInt; i++)
                {
                SequenceNode* nodeToBeDeleted = currentNode;

                //Checks if to be deleted node is not the tail 
                //Sets node before deletion's next to the current node's next
                //Deletes the current node and sets the current node to the node before deletion's next
                //Sets the current node's previous node to the node before deletion node
                if(nodeToBeDeleted->next != nullptr) 
                {
                    nodeBeforeDeletion->next = nodeToBeDeleted->next;
                    delete nodeToBeDeleted;
                    currentNode = nodeBeforeDeletion->next;
                    currentNode->prev = nodeBeforeDeletion;

                //Deletes the current node and sets tail since the next node is nullptr
                }else{ 
                    delete nodeToBeDeleted;
                    tail = nodeBeforeDeletion;
                    tail->next = nullptr;
                }

                numElts -=1; //Decrements the size of the list by 1
            }

        //If deletion starts at element 0 then the process starts at the head
        }else{

            //Loops through list and deletes the current node until it reaches the deletion end point
            for(int i = 0; i < countInt; i++)
                {
                SequenceNode* nodeToBeDeleted = currentNode;

                //Checks it the node needing to be deleted is not at the tail
                //Deletes the current node and sets the current node to the next node
                //Sets the head to the current node after deletion since deletion starts at the head
                //Sets previous node to null pointer since the current node is at the head
                if(nodeToBeDeleted->next != nullptr)
                {
                    SequenceNode* nodeAfterDeletion = nodeToBeDeleted->next;
                    delete nodeToBeDeleted;
                    currentNode = nodeAfterDeletion;
                    currentNode->prev = nullptr;
                    head = currentNode;

                //If the whole list gets deleted then the head and tail needs set to nullptr
                }else{
                    delete nodeToBeDeleted;
                    head = nullptr;
                    tail = nullptr;
                }

                numElts -=1; //Decrements the number of elements by 1
            }
        }

    //Throws exception if deletion is in the bounds of the list
    }else{
        throw exception();

    }  
}

//Returns an output stream of the elements in the linked list
ostream& operator<<(ostream& os, const Sequence& s)
{
    Sequence::SequenceNode *currentNode = s.head;

    os << "<"; //Formats the list

    //Loops through the entire list and saves each element in os
    while (currentNode != nullptr){
        os << currentNode->elt;
        if(currentNode->next != nullptr){
            os << ", ";
        }
        currentNode = currentNode->next;
    }

    os << ">"; //Ends format for the list

    return os;
}
