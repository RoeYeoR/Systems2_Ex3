# Catan Game Project

This project is a simplified implementation of the board game Catan. It includes core functionalities such as initializing players, placing settlements and roads, rolling dice, trading resources, and using development cards.

## Features

- Initialize players and the game board.
- Players can place settlements and roads.
- Players can roll dice to collect resources.
- Players can trade resources with each other.
- Players can buy and use development cards.
- Print the game board and layout.
- Determine the winner based on points.
## Main Methods
### Player Class

- `void placeSettlement(Catan& game, Board& board, int location, VertexPositionType position)`: Places a settlement for the player at the specified location and position on the board.
- `void placeRoad(Board& board, int location, VertexPositionType start, VertexPositionType end)`: Places a road for the player between the specified start and end positions at the given location.
- `void rollDice(Catan& game, Board& board)`: Simulates rolling the dice, which affects resource distribution based on the dice roll outcome.
- `void trade(Player& other, ResourceType give, ResourceType receive, int giveAmount, int receiveAmount)`: Trades resources with another player.
- `void buyDevelopmentCard()`: Buys a development card for the player.
- `void useDevelopmentCard(Catan& game, DevelopmentCardType card)`: Uses a development card of the specified type.
- `void placeCity(Board& board, Point2D location)`: Upgrades a settlement to a city at the specified location.
- `void showAllResources()`: Displays all resources the player currently has.
- `void printPoints()`: Prints the player's current points.
- `void endTurn()`: Ends the player's turn.

### Board Class

- `void printBoard()`: Prints the current state of the board.
- `void printLayout()`: Prints the layout of the board.

### Catan Class

- `Catan(Player& p1, Player& p2, Player& p3)`: Initializes the game with the given players.
- `Board getBoard()`: Returns the current game board.
- `void ChooseStartingPlayer()`: Chooses and prints the starting player.
- `void printWinner()`: Determines and prints the winner of the game.
