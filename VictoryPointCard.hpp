#ifndef VICTORY_POINT_CARD_HPP
#define VICTORY_POINT_CARD_HPP

#include "DevelopmentCard.hpp"

class VictoryPointCard : public DevelopmentCard {

private:
    static int amount;  
    
public:
    VictoryPointCard();
    int getAmount();
    void use();
};

#endif // VICTORY_POINT_CARD_HPP
