//315144972
//roeyshmil09@gmail.com

#include "DevelopmentCardType.hpp"
#include <ostream>

std::ostream& operator<<(std::ostream& os, DevelopmentCardType devType) {
    static std::map<DevelopmentCardType, std::string> developmentCardTypeNameMap = {
        {DevelopmentCardType::Promotion, "Promotion"},
        {DevelopmentCardType::VictoryPoint, "VictoryPoint"},
        {DevelopmentCardType::Knight, "Knight"},
    };

    os << developmentCardTypeNameMap[devType];
    return os;
}
