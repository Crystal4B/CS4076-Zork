#include "curseditem.h"

CursedItem::CursedItem(string name, int weight, float value, int damage) : Item(name, weight, value)
{
    this->damage = damage;
}

string CursedItem::getType()
{
    return "Cursed";
}

int CursedItem::getDamage()
{
    return this->damage;
}

void CursedItem::setDamage(int newDamage)
{
    this->damage = newDamage;
}
