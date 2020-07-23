#ifndef GAME_H
#define GAME_H

#include<string>
#include<vector>

#include "character.h"
#include "room.h"

using namespace std;

class Game
{
public:
    Game();
    void reset(bool show_update = true);

    void map();
    void info();
    void go(string direction);
    void teleport();
    void take(string item);
    void use(string item);

    void update_screen();

    Character &getPlayer();
    void setOver(bool over);
    bool is_over();
    void setCurrentRoom(Room *next);

private:
    Character      player;
    vector<Room *> rooms;
    bool           gameOver;

    /****************** 3. Templates ******************/
    template<typename T, typename T2>
    T calculate(T num1, T num2, T2 operand)
    {
        switch(operand)
        {
            case '+': return num1 + num2;
            case '-': return num1 - num2;
            case '*': return num1 * num2;
            case '/': return num1 / num2;
        }
        return -1;
    }
};
#endif // GAME_H
