//315144972
//roeyshmil09@gmail.com

#include "PromotionCard.hpp"
#include <iostream>


PromotionCard::PromotionCard(PromotionCardType& type)
{
this->type = type;
amount=1;
}

int PromotionCard::getCurrentAmount()
{
return this->amount;
}

void PromotionCard::changeAmount(int count)
{
amount += count;
}

void  PromotionCard::use()
{
amount--;
}






