#include "game.h"

#include <ctime>
#include <iostream>

#include "eventmanager.h"
#include "room.h"
#include "usableitem.h"
#include "curseditem.h"
#include "keyitem.h"

#include "golistener.h"
#include "maplistener.h"
#include "infolistener.h"
#include "restartlistener.h"
#include "teleportlistener.h"
#include "exitlistener.h"
#include "takelistener.h"
#include "uselistener.h"
#include "characterdeathlistener.h"
#include "enterroomlistener.h"
#include "victorylistener.h"
#include "defeatlistener.h"
#include "charactercursedlistener.h"

Game::Game() :
	player("Hero")
{
	srand(time(nullptr));

	// Commands
	EventManager::getInstance().listen("go",        new GoListener(this));
	EventManager::getInstance().listen("map",       new MapListener(this));
	EventManager::getInstance().listen("info",      new InfoListener(this));
	EventManager::getInstance().listen("restart",   new RestartListener(this));
	EventManager::getInstance().listen("teleport",  new TeleportListener(this));
	EventManager::getInstance().listen("exit",      new ExitListener(this));
	EventManager::getInstance().listen("take",      new TakeListener(this));
	EventManager::getInstance().listen("use",       new UseListener(this));

	// State changes
	EventManager::getInstance().listen("characterDeath", new CharacterDeathListener(this));
	EventManager::getInstance().listen("enterRoom",      new EnterRoomListener(this));
	EventManager::getInstance().listen("victory",        new VictoryListener(this));
	EventManager::getInstance().listen("defeat",         new DefeatListener(this));
	EventManager::getInstance().listen("characterCursed",new CharacterCursedListener(this));

	rooms.push_back(new Room("A")); // 0
	rooms.push_back(new Room("B")); // 1
	rooms.push_back(new Room("C")); // 2
	rooms.push_back(new Room("D")); // 3
	rooms.push_back(new Room("E")); // 4
	rooms.push_back(new Room("F")); // 5
	rooms.push_back(new Room("G")); // 6
	rooms.push_back(new Room("H")); // 7
	rooms.push_back(new Room("I")); // 8
	rooms.push_back(new Room("J")); // 9

	//                 N         E         S         W
	rooms[0]->setExits(rooms[4], rooms[2], rooms[7], rooms[1]);
	rooms[1]->setExits(nullptr,  rooms[0], nullptr,  nullptr);
	rooms[2]->setExits(nullptr,  nullptr,  nullptr,  rooms[0]);
	rooms[3]->setExits(nullptr,  rooms[4], nullptr,  nullptr);
	rooms[4]->setExits(nullptr,  rooms[5], rooms[0], rooms[3]);
	rooms[5]->setExits(nullptr,  nullptr,  nullptr,  rooms[4]);
	rooms[6]->setExits(nullptr,  rooms[7], nullptr,  nullptr);
	rooms[7]->setExits(rooms[0], rooms[8], rooms[9], rooms[6]);
	rooms[8]->setExits(nullptr,  nullptr,  nullptr,  rooms[7]);
	rooms[9]->setExits(rooms[7], nullptr,  nullptr,  nullptr);

	reset();    
}

void Game::reset(bool show_update)
{
	gameOver = false;

	KeyItem* key = new KeyItem("Key", 1, 20, 1);

	rooms[9]->setLock(key);

	rooms[2]->addItem(new CursedItem("Chalice", 1, 10.0, 30));
	rooms[3]->addItem(new UsableItem("Potion", 2, 40, 30));
	rooms[5]->addItem(key);

	player.setCurrentRoom(rooms[0]);
	player.setHealth(100);
	player.setStamina(100);

	cout << "Welcome to Zork!" << endl;
	if (show_update) {
		update_screen();
	}
}

void Game::setOver(bool over)
{
	this->gameOver = over;
}

void Game::map()
{
	cout << "D-E-F" << endl;
	cout << "  |  " << endl;
	cout << "B-A-C" << endl;
	cout << "  |  " << endl;
	cout << "G-H-I" << endl;
	cout << "  |  " << endl;
	cout << "  J  " << endl;
}

void Game::info()
{
	cout << "Available commands:" << endl;
	cout << " - go <direction>"   << endl;
	cout << " - teleport"         << endl;
	cout << " - map"              << endl;
	cout << " - info"             << endl;
	cout << " - take <item>"      << endl;
	cout << " - use <item>"       << endl;
}

void Game::go(string direction)
{
	Room *next = player.getCurrentRoom()->getExit(direction);

	if (next == nullptr)
	{
		cout << "You hit a wall" << endl;
	}
	else if (next->getLock() != NULL)
	{
		KeyItem* keyRequired = (KeyItem*) next->getLock();
		if (!player.hasKey(keyRequired->getLock()))
		{
			cout << "Room is locked" << endl;
		}
		else
		{
			player.setCurrentRoom(next);
			player--;
			EventManager::getInstance().trigger("enterRoom", next);
		}
	}
	else
	{
		player.setCurrentRoom(next);
		player--;
		EventManager::getInstance().trigger("enterRoom", next);
	}
}

void Game::take(string name)
{
	Item *item = player.getCurrentRoom()->takeItem(name);
	if (item != NULL)
	{
		cout << "Item taken" << endl;
		/****************** 10. Dynamic and static dispatch ******************/
		player.addItem(item);
		if (item->getType() == "Cursed")
		{
			EventManager::getInstance().trigger("characterCursed", item);
		}
	}
}

void Game::use(string name)
{
	/****************** 7. Virtual functions and polymorphism ******************/
	Item *item = player.takeItem(name);
	if (item != NULL)
	{
		if(item->getType() == "Potion")
		{
			UsableItem* usableItem = (UsableItem*) item;
			cout << "Used " << name << endl;
			player.setHealth(calculate(player.getHealth(), usableItem->getAmount(), '+'));
		}
		else
		{
			cout << "Item not usable" << endl;
			player.addItem(item);
		}
	}
}

void Game::teleport()
{
	int selected = rand() % rooms.size();
	player.setCurrentRoom(rooms[selected]);
	player.setStamina(calculate(player.getStamina(), 50, '-'));
	EventManager::getInstance().trigger("enterRoom", rooms[selected]);
}

bool Game::is_over()
{
	return gameOver;
}

Character &Game::getPlayer()
{
	return player;
}

void Game::update_screen()
{
	if (!gameOver) {
		Room *currentRoom = player.getCurrentRoom();

		cout << endl;
		cout << "You are in " << currentRoom->getName() << endl;
		cout << "Items: " << currentRoom->getItems() << endl;

		cout << "Exits:";
		if (currentRoom->getExit("north") != nullptr) { cout << " north"; }
		if (currentRoom->getExit("east")  != nullptr) { cout << " east";  }
		if (currentRoom->getExit("south") != nullptr) { cout << " south"; }
		if (currentRoom->getExit("west")  != nullptr) { cout << " west";  }
		cout << endl;

		cout << player << endl;
	} else {
		cout << "Type \"restart\" or \"exit\"." << endl;
	}
}
