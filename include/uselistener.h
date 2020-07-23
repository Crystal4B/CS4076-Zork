#ifndef USELISTENER_H
#define USELISTENER_H

#include <string>
#include "eventlistener.h"

using namespace std;

class Game;

class UseListener : public EventListener
{
public:
    UseListener(Game *game);
    void run(void *args) override;
private:
    Game *game;
    string item;
};

#endif // USELISTENER_H
