#include "room.h"
#include "game.h"

#include <iostream>

Room::Room(string name) :
    name(name)
{
    exits["north"] = nullptr;
    exits["east"]  = nullptr;
    exits["south"] = nullptr;
    exits["west"]  = nullptr;
    key = NULL;
}

string Room::getName()
{
    return name;
}

string Room::getItems()
{
    string str = "";
    if (items.size() < 1)
    {
        return "No Items";
    }

    str += items[0]->getName();
    for (unsigned int i = 1; i < items.size(); i++)
    {
        str += ", " + items[i]->getName();
    }
    return str;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west)
{
    exits["north"] = north;
    exits["east"]  = east;
    exits["south"] = south;
    exits["west"]  = west;
}

Room *Room::getExit(string direction)
{
    return exits[direction];
}

void Room::addItem(Item *item)
{
    this->items.push_back(item);
}

Item* Room::takeItem(string name)
{   
    for (unsigned int i = 0; i < items.size(); i++)
    {
        string lowerItem = "";
        for (int c : items[i]->getName())
        {
            lowerItem += tolower(c);
        }

        if (lowerItem == name)
        {
            Item* item = items[i];
            items.erase(items.begin() + i);
            return item;
        }
    }
    return NULL;
}

void Room::setLock(Item* key)
{
    this->key = key;
}

Item* Room::getLock()
{
    return this->key;
}
