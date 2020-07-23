#include "usableitem.h"

UsableItem::UsableItem(string name, int weight, float value, int amount) : Item(name, weight, value)
{
    this->amount = amount;
}

string UsableItem::getType()
{
    return "Potion";
}

int UsableItem::getAmount()
{
    return this->amount;
}

void UsableItem::setAmount(int newAmount)
{
    this->amount = newAmount;
}
