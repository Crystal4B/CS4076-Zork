#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

// Item.h
/****************** 8. Abstract classes and pure virtual functions ******************/
class Item
{
private:
    string name;
    int weight;
    float value;

public:
    virtual string getType() = 0;

    Item(string name, int weight, float value);
    virtual ~Item();
    string getName();
    int getWeight();
    float getValue();
    void setName(string newName);
    void setWeight(int newWeight);
    void setValue(float newValue);

    bool operator==(Item *other);
};

#endif // ITEM_H
