#ifndef PROMOTION_CARD_HPP
#define PROMOTION_CARD_HPP

#include "DevelopmentCard.hpp"



enum class PromotionCardType {
    Monopoly,
    BuildingRoads,
    YearOfAbundance
};


class PromotionCard : public DevelopmentCard 
{   
    private:
        PromotionCardType type;
        static int amount;

    public:
        PromotionCard(PromotionCardType& type);
      
        int getAmount();
        void use();
        void useMonopoly();
        void useBuildingRoads();
        void useYearOfAbundance();
};

#endif // PROMOTION_CARD_HPP
