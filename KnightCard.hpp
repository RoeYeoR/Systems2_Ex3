#ifndef KNIGHT_CARD_HPP
#define KNIGHT_CARD_HPP

#include "DevelopmentCard.hpp"

class KnightCard : public DevelopmentCard {
private:
     static int amount;

public:
    KnightCard();
    int getAmount();
    void use() override;
};

#endif // KNIGHT_CARD_HPP
