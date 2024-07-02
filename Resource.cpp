//315144972
//roeyshmil09@gmail.com


#include "Resource.hpp"
#include <ostream>


Resource::Resource(ResourceType type) : type(type) , amount(0){}
Resource::Resource(ResourceType type, int amount) : type(type), amount(amount) {}

ResourceType Resource::getType() const
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
void Resource::resetAmount()
{
    amount = 0;

}

std::ostream& operator<<(std::ostream& os, const ResourceType& resource) {
    switch (resource) {
        case ResourceType::Wood: os << "Wood"; break;
        case ResourceType::Brick: os << "Brick"; break;
        case ResourceType::Wool: os << "Sheep"; break;
        case ResourceType::Oat: os << "Wheat"; break;
        case ResourceType::Iron: os << "Ore"; break;
        default: os.setstate(std::ios_base::failbit);
    }
    return os;
}

