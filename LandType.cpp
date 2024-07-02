//315144972
//roeyshmil09@gmail.com

#include "LandType.hpp"
#include <ostream>

std::ostream& operator<<(std::ostream& os, LandType landType) {
    static std::map<LandType, std::string> landTypeNameMap = {
        {LandType::Forest, "Forest"},
        {LandType::Hills, "Hills"},
        {LandType::PastureLand, "PastureLand"},
        {LandType::AgriculturalLand, "AgriculturalLand"},
        {LandType::Mountains, "Mountains"},
        {LandType::Desert, "Desert"}
    };

    os << landTypeNameMap[landType];
    return os;
}
