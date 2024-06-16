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

    // Starting the game. Every player places two settlements and two roads.
    catan.ChooseStartingPlayer(); // should print the name of the starting player, assume it is Amit.
    Board board = catan.getBoard(); // get the board of the game.
    board.printBoard();
    board.printLayout();


    PlotOfLand plot0 = board.getPlot(0);
    std::cout <<"plot0 resource type: " << plot0.getResource().getType() << "\n";

    PlotOfLand plot1 = board.getPlot(1);
    std::cout << "plot1 resource type: " << plot1.getResource().getType() << "\n";


     // Player p1 (Amit) places two settlements and two roads
    try {
        // Place first settlement
        p1.placeSettlement(catan,board, 0,VertexPositionType::BottomRightVertex);
        p1.placeRoad(board, 4,VertexPositionType::UpVertex, VertexPositionType::UpRightVertex);
        
        // Place second settlement
        p1.placeSettlement(catan,board, 12, VertexPositionType::UpVertex);
        p1.placeRoad(board, 12, VertexPositionType::UpVertex, VertexPositionType::UpRightVertex);
        std::cout<< "*****************************************************************************************************" << "\n";
        //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

         // Place first settlement
        p2.placeSettlement(catan,board, 4,VertexPositionType::BottomLeftVertex);
        p2.placeRoad(board, 3,VertexPositionType::BottomRightVertex, VertexPositionType::BottomVertex);

        // Place second settlement
        p2.placeSettlement(catan,board, 15, VertexPositionType::UpVertex);
        p2.placeRoad(board, 11, VertexPositionType::BottomLeftVertex, VertexPositionType::UpLeftVertex);
        std::cout<< "*****************************************************************************************************" << "\n";
        //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

         // Place first settlement
        p3.placeSettlement(catan,board, 13,VertexPositionType::BottomLeftVertex);
        p3.placeRoad(board, 16,VertexPositionType::UpVertex, VertexPositionType::UpRightVertex);

        // Place second settlement
        p3.placeSettlement(catan,board, 18, VertexPositionType::UpVertex);
        p3.placeRoad(board, 14, VertexPositionType::BottomRightVertex, VertexPositionType::UpRightVertex);
        std::cout<< "*****************************************************************************************************" << "\n";
        //||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


       
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }




    

   
    

    // p1 has wood, bricks, and wheat; p2 has wood, ore, and wool; p3 has ore, wool, and wheat.
    p1.rollDice(catan,board);                                    // Lets say it prints 4. Then, p2 gets ore from the mountains.
    p1.placeRoad(board,4,VertexPositionType::UpRightVertex,VertexPositionType::BottomRightVertex); // p1 continues to build a road.
    p1.endTurn();                                     // p1 ends his turn.
       
    p2.rollDice(catan,board); // Lets say it prints 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    p2.endTurn();  // p2 ends his turn.

    p3.rollDice(catan,board); // Lets say it prints 3. Then, p3 gets wheat from the Agricultural Land and ore from the Mountains, p1 gets wheat from the Agricultural Land.
    p3.endTurn();  // p3 ends his turn.
     /*
    try
    {
        p2.rollDice(board); // p2 tries to roll the dice again, but it's not his turn.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    */

   
    p1.rollDice(catan,board);                       // Lets say it prints 6. Then, p1 gets bricks from the hills.
    p1.trade(p2, ResourceType::Wood, ResourceType::Brick, 1, 1); // p1 trades 1 wood for 1 brick with p2.
    p1.endTurn();                        // p1 ends his turn.

    p2.rollDice(catan,board);           // Lets say it prints 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    p2.buyDevelopmentCard(); // p2 buys a development card. Lets say it is a bonus points card.
    p2.endTurn();            // p2 ends his turn.
    /*
    p1.printPoints(); // p1 has 2 points because it has two settlements.
    p2.printPoints(); // p2 has 3 points because it has two settlements and a bonus points card.
    p3.printPoints(); // p3 has 2 points because it has two settlements.

    catan.printWinner(); // Should print None because no player reached 10 points.
    */
    return 0;
}
