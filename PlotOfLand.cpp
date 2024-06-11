#include "PlotOfLand.hpp"
#include <string>
PlotOfLand::PlotOfLand() : resource(ResourceType::None), number(0) {}

PlotOfLand::PlotOfLand(ResourceType type, int num) : resource(type), number(num) {}

void PlotOfLand::setResource(ResourceType type) {
    this->resource = Resource(type);
}

void PlotOfLand::setNumber(int num) {
    this->number = num;
}

void PlotOfLand::setlandType(std::string landType)
{
    this->landType = landType;

}

Resource PlotOfLand::getResource() const {
    return resource;
}

int PlotOfLand::getNumber() const {
    return number;
}

std::string PlotOfLand::getLandType() const {
    return this->landType;
}