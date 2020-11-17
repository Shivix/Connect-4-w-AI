#include <iostream>
#include "../include/opponent.hpp"
#include "../include/board.hpp"

opponent::opponent():
searchDepth(setSearchDepth())
{}
[[maybe_unused]] opponent::opponent(int searchDepth):
        searchDepth(searchDepth)
{}

int opponent::evaluateMove(board gameBoard, int depthPos){ // uses multiple parameters for use with recursion
    if(depthPos == 0){
        return gameBoard.evaluateBoard();
    }
    return minimax(gameBoard, depthPos, gameBoard.getTurn() == board::counter::red);
}

int opponent::getSearchDepth() const noexcept {
    return searchDepth;
}

int opponent::setSearchDepth(){
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
    catch(std::exception& exception) {
        std::cout << exception.what() << std::endl;
        setSearchDepth();
    }
    return searchDepth;
}

int opponent::minimax(board gameBoard, int depthPos, bool isMax){
    int maxEvaluation = isMax ? -WINNING_SCORE : WINNING_SCORE;
    int bestMove = -1;
    for(int moveCounter = 0; moveCounter < board::BOARD_WIDTH; ++moveCounter){
        auto testBoard = board(board::counter::yellow);
        testBoard = gameBoard;
        if (testBoard.applyMove(moveCounter)){
            if (testBoard.evaluateBoard() == WINNING_SCORE){  // check if won (no need to look further if it can win)
                maxEvaluation = isMax ? WINNING_SCORE : -WINNING_SCORE;
                bestMove = moveCounter;
                break;
            }
            int evaluation = evaluateMove(testBoard, depthPos - 1);
            if (isMax){
                if(evaluation >= maxEvaluation){
                    maxEvaluation = evaluation;
                    bestMove = moveCounter;
                }
                alpha = std::max(alpha, evaluation);
            }
            else{
                if(evaluation <= maxEvaluation){
                    maxEvaluation = evaluation;
                    bestMove = moveCounter;
                }
                beta = std::min(beta, evaluation);
            }
        }
        if(beta < alpha){
            break;
        }
    }
    if(depthPos == getSearchDepth()){
        if (bestMove == -1){
            throw std::runtime_error("ERROR: BEST MOVE NOT SET\n");
        }
        else{
            return bestMove;
        }
    }
    else{
        return maxEvaluation;
    }
}
