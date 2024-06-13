#ifndef LANDTYPE_H
#define LANDTYPE_H

#include <iostream>
#include <map>

enum class LandType {
    Forest,
    Hills,
    PastureLand,
    AgriculturalLand,
    Mountains,
    Desert
};

std::ostream& operator<<(std::ostream& os, LandType landType);

#endif // LANDTYPE_H
