// Alexander Shampton
// Project 5

#include <iostream>
#include <fstream> 
#include <string>
#include <cstring>
#include "trie.h"

int main()
{
    Trie trie;

    ifstream fileIn("wordlist_windows.txt"); //The file being read
    vector<string> wordlist;

    //If file is good, then the words get pushed into a word list
    if (fileIn.good())
    {
        string word;
        while (!fileIn.eof())
        {
            fileIn >> word; 
            wordlist.push_back(word); 
        }
    }
    else {
        cerr << "Couldn't open file!" << endl; // cerr goes to the error output which is usually just stdout
    }

    //inserts the words into the trie
    for (auto word : wordlist)
    {
        trie.insert(word);
    }

    string input; //user input for string
    string answerInput; //user input for continuing

    //loops through input until user input EXIT
    while(input != "!")
    {
        cout << "\nPlease enter a word prefix (or enter ! to exit the program): ";
        cin >> input;

        if(input != "!")
        {
            int count = trie.completeCount(input); //number of words beginning with the prefix in the trie

            //outputs if user wants to see completions if there are words beginning with the prefix
            if(count != 0){
                cout << "\nThere are " << count << " completions for the prefix '" << input << "'. Show completions? (Yes/No): ";
                cin >> answerInput;
            }else{
                cout << "There are no completions for the prefix '" << input << "' " << endl;
            }

            //outputs the completions if the user wants them to be outputted
            if((answerInput == "yes" || answerInput == "Yes" || answerInput == "YES") && count>0){
                cout << "Completions\n-----------" << endl;
                vector<string> vec = trie.complete(input); //vector of words with prefix

                //outputs the vector strings
                for (vector<string>::iterator it = vec.begin(); it != vec.end(); ++it) {	
                    cout << *it << endl;
                }

            }else{
                cout << "Ok, Completions will not be shown" << endl;
            }
        }
        else //if input == ! leave program
        {
            cout << "Exiting..." << endl;
            break;
        }

    }
 
    return(0);
}