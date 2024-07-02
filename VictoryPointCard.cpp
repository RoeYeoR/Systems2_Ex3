//315144972
//roeyshmil09@gmail.com

#include "VictoryPointCard.hpp"
#include <iostream>

int VictoryPointCard::amount = 0;

VictoryPointCard::VictoryPointCard()
{
amount++;
}

int VictoryPointCard::getAmount()
{
return this->amount;
}


void VictoryPointCard::use() {
// Implement the use of victory point card
std::cout << "Using a Victory Point Card" << std::endl;
}
