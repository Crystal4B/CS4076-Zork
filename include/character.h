#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "item.h"

using namespace std;

// No need to include room since we're only working with pointers.
// This is how we tell the compiler "there will be a room eventually".
// This is called a "forward declaration".
class Room;

class Character
{
public:
    Character(string name);

    string getName();
    int    getHealth();
    int    getStamina();
    Room  *getCurrentRoom();

    void setName(string name);
    void setHealth(int setHealth);
    void setStamina(int stamina);
    void setCurrentRoom(Room *next);

    void addItem(Item *item);
    Item* takeItem(string name);
    bool hasItem(Item *item);
    bool hasKey(int lock_id);

    void operator--(int);
	
	/***************** 6. Friends *****************/
    friend ostream& operator <<(ostream& outputStream, const Character person);


private:
    vector<Item*> inventory;
    string name;
    int health;
    int stamina;
    Room *currentRoom;
};

#endif // CHARACTER_H
