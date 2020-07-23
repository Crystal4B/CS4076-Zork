#include<iostream>
#include "takelistener.h"
#include "game.h"

TakeListener::TakeListener(Game *game)
{
    this->game = game;
}

void TakeListener::run(void *args_ptr)
{
    if (game->is_over())
    {
        return;
    }

    vector<string> *args = (vector<string> *) args_ptr;
    if (args->size() > 1)
    {
        // in case our item is longer than one word
        string item = args->at(1);
        for (unsigned int i = 2; i < args->size(); i++)
        {
            item += " " + args->at(i);
        }
        game->take(args->at(1));
    }
    else
    {
        cout << "Need Item" << endl;
    }
}
