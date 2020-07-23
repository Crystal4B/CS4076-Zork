#ifndef CHARACTERCURSEDLISTENER_H
#define CHARACTERCURSEDLISTENER_H

#include "eventlistener.h"

class Game;

class CharacterCursedListener : public EventListener
{
public:
    CharacterCursedListener(Game *game);
    void run(void *args) override;
private:
    Game *game;
};

#endif // CHARACTERCURSEDLISTENER_H
