#include <iostream>
#include "../include/board.hpp"
#include "../include/opponent.hpp"

int main()
{
    board gameBoard;
    opponent opponent;
    std::cout << "Welcome to Connect 4. ";
    std::cout << "The AI will look " << opponent.getSearchDepth() << " turns ahead. Good luck!" << std::endl;
    gameBoard.draw();
    int move = -1;
        while(true){
            //                            Input Move                                  
            if(gameBoard.getTurn() == board::counter::red){
                std::cout << "type your move: ";
                while(true){
                    try{
                        std::cin.clear();
                        std::cin >> move; // type the number of the column you want to drop a piece into (left most is column 0)
                        if(move > board::BOARD_WIDTH - 1 || move < 0){
                            throw std::invalid_argument("Bad input");
                        }
                        else{
                            break;
                        }
                    }
                    catch(std::invalid_argument&){
                        std::cout << "Incorrect input, please type a number between 0 and " << board::BOARD_WIDTH - 1 << "\n";
                    }
                }
            }
            else{
                std::cout << "Computers turn:";
                
                //                                       minimax move                       
                opponent.alpha = -WINNING_SCORE;
                opponent.beta = WINNING_SCORE;
                move = opponent.evaluateMove(gameBoard, opponent.getSearchDepth());
                std::cout << move << "\n";
            }

            gameBoard.applyMove(move);
            gameBoard.draw();
            
            std::cout << "This board has a score of: " << gameBoard.evaluateBoard() << std::endl;
            
            gameBoard.switchTurn();
            
            if(gameBoard.evaluateBoard() == WINNING_SCORE){
                std::cout << "Red Wins!";
                break;
            }
            else if(gameBoard.evaluateBoard() == -WINNING_SCORE){
                std::cout << "Yellow Wins!";
                break;
            }
        }
    return 0;
}
