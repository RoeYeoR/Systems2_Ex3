#include "PromotionCard.hpp"
#include <iostream>


int PromotionCard::amount =0;


PromotionCard::PromotionCard(PromotionCardType& type)
{
    this->type = type;
    amount++;
}




int PromotionCard::getAmount()
{
    return this->amount;
}




void PromotionCard::use() {
    // switch (type) {
    //         case PromotionCardType::Monopoly:
    //             useMonopoly();
    //             break;
    //         case PromotionCardType::BuildingRoads:
    //             useBuildingRoads();
    //             break;
    //         case PromotionCardType::YearOfAbundance:
    //             useYearOfAbundance();
    //             break;
    //     }
    std::cout<<"override development card use function";
    
}

    // void PromotionCard::useMonopoly() {
    //     std::string resource;
    //     std::cout << "Enter the resource you want to monopolize: ";
    //     std::cin >> resource;

    //     for (Player& otherPlayer : catan.players) {
    //         if (&otherPlayer != &player) {
    //             int amount = otherPlayer.resources[resource];
    //             catan.transferResource(otherPlayer, player, resource, amount);
    //         }
    //     }
    // }

    // void PromotionCard::useBuildingRoads() {
    //     catan.buildRoad(player);
    //     catan.buildRoad(player);
    // }

    // void PromotionCard::useYearOfAbundance() {
    //     std::string resource1, resource2;
    //     std::cout << "Enter the first resource you want: ";
    //     std::cin >> resource1;
    //     std::cout << "Enter the second resource you want: ";
    //     std::cin >> resource2;

    //     player.receiveResource(resource1, 1);
    //     player.receiveResource(resource2, 1);
    // }
