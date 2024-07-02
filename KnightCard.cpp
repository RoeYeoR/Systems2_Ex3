//315144972
//roeyshmil09@gmail.com

#include "KnightCard.hpp"
#include <iostream>


int KnightCard::amount = 0;


KnightCard::KnightCard()
{
    amount ++;
}

int KnightCard::getAmount()
{
    return this->amount;
}



void KnightCard::use() {
    // Implement the use of knight card
    std::cout << "Using a Knight Card" << std::endl;
}
