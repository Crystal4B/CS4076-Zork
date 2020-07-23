#include "item.h"

/****************** 9. Initializer list ******************/
Item::Item(string name, int weight, float value)
    : name{name}, weight{weight}, value{value}
{

}

/****************** 1. Deconstructor ******************/
Item::~Item()
{
    delete this;
}

string Item::getName()
{
    return this->name;
}

string Item::getType()
{
    return "Miscellaneous";
}

int Item::getWeight()
{
    return this->weight;
}

float Item::getValue()
{
    return this->value;
}

void Item::setName(string newName)
{
    this->name = newName;
}

void Item::setWeight(int newWeight)
{
    this->weight = newWeight;
}

void Item::setValue(float newValue)
{
    this->value = newValue;
}

/****************** 5. Binary operator overloading ******************/
bool Item::operator==(Item *other)
{
    return this->name == other->getName();
}
