#ifndef PLOTOFLAND_HPP
#define PLOTOFLAND_HPP

#include "Resource.hpp"
#include <string>

class PlotOfLand {
private:
    Resource resource;
    std::string landType;
    int number;

public:
    PlotOfLand();
    PlotOfLand(ResourceType type, int num);

    void setResource(ResourceType type);
    void setNumber(int num);
    void setlandType(std::string landType);
    Resource getResource() const;
    int getNumber() const;
    std::string getLandType() const;
};

#endif // PLOTOFLAND_HPP
