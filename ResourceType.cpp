//315144972
//roeyshmil09@gmail.com

#include "ResourceType.hpp"
#include <ostream>

std::ostream& operator<<(std::ostream& os, ResourceType resourceType) {
    static std::map<ResourceType, std::string> resourceTypeNameMap = {
        {ResourceType::Wood, "Wood"},
        {ResourceType::Brick, "Brick"},
        {ResourceType::Wool, "Wool"},
        {ResourceType::Oat, "Oat"},
        {ResourceType::Iron, "Iron"},
        {ResourceType::None, "None"}
    };

    os << resourceTypeNameMap[resourceType];
    return os;
}
