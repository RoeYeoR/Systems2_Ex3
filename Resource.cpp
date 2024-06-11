#include "Resource.hpp"


Resource::Resource(ResourceType type) : type(type) , amount(0){}
Resource::Resource(ResourceType type, int amount) : type(type), amount(amount) {}

ResourceType Resource::getType()
{
    return type;
}

void Resource::changeAmount(int amount)
{
    this->amount += amount;
}

int Resource::getCurrentAmount()
{
    return this->amount;
}

