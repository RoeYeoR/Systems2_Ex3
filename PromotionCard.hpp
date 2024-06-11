#ifndef PROMOTION_CARD_HPP
#define PROMOTION_CARD_HPP

#include "DevelopmentCard.hpp"

class PromotionCard : public DevelopmentCard {
public:
    void use() override;
};

#endif // PROMOTION_CARD_HPP
