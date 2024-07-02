#ifndef PROMOTION_CARD_HPP
#define PROMOTION_CARD_HPP

#include "DevelopmentCard.hpp"


enum class PromotionCardType {
    Monopoly,
    BuildingRoads,
    YearOfAbundance,
    None
};

class PromotionCard : public DevelopmentCard 
{   
    private:
        PromotionCardType type;
        int amount= 0;

    public:
        PromotionCard(PromotionCardType& type);
        PromotionCardType getType();
        void changeAmount(int count);
        int getCurrentAmount();
        void use();
};

#endif // PROMOTION_CARD_HPP
