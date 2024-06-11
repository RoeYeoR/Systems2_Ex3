#include <iostream>
#include <stdexcept>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"
using namespace std;

int main()
{
    // Initialize players
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");

    // Initialize game with players
    Catan catan(p1, p2, p3);

    // Starting the game. Every player places two settlements and two roads.
    catan.ChooseStartingPlayer(); // should print the name of the starting player, assume it is Amit.
    Board board = catan.getBoard(); // get the board of the game.

    // Place initial settlements and roads for p1
    vector<string> places1 = {"Forest", "Hills"};
    vector<int> placesNum1 = {5, 6};
    p1.placeSettlement(places1, placesNum1, board);
    p1.placeRoad(places1, placesNum1, board);

    vector<string> places2 = {"Agricultural Land", "Desert"};
    vector<int> placesNum2 = {3, 4};
    p1.placeSettlement(places2, placesNum2, board);
    p1.placeRoad(places2, placesNum2, board); // p1 chooses Forest, hills, Agricultural Land, Desert with numbers 5, 6, 3, 4.

    // Place initial settlements and roads for p2
    vector<string> places3 = {"Mountains", "Pasture Land"};
    vector<int> placesNum3 = {4, 9};
    p2.placeSettlement(places3, placesNum3, board);
    p2.placeRoad(places3, placesNum3, board);

    // p3 tries to place a settlement in the same location as p2.
    try
    {
        p3.placeSettlement(places3, placesNum3, board);
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    vector<string> places4 = {"Forest", "Pasture Land"};
    vector<int> placesNum4 = {5, 9};
    p2.placeSettlement(places4, placesNum4, board);
    p2.placeRoad(places4, placesNum4, board); // p2 chooses Mountains, Pasture Land, and Forest with numbers 4, 9, 5.

    // Place initial settlements and roads for p3
    vector<string> places5 = {"Mountains", "Pasture Land"};
    vector<int> placesNum5 = {3, 8};
    p3.placeSettlement(places5, placesNum5, board);
    p3.placeRoad(places5, placesNum5, board);

    vector<string> places6 = {"Agricultural Land", "Pasture Land"};
    vector<int> placesNum6 = {3, 9};
    p3.placeSettlement(places6, placesNum6, board);
    p3.placeRoad(places6, placesNum6, board); // p3 chooses Mountains, Pasture Land, Agricultural Land, Pasture Land with numbers 3, 8, 3, 9.

    // p1 has wood, bricks, and wheat; p2 has wood, ore, and wool; p3 has ore, wool, and wheat.
    p1.rollDice(board);                                    // Lets say it prints 4. Then, p2 gets ore from the mountains.
    p1.placeRoad({"Forest", "Hills"}, {5, 6}, board); // p1 continues to build a road.
    p1.endTurn();                                     // p1 ends his turn.

    p2.rollDice(board); // Lets say it prints 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    p2.endTurn();  // p2 ends his turn.

    p3.rollDice(board); // Lets say it prints 3. Then, p3 gets wheat from the Agricultural Land and ore from the Mountains, p1 gets wheat from the Agricultural Land.
    p3.endTurn();  // p3 ends his turn.

    try
    {
        p2.rollDice(board); // p2 tries to roll the dice again, but it's not his turn.
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }

    p1.rollDice(board);                       // Lets say it prints 6. Then, p1 gets bricks from the hills.
    p1.trade(p2, ResourceType::Wood, ResourceType::Brick, 1, 1); // p1 trades 1 wood for 1 brick with p2.
    p1.endTurn();                        // p1 ends his turn.

    p2.rollDice(board);           // Lets say it prints 9. Then, p3 gets wool from the Pasture Land, p2 gets wool from the Pasture Land.
    p2.buyDevelopmentCard(); // p2 buys a development card. Lets say it is a bonus points card.
    p2.endTurn();            // p2 ends his turn.

    p1.printPoints(); // p1 has 2 points because it has two settlements.
    p2.printPoints(); // p2 has 3 points because it has two settlements and a bonus points card.
    p3.printPoints(); // p3 has 2 points because it has two settlements.

    catan.printWinner(); // Should print None because no player reached 10 points.

    return 0;
}
