# Connect 4 w/ Minimax

A connect 4 game with an AI using the Minimax decision rule with alpha beta pruning for efficiency.

## Usage

The AI will look a set amount of turns ahead which will be set at the start of the program.

Once it asks for your move you can type in a number between 0 and 6 to choose which column to place 
the counter in. (each column will be labeled)

The game will end once their are 4 connecting counters of the same colour.

## MiniMax

A decision rule that minimizes the possible loss for a worst case scenario.
It calculates the highest value that the player can be sure to get without knowing the 
actions of the other players; equivalently, it is the lowest value the other players can 
force the player to receive when they know the player's action.

This was used  to look a varied amount of turns ahead and figure out the best move in connect 4.

### Alpha-beta pruning

Reduces the number of nodes that must be evaluated by the Minimax algorithm by 'Pruning'
parts of it's search tree. It prunes once a move has been found that proves the branch 
is worse than the previous.

## Authors

* **Mark Oborne** - [Shivix](https://github.com/Shivix)
* **James Rogers** - [Jamesrogers221194](https://github.com/Jamesrogers221194)