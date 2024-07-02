//315144972
//roeyshmil09@gmail.com

#include <iostream>
#include <stdexcept>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "LandType.hpp"
#include "VertexPositionType.hpp"
using namespace std;


int main()
{
    // Initialize players
    Player p1("Amit"); // assume it's red
    Player p2("Yossi"); // assume it's white
    Player p3("Dana");// assume it's blue

    // Initialize game with players
    Catan catan(p1, p2, p3);
      std::cout << std::endl;
    // Starting the game. Every player places two settlements and two roads.
    catan.ChooseStartingPlayer(); // should print the name of the starting player, assume it is Amit.
    Board board = catan.getBoard(); // get the board of the game.
    board.printBoard();
    board.printLayout();

    // Place first settlement
    p1.placeSettlement(catan,board, 0,VertexPositionType::BottomRightVertex);
    p1.placeRoad(board, 4,VertexPositionType::UpVertex, VertexPositionType::UpRightVertex);
    
    // Place second settlement
    p1.placeSettlement(catan,board, 12, VertexPositionType::UpVertex);
    p1.placeRoad(board, 12, VertexPositionType::UpVertex, VertexPositionType::UpRightVertex);
    p1.showAllResources();
    std::cout<< "*****************************************************************************************************" << "\n";
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

        // Place first settlement
    p2.placeSettlement(catan,board, 4,VertexPositionType::BottomLeftVertex);
    p2.placeRoad(board, 3,VertexPositionType::BottomRightVertex, VertexPositionType::BottomVertex);

    // Place second settlement
    p2.placeSettlement(catan,board, 15, VertexPositionType::UpVertex);
    p2.placeRoad(board, 11, VertexPositionType::BottomLeftVertex, VertexPositionType::UpLeftVertex);
    p2.showAllResources();
    std::cout<< "*****************************************************************************************************" << "\n";
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

        // Place first settlement
    p3.placeSettlement(catan,board, 13,VertexPositionType::BottomLeftVertex);
    p3.placeRoad(board, 16,VertexPositionType::UpVertex, VertexPositionType::UpRightVertex);

    // Place second settlement
    p3.placeSettlement(catan,board, 18, VertexPositionType::UpVertex);
    p3.placeRoad(board, 14, VertexPositionType::BottomRightVertex, VertexPositionType::UpRightVertex);
    p3.showAllResources();
    std::cout<< "*****************************************************************************************************" << "\n";
    //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    std::cout << std::endl;
    std::cout << std::endl;
    p1.rollDice(catan,board);                                   
    p1.placeRoad(board,4,VertexPositionType::UpRightVertex,VertexPositionType::BottomRightVertex); 
    p1.endTurn(); 

    std::cout << std::endl;
    std::cout << std::endl;                                   
       
    p2.rollDice(catan,board); 
    p2.endTurn(); 

    std::cout << std::endl;
    std::cout << std::endl;
    p3.rollDice(catan,board); 
    p3.endTurn(); 

    std::cout << std::endl;
    std::cout << std::endl;


    p1.rollDice(catan,board);                     
    p1.trade(p2, ResourceType::Wood, ResourceType::Brick, 1, 1); 
    p1.trade(p3, ResourceType::Oat, ResourceType::Wood, 1, 1);
    p1.showAllResources();
    p2.showAllResources();
    p3.showAllResources(); 
    p1.endTurn();   

    std::cout << std::endl;
    std::cout << std::endl;                     

    p2.rollDice(catan,board);         
    p2.buyDevelopmentCard(); 
    p2.trade(p1,ResourceType::Brick, ResourceType::Iron,1,1);
    p1.showAllResources();
    p2.showAllResources();
    p2.endTurn();            

    std::cout << std::endl;
    std::cout << std::endl;

    p3.rollDice(catan,board);
    p3.buyDevelopmentCard();
    p3.buyDevelopmentCard();
    p3.useDevelopmentCard(catan,DevelopmentCardType::VictoryPoint);
    p3.useDevelopmentCard(catan,DevelopmentCardType::Promotion);
    p3.showAllResources();
    p3.endTurn();
    std::cout << std::endl;
    std::cout << std::endl;


    p1.rollDice(catan,board);
    p1.placeSettlement(catan,board, 4,VertexPositionType::BottomRightVertex);
    p1.placeCity(board,Point2D(2,4));
    p1.buyDevelopmentCard();
    p1.buyDevelopmentCard();
    p1.useDevelopmentCard(catan,DevelopmentCardType::Promotion);                     
    p1.trade(p2, ResourceType::Iron, ResourceType::Wool, 2, 1); 
    p1.trade(p3, ResourceType::Wool, ResourceType::Oat, 1, 2);
    p1.showAllResources();
    p1.endTurn();

    std::cout << std::endl;
    std::cout << std::endl;


    p2.rollDice(catan,board);
    p2.placeRoad(board, 8,VertexPositionType::UpVertex,VertexPositionType::UpRightVertex);
    p2.placeRoad(board, 8,VertexPositionType::UpRightVertex, VertexPositionType::BottomRightVertex);
    p2.trade(p1,ResourceType::Oat, ResourceType::Wood, 2, 1);
    p2.showAllResources();
    p2.endTurn();

    std::cout << std::endl;
    std::cout << std::endl;

    p3.rollDice(catan,board);
    p3.buyDevelopmentCard();
    p3.useDevelopmentCard(catan,DevelopmentCardType::Knight);
    p3.showAllResources();
    p3.endTurn();

    std::cout << std::endl;
    std::cout << std::endl;

    p1.rollDice(catan,board);
    p1.useDevelopmentCard(catan,DevelopmentCardType::Knight);
    p1.trade(p3,ResourceType::Brick,ResourceType::Oat,2,3);
    p1.showAllResources();
    p3.showAllResources();
    p1.endTurn();


    std::cout << std::endl;
    std::cout << std::endl;


    p2.rollDice(catan,board);
    p2.placeSettlement(catan,board,8,VertexPositionType::BottomRightVertex);
    p2.placeCity(board,Point2D(4,3));
    p2.endTurn();

    std::cout << std::endl;
    std::cout << std::endl;


    p3.rollDice(catan,board);
    p3.placeCity(board,Point2D(8,3));
    p3.endTurn();

    std::cout<< "************** Final Points for this Game: ************** "<<std::endl;
    std::cout << std::endl;

    p1.printPoints();
    p2.printPoints();
    p3.printPoints();


    catan.printWinner();

    return 0;
}
