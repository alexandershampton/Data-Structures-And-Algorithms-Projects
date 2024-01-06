// Alexander Shampton
// Project 2
// This file has the user create two character's and make them fight until one of them dies

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "character.h"

using namespace std;

//This functions asks for character data, creates a character, and returns a character
Character characterCreator(){

    //Character data variables
    string characterName; //the character's name
    string characterRole; //the character's role
    int characterHP; //the character's health, if it reaches 0 or below, the character dies
    int characterAttBonus; //value added to character's attack roll to see if an attack hits
    int characterDamBonus; //value added to a character's damage roll to damage the other character
    int characterArmorClass; //value for how hard it is to hit

    //Input for character data
    cin >> characterName; 
    cout << "\n" << characterName << "'s role? " << endl;
    cin >> characterRole; 
    cout << "\n" << characterName << " the " << characterRole << "'s hit points? " << endl;
    cin >> characterHP; 
    cout << "\n" << characterName << " the " << characterRole << "'s attack bonus? " << endl;
    cin >> characterAttBonus; 
    cout << "\n" << characterName << " the " << characterRole << "'s damage bonus? " << endl;
    cin >> characterDamBonus; 
    cout << "\n" << characterName << " the " << characterRole << "'s armor class? " << endl;
    cin >> characterArmorClass; 

    //Creates Character
    Character character(characterName, characterRole, characterHP, characterAttBonus, characterDamBonus, characterArmorClass);

    character.print(cout); //prints the character's stats

    return(character);
}

// main() creates character's and simulates them fighting
int main()
{
    cout << "First character name? " << endl;
    Character character1 = characterCreator(); //Creates character1

    cout << "Second character name? " << endl;
    Character character2 = characterCreator(); //Creates character2

    cout << "Simulated Combat:" << endl;
    srand(time (nullptr)); //seeds time into rand

    //Loop for combat until a character's HP reaches 0 or below 0
    while (character1.getHealth()>0 && character2.getHealth()>0){
        character1.attack(character2);
        if (character2.getHealth()>0){
            character2.attack(character1);
        }
    }

    //Conditionals that check which character wins by checking HP
    if (character1.getHealth() == 0){
        cout << character2.getName() << " wins!" << endl;
    }else{
        cout <<  character1.getName() << " wins!" << endl;

    }
    return 0;
}
