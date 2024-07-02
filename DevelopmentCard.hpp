//315144972
//roeyshmil09@gmail.com

#ifndef DEVELOPMENT_CARD_HPP
#define DEVELOPMENT_CARD_HPP
#include <ostream>
#include "DevelopmentCardType.hpp"


class DevelopmentCard {
    
    public:
    virtual ~DevelopmentCard() {}
    virtual void use() = 0;
   
};

#endif // DEVELOPMENT_CARD_HPP
