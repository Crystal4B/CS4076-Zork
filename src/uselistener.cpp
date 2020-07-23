#include "uselistener.h"

#include <iostream>

#include "eventmanager.h"
#include "game.h"

UseListener::UseListener(Game *game)
{
    this->game = game;
}

void UseListener::run(void *args_ptr)
{
    vector<string> *args = (vector<string> *) args_ptr;

    if (args->size() > 1) {
        game->use(args->at(1));
    } else {
        cout << "Need a Item!" << endl;
    }
}
