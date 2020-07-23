#ifndef USABLEITEM_H
#define USABLEITEM_H

#include "item.h"

/****************** 2. Inheritance (including virtual methods) and cascading constructors ******************/
class UsableItem : public Item
{
public:
    UsableItem(string name, int weight, float value, int amount);

    string getType() override;
    int getAmount();
    void setAmount(int newAmount);
private:
    int amount;
};

#endif // USABLEITEM_H
