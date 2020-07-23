#ifndef ROOM_H
#define ROOM_H

#include<map>
#include<string>
#include<vector>
#include "item.h"

using namespace std;

class Room
{
public:
    Room(string name);
    string getName();
    string getItems();
    void setExits(Room *north, Room *east, Room *south, Room *west);
    Room *getExit(string direction);
    void addItem(Item *item);
    Item *takeItem(string name);
    void setLock(Item* key);
    Item* getLock();

private:
    string name;
    Item* key;
    map<string, Room *> exits;
    vector<Item*> items;
};

#endif // ROOM_H
