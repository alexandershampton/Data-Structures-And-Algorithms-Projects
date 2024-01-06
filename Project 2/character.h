// Alexander Shampton
// Project 2
// Header file 

#include <string>
using namespace std;
//Declaration class Character
class Character
{
//Character private variables
private:
    string name;
    string role;
    int hp;
    int ab;
    int db;
    int ac;

//Character methods and constructor
public:
    Character();
    Character(const string newName, const string newRole, const int newHP, const int newAB, const int newDB, const int newAC);
    void print(ostream&) ;
    void attack(Character &otherCharacter) ;
    void damage(int amount) ;
    int getHealth() const;
    string getName() const;
    string getRole() const;
};