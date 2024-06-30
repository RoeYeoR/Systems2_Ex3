#ifndef RESOURCESTYPE_H
#define RESOURCESTYPE_H

#include <iostream>
#include <map>

enum class ResourceType { 
    Wood =0,
    Brick=1, 
    Wool=2, 
    Oat=3, 
    Iron=4, 
    None=5

 };
    

std::ostream& operator<<(std::ostream& os, ResourceType resourceType);

#endif // RESOURCESTYPE_H
