#include <iostream>
#include "board.hpp"
#include "opponent.hpp"

int main()
{
    board gameBoard;
    opponent opponent;
    std::cout << "Welcome to Connect 4. Please type how many turns you would like the AI to look ahead:";
    std::cin >> opponent::searchDepth;
    gameBoard.draw();
    int move = -1;
    bool isRed = true;
        while(true){

            //                            Input Move                                  
            if(isRed){
                std::cout << "type your move: ";
                bool correctMove = false;
                while(!correctMove){
                    std::cin >> move; // type the number of the column you want to drop a piece into (left most is column 0)
                    if (move > BOARD_WIDTH - 1){
                        std::cout << "Incorrect input, please type a number between 0 and " << BOARD_WIDTH - 1 << "\n";
                    }
                    else{
                        correctMove = true;
                    }
                }
            }
            else{
                std::cout << "Computers turn:";
                
                //                                       minimax move                       
                int alpha = -WINNING_SCORE;
                int beta = WINNING_SCORE;
                move = opponent.miniMax(gameBoard, opponent::searchDepth, opponent::searchDepth, false, alpha, beta);
                std::cout << move << "\n";
            }

            gameBoard.applyMove(move, isRed);
            gameBoard.draw();
            
            std::cout << "This board has a score of: " << gameBoard.evaluateBoard() << std::endl;
            
            isRed = !isRed;
            
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
