#ifndef TAKELISTENER_H
#define TAKELISTENER_H

#include "eventlistener.h"

class Game;

// TakeListener.h
class TakeListener : public EventListener
{
private:
    Game *game;
public:
    TakeListener(Game *game);
    void run(void *args) override;
};

#endif // TAKELISTENER_H
