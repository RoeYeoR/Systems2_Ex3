#ifndef RESOURCE_HPP
#define RESOURCE_HPP

enum class ResourceType { Wood, Brick, Wool, Oat, Iron, None };

class Resource {

    private:
        ResourceType type;
        int amount;


    public:
    Resource(ResourceType type); 
    Resource(ResourceType type, int amount);
    ResourceType getType();
    void changeAmount(int amount);
    int getCurrentAmount();
};

#endif // RESOURCE_HPP
