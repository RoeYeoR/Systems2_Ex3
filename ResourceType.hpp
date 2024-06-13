#ifndef RESOURCESTYPE_H
#define RESOURCESTYPE_H

#include <iostream>
#include <map>

enum class ResourceType { 
    Wood =0,
    Brick=1, 
    Wool=3, 
    Oat=4, 
    Iron=5, 
    None=6 

 };
    

std::ostream& operator<<(std::ostream& os, ResourceType resourceType);

#endif // RESOURCESTYPE_H
