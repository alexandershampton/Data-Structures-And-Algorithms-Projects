// Alexander Shampton
// Project 2
// This file defines the methods of a Character 

#include "character.h"
#include <iostream>

using namespace std;

Character::Character(): name(), role(), hp(), ab(), db(), ac()
{
}

//Character constructor
Character::Character(const string newName, const string newRole, const int newHP, const int newAB, const int newDB, const int newAC):
    name(newName),
    role(newRole),
    hp(newHP),
    ab(newAB),
    db(newDB),
    ac(newAC)
{
}    
    //This method makes a Character attack another character based off of random die rolls
    void Character::attack(Character &otherCharacter)
    {

        cout << name << " attacks!" << endl;
        int attackRoll = ((rand() % 20) + 1); //Random roll from 20
        int attackWithBonus = attackRoll + ab;
        if (otherCharacter.ac<=(attackWithBonus)){

            cout << "Attack roll: " << attackRoll << " + " << ab << " = " << attackWithBonus << " --> HIT!" << endl;
            int damageRoll = ((rand() % 10) + 1); //Random damage amount 1-10
            int damageWithBonus = damageRoll + db; //Random damage amount plus the attacking character's damage bonus

            cout << "Damage: " << damageRoll << " + " << db <<  " = " <<  damageWithBonus << endl;

            otherCharacter.damage(damageWithBonus); //Subtracting the attack damage + damage bonus from recieving character HP

            cout << otherCharacter.getName() << " has " << otherCharacter.getHealth() << " hit points remaining\n" << endl;
        }
        else{
            cout << "Attack roll: " << attackRoll << " + " << ab << " = " << attackWithBonus << " --> MISS!\n" << endl;
        }
    }

    //This method subtracts the damage done to the Character's HP 
    void Character::damage(int amount){
        if (hp-amount>=0){
            hp -= amount;

        }else{
            hp = 0;
        }
    }

    //Returns the health of the Character
    int Character::getHealth() const{
        return(hp);
    }

    //Returns the name of the Character
    string Character::getName() const{
        return(name);
    }

    //Returns the role of the Character
    string Character:: getRole() const{
        return(role);
    } 

    //Outputs the character to a ostream
    void Character::print(ostream& os)
    {
        os << "\nCharacter summary\n-----------------" << endl;
        os << getName() << " the " << getRole() << endl;
        os << "HP: " << getHealth() << endl;
        os << "AB: " << ab << endl;
        os << "DB: " << db << endl;
        os << "AC: " << ac << "\n\n";
    }