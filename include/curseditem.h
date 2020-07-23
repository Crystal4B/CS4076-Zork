#ifndef CURSEDITEM_H
#define CURSEDITEM_H

#include "item.h"

class CursedItem : public Item
{
private:
   int damage;
public:
    CursedItem(string name, int weight, float value, int damage);

    string getType() override;
    int getDamage();
    void setDamage(int newDamage);
};

#endif // CURSEDITEM_H
