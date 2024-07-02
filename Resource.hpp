#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include "ResourceType.hpp"

class Resource {

private:
    ResourceType type;
    int amount;


public:
    Resource(ResourceType type); 
    Resource(ResourceType type, int amount);
    ResourceType getType() const;
    int getCurrentAmount();
    void changeAmount(int amount);
    void resetAmount();
    friend std::ostream& operator<<(std::ostream& os, const ResourceType& resource);
};

#endif // RESOURCE_HPP
