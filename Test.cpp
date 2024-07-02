//315144972
//roeyshmil09@gmail.com

#include "doctest.h"
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "LandType.hpp"
#include "VertexPositionType.hpp"

TEST_CASE("Catan Initialization and Starting Player") {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");

    Catan catan(p1, p2, p3);
    Board board = catan.getBoard();

    REQUIRE_NOTHROW(catan.ChooseStartingPlayer());
}

TEST_CASE("Player Settlements and Roads") {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");

    Catan catan(p1, p2, p3);
    Board board = catan.getBoard();

    REQUIRE_NOTHROW(p1.placeSettlement(catan, board, 0, VertexPositionType::BottomRightVertex));
    REQUIRE_NOTHROW(p1.placeRoad(board, 4, VertexPositionType::UpVertex, VertexPositionType::UpRightVertex));

    REQUIRE_NOTHROW(p1.placeSettlement(catan, board, 12, VertexPositionType::UpVertex));
    REQUIRE_NOTHROW(p1.placeRoad(board, 12, VertexPositionType::UpVertex, VertexPositionType::UpRightVertex));

    REQUIRE_NOTHROW(p2.placeSettlement(catan, board, 4, VertexPositionType::BottomLeftVertex));
    REQUIRE_NOTHROW(p2.placeRoad(board, 3, VertexPositionType::BottomRightVertex, VertexPositionType::BottomVertex));

    REQUIRE_NOTHROW(p2.placeSettlement(catan, board, 15, VertexPositionType::UpVertex));
    REQUIRE_NOTHROW(p2.placeRoad(board, 11, VertexPositionType::BottomLeftVertex, VertexPositionType::UpLeftVertex));

    REQUIRE_NOTHROW(p3.placeSettlement(catan, board, 13, VertexPositionType::BottomLeftVertex));
    REQUIRE_NOTHROW(p3.placeRoad(board, 16, VertexPositionType::UpVertex, VertexPositionType::UpRightVertex));

    REQUIRE_NOTHROW(p3.placeSettlement(catan, board, 18, VertexPositionType::UpVertex));
    REQUIRE_NOTHROW(p3.placeRoad(board, 14, VertexPositionType::BottomRightVertex, VertexPositionType::UpRightVertex));
}

TEST_CASE("Player Dice Roll and Resource Management") {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");

    Catan catan(p1, p2, p3);
    Board board = catan.getBoard();

    REQUIRE_NOTHROW(p1.rollDice(catan, board));
    REQUIRE_NOTHROW(p1.endTurn());

    REQUIRE_NOTHROW(p2.rollDice(catan, board));
    REQUIRE_NOTHROW(p2.endTurn());

    REQUIRE_NOTHROW(p3.rollDice(catan, board));
    REQUIRE_NOTHROW(p3.endTurn());
}

TEST_CASE("Trading and Resource Management") {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");

    Catan catan(p1, p2, p3);
    Board board = catan.getBoard();

    REQUIRE_NOTHROW(p1.trade(p2, ResourceType::Wood, ResourceType::Brick, 1, 1));
    REQUIRE_NOTHROW(p1.trade(p3, ResourceType::Oat, ResourceType::Wood, 1, 1));

    REQUIRE_NOTHROW(p2.trade(p1, ResourceType::Brick, ResourceType::Iron, 1, 1));
}

TEST_CASE("Development Cards Usage") {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");

    Catan catan(p1, p2, p3);

    REQUIRE_NOTHROW(p2.buyDevelopmentCard());
    REQUIRE_NOTHROW(p3.buyDevelopmentCard());
    REQUIRE_NOTHROW(p3.useDevelopmentCard(catan, DevelopmentCardType::VictoryPoint));
    REQUIRE_NOTHROW(p3.useDevelopmentCard(catan, DevelopmentCardType::Promotion));

    REQUIRE_NOTHROW(p1.useDevelopmentCard(catan, DevelopmentCardType::Promotion));
}

TEST_CASE("Settlement and City Placement") {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");

    Catan catan(p1, p2, p3);
    Board board = catan.getBoard();

    REQUIRE_NOTHROW(p1.placeSettlement(catan, board, 4, VertexPositionType::BottomRightVertex));
    REQUIRE_NOTHROW(p1.placeCity(board, Point2D(2, 4)));

    REQUIRE_NOTHROW(p2.placeSettlement(catan, board, 8, VertexPositionType::BottomRightVertex));
    REQUIRE_NOTHROW(p2.placeCity(board, Point2D(4, 3)));

    REQUIRE_NOTHROW(p3.placeCity(board, Point2D(8, 3)));
}

TEST_CASE("Final Points and Winner") {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");

    Catan catan(p1, p2, p3);

    REQUIRE_NOTHROW(p1.printPoints());
    REQUIRE_NOTHROW(p2.printPoints());
    REQUIRE_NOTHROW(p3.printPoints());

    REQUIRE_NOTHROW(catan.printWinner());
}

TEST_CASE("Settlement and City Placement") 
{
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");

    Catan catan(p1, p2, p3);
    Board board = catan.getBoard();

    REQUIRE_NOTHROW(p1.placeSettlement(catan, board, 4, VertexPositionType::BottomRightVertex));
    REQUIRE_NOTHROW(p1.placeCity(board, Point2D(2, 4)));

    REQUIRE_NOTHROW(p2.placeSettlement(catan, board, 8, VertexPositionType::BottomRightVertex));
    REQUIRE_NOTHROW(p2.placeCity(board, Point2D(4, 3)));

    REQUIRE_NOTHROW(p3.placeCity(board, Point2D(8, 3)));
}

TEST_CASE("Player Dice Roll and Resource Management") {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");

    Catan catan(p1, p2, p3);
    Board board = catan.getBoard();

    REQUIRE_NOTHROW(p1.rollDice(catan, board));
    REQUIRE_NOTHROW(p1.endTurn());

    REQUIRE_NOTHROW(p2.rollDice(catan, board));
    REQUIRE_NOTHROW(p2.endTurn());

    REQUIRE_NOTHROW(p3.rollDice(catan, board));
    REQUIRE_NOTHROW(p3.endTurn());
}


TEST_CASE("Extended Gameplay with Dice Rolls, Trades, and Development Cards") {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dana");

    Catan catan(p1, p2, p3);
    Board board = catan.getBoard();

    // Initial settlements and roads
    p1.placeSettlement(catan, board, 0, VertexPositionType::BottomRightVertex);
    p1.placeRoad(board, 4, VertexPositionType::UpVertex, VertexPositionType::UpRightVertex);
    p1.placeSettlement(catan, board, 12, VertexPositionType::UpVertex);
    p1.placeRoad(board, 12, VertexPositionType::UpVertex, VertexPositionType::UpRightVertex);
    
    p2.placeSettlement(catan, board, 4, VertexPositionType::BottomLeftVertex);
    p2.placeRoad(board, 3, VertexPositionType::BottomRightVertex, VertexPositionType::BottomVertex);
    p2.placeSettlement(catan, board, 15, VertexPositionType::UpVertex);
    p2.placeRoad(board, 11, VertexPositionType::BottomLeftVertex, VertexPositionType::UpLeftVertex);
    
    p3.placeSettlement(catan, board, 13, VertexPositionType::BottomLeftVertex);
    p3.placeRoad(board, 16, VertexPositionType::UpVertex, VertexPositionType::UpRightVertex);
    p3.placeSettlement(catan, board, 18, VertexPositionType::UpVertex);
    p3.placeRoad(board, 14, VertexPositionType::BottomRightVertex, VertexPositionType::UpRightVertex);

    // Rolling dice and trading resources
    p1.rollDice(catan, board);
    p1.trade(p2, ResourceType::Wood, ResourceType::Brick, 1, 1);
    p1.trade(p3, ResourceType::Oat, ResourceType::Wood, 1, 1);
    p1.endTurn();

    p2.rollDice(catan, board);
    p2.trade(p1, ResourceType::Brick, ResourceType::Iron, 1, 1);
    p2.endTurn();

    p3.rollDice(catan, board);
    p3.endTurn();

    // Buying and using development cards
    p1.buyDevelopmentCard();
    p1.useDevelopmentCard(catan, DevelopmentCardType::Promotion);
    p1.endTurn();

    p2.buyDevelopmentCard();
    p2.useDevelopmentCard(catan, DevelopmentCardType::Knight);
    p2.endTurn();

    p3.buyDevelopmentCard();
    p3.useDevelopmentCard(catan, DevelopmentCardType::VictoryPoint);
    p3.endTurn();

    // Additional actions
    p1.rollDice(catan, board);
    p1.placeSettlement(catan, board, 4, VertexPositionType::BottomRightVertex);
    p1.placeCity(board, Point2D(2, 4));
    p1.trade(p2, ResourceType::Iron, ResourceType::Wool, 2, 1);
    p1.trade(p3, ResourceType::Wool, ResourceType::Oat, 1, 2);
    p1.endTurn();

    p2.rollDice(catan, board);
    p2.placeRoad(board, 8, VertexPositionType::UpVertex, VertexPositionType::UpRightVertex);
    p2.placeRoad(board, 8, VertexPositionType::UpRightVertex, VertexPositionType::BottomRightVertex);
    p2.endTurn();

    p3.rollDice(catan, board);
    p3.buyDevelopmentCard();
    p3.useDevelopmentCard(catan, DevelopmentCardType::Knight);
    p3.endTurn();

    // Final points and winner
    REQUIRE_NOTHROW(p1.printPoints());
    REQUIRE_NOTHROW(p2.printPoints());
    REQUIRE_NOTHROW(p3.printPoints());
    REQUIRE_NOTHROW(catan.printWinner());
}
