#ifndef DevelopmentCardType_H
#define DevelopmentCardType_H

#include <iostream>
#include <map>


enum class DevelopmentCardType {
    Promotion,
    VictoryPoint,
    Knight
};

std::ostream& operator<<(std::ostream& os, DevelopmentCardType devType);

#endif // LANDTYPE_H
