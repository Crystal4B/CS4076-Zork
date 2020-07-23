#include "keyitem.h"

KeyItem::KeyItem(string name, int weight, float value, int lock_id) : Item(name, weight, value), lock_id{lock_id}
{

}

string KeyItem::getType()
{
    return "Key";
}

int KeyItem::getLock()
{
    return this->lock_id;
}

void KeyItem::setLock(int newLock_id)
{
    this->lock_id = newLock_id;
}
