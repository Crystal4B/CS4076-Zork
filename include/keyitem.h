#ifndef KEYITEM_H
#define KEYITEM_H

#include "item.h"

class Room;

class KeyItem : public Item
{
private:
    int lock_id;

public:
    KeyItem(string name, int weight, float value, int lock_id);

    string getType() override;
    int getLock();
    void setLock(int newLock_id);
};

#endif // KEYITEM_H
