#include <iostream>
#include "../include/opponent.hpp"


opponent::opponent() = default;

int opponent::miniMax(board gameBoard, int depth, int depthPos, bool isRed, int alpha, int beta){ // uses multiple parameters for use with recursion
    if(depthPos == 0){
        return gameBoard.evaluateBoard();

    }
    if(isRed){
        int maxEvaluation = -WINNING_SCORE;
        int bestMove = -1;
        for(int moveCounter = 0; moveCounter < board::BOARD_WIDTH; ++moveCounter){
            board testBoard;
            testBoard = gameBoard;
            if (testBoard.applyMove(moveCounter, isRed)){

                if (testBoard.evaluateBoard() == WINNING_SCORE){  // check if won (no need to look further if it can win)
                    maxEvaluation = WINNING_SCORE;
                    bestMove = moveCounter;
                    break;
                }

                int evaluation = miniMax(testBoard, depth, depthPos - 1, false, alpha, beta);
                if(evaluation >= maxEvaluation){
                    maxEvaluation = evaluation;
                    bestMove = moveCounter;
                }
                alpha = std::max(alpha, evaluation);
            }

            if(beta < alpha){
                break;
            }
        }
        if(depthPos == depth){
            if (bestMove == -1){
                std::cout << "ERROR: BEST MOVE NOT SET\n";
                return -1;
            }
            else{
                return bestMove;
            }
        }
        else{
            return maxEvaluation;
        }
    }
    else{
        int minEval = WINNING_SCORE;
        int bestMove = -1;
        for(auto moveCounter = 0; moveCounter < board::BOARD_WIDTH; ++moveCounter){
            board testBoard;
            testBoard = gameBoard;
            if (testBoard.applyMove(moveCounter, isRed)){
                if (testBoard.evaluateBoard() == WINNING_SCORE){
                    minEval = -WINNING_SCORE;
                    bestMove = moveCounter;
                    break;
                }
                else{
                    int Eval = miniMax(testBoard, depth, depthPos - 1, true, alpha, beta);
                    if(Eval <= minEval){
                        minEval = Eval;
                        bestMove = moveCounter;
                    }
                    beta = std::min(beta, Eval);
                }
                if(beta < alpha){
                    break;
                }
            }
        }
        if(depthPos == depth){
            if (bestMove == -1){
                std::cout << "ERROR: BEST MOVE NOT SET\n";
                return -1;
            }
            else{
                return bestMove;
            }
        }
        else{
            return minEval;
        }
    }
}

void opponent::setSearchDepth(){
    std::cout << "Please type how many turns you would like the AI to look ahead:";
    std::cin.exceptions(std::ios_base::failbit);
    try{
        std::cin >> searchDepth;
        if(std::cin.gcount() >= 1){
            throw std::invalid_argument("More than one number");
        }
        if(searchDepth <= 0){
            throw std::invalid_argument("Less than 0");
        }
    }
    catch(...) {
        std::cout << "Incorrect value for search depth" << std::endl;
        setSearchDepth();
    }
}

