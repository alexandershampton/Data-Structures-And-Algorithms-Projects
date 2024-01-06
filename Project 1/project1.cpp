// Alexander Shampton
// Project 1
// This file simulates the rolling of dice a number of times as determined by the user

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// main() simulates a dice roll the number of times the user inputs
int main()
{
    // Local variables
    int arrayOfRolls[11] = {0}; // creating empty array simulating the number combination of two dice rolls
    int input;                  // var for user input

    cout << "How many rolls? ";
    cin >> input; // user's input for number of rolls
    cout << "Simulating " << input << " rolls..." << endl;
    cout << "Results:" << endl;
    srand(time(nullptr)); // seeds random with time for more random outcome

    // Loops the number of times the user inputed, rolls the dice randomly, and puts the result in an array
    for (int i = 0; i < input; i++)
    {
        int die1 = (rand() % 6) + 1;     // random 1st die roll
        int die2 = (rand() % 6) + 1;     // random 2nd die roll
        int diceRoll = die1 + die2;      // combines the two die rolls
        arrayOfRolls[diceRoll - 2] += 1; // adds 1 to the index (number rolled - 2), for the number rolled
    }

    // Loops through the array and outputs every combination of dice rolls
    // with the number of times the combination was rolled
    for (int i = 0; i < int(sizeof(arrayOfRolls) / sizeof(int)); i++)
    {
        cout << i + 2 << " was rolled " << arrayOfRolls[i] << " times " << endl; 
    }
    return 0;
}
