#include <iostream>
#include "character.h"

#include "eventmanager.h"
#include "keyitem.h"

Character::Character(string name)
{
	this->name  = name; // We need to use "this->" to differentiate between the "name" argument and the "name" from the class.
	health      = 100;
	stamina     = 100;
	currentRoom = nullptr;
}

string Character::getName()
{
	return name;
}

int Character::getHealth()
{
	return health;
}

int Character::getStamina()
{
	return stamina;
}

Room *Character::getCurrentRoom()
{
	return currentRoom;
}

void Character::setName(string name)
{
	this->name = name;
}

void Character::setHealth(int health)
{
	if (health <= 0) {
		health = 0;
		EventManager::getInstance().trigger("characterDeath", this);
	}

	this->health = health;
}

void Character::setStamina(int stamina)
{
	if (stamina <= 0) {
		stamina = 0;
		EventManager::getInstance().trigger("characterDeath", this);
	}

	this->stamina = stamina;
}

void Character::setCurrentRoom(Room *next)
{
	currentRoom = next;
}

void Character::addItem(Item *item)
{
	inventory.push_back(item);
}

Item* Character::takeItem(string name)
{
	if (inventory.size() < 1)
	{
		return NULL;
	}

	for (unsigned int i = 0; i < inventory.size(); i++)
	{
		string lowerItem = "";
		for (int c : inventory[i]->getName())
		{
			lowerItem += tolower(c);
		}

		if (lowerItem == name)
		{
			Item *item = inventory[i];
			inventory.erase(inventory.begin() + i);
			return item;
		}
	}
	return NULL;
}

bool Character::hasItem(Item *item)
{
	for (Item *thing : inventory)
	{
		if (thing == item)
		{
			return true;
		}
	}
	return false;
}

bool Character::hasKey(int lock_id)
{
	for (Item *thing : inventory)
	{
		if (thing->getType() == "Key")
		{
			KeyItem* key = (KeyItem*) thing;
			if (key->getLock() == lock_id)
			{
				return true;
			}
		}
	}
	return false;
}

/****************** 4. Unary operator overloading ******************/
void Character::operator--(int)
{
	this->stamina -= 1;
}

ostream& operator <<(ostream& out, const Character person)
{
	out << person.name << "-> HP: " << to_string(person.health) << " ST: " << to_string(person.stamina) << endl;
	out << "Inventory: ";
	if (person.inventory.size() != 0)
	{
		for (Item *item : person.inventory)
		{
			out << item->getName() << " ";
		}
	}
	else
	{
		out << "Empty";
	}
	
	return out;
}