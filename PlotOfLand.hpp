#ifndef PLOTOFLAND_HPP
#define PLOTOFLAND_HPP

#include "Resource.hpp"
#include "LandType.hpp"
#include <string>



class PlotOfLand {
private:
    Resource resource;
    LandType landType;
    int number;

public:
    PlotOfLand();
    PlotOfLand(ResourceType type, int num);

    void setResource(ResourceType type);
    void setNumber(int num);
    void setlandType(LandType landType);
    Resource getResource() const;
    int getNumber() const;
    LandType getLandType() const;
   
};

#endif // PLOTOFLAND_HPP
