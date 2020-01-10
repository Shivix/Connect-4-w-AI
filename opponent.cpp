#include <iostream>
#include <cmath>
#include "opponent.hpp"


opponent::opponent() = default;

opponent::~opponent() = default;

int opponent::miniMax(const board& gameBoard, int depth, int depthPos, bool isRed, int alpha, int beta){ // uses multiple parameters for use with recursion
    if(depthPos == 0){
        return evaluateBoard(gameBoard);

    }
    if(isRed){
        int maxEvaluation = -WINNING_SCORE;
        int bestMove = -1;
        for(int moveCounter = 0; moveCounter < BOARD_WIDTH; ++moveCounter){
            board testBoard;
            testBoard = gameBoard;
            if (testBoard.applyMove(moveCounter, isRed)){

                if (evaluateBoard(testBoard) == WINNING_SCORE){  // check if won (no need to look further if it can win)
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
        for(auto moveCounter = 0; moveCounter < BOARD_WIDTH; ++moveCounter){
            board testBoard;
            testBoard = gameBoard;
            if (testBoard.applyMove(moveCounter, isRed)){
                if (evaluateBoard(testBoard) == WINNING_SCORE){
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
                    beta=std::min(beta, Eval);
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

int opponent::evaluateBoard(board board){
    int evaluation = 0;
    bool gameWon = false;

    // loop through all game positions
    for(int heightCounter = 0; heightCounter < BOARD_HEIGHT; ++heightCounter){
        for(int widthCounter = 0; widthCounter < BOARD_WIDTH; ++widthCounter){
            //                          check for east connect                          

            // if test area is not within board, skip

            if((widthCounter + BOARD_CONNECT - 1) < BOARD_WIDTH){

                int groupCount = 0;
                int groupType = board::empty;
                for(int emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){
                    if(board.boardVec[(heightCounter)][(widthCounter + emptyCounter)] != board::empty){ // if test area is not empty, skip
                        ++groupCount;

                        if(groupType == board::empty){
                            if(board.boardVec[heightCounter][widthCounter + emptyCounter] == board::red){
                                groupType = board::red;
                            }
                            else{
                                groupType = board::yellow;
                            }
                        }
                        else{
                            if((groupType == board::red && board.boardVec[heightCounter][widthCounter + emptyCounter] == board::yellow)
                               ||(groupType == board::yellow && board.boardVec[heightCounter][widthCounter + emptyCounter] == board::red)){
                                groupType = board::both;
                            }
                        }
                    }
                }

                // calculate score (- for yellow + for red)

                if(groupCount > 0 && groupType != board::both){
                    int groupScore = static_cast<int>(pow(groupCount, 4));

                    if(groupCount == BOARD_CONNECT){
                        groupScore = WINNING_SCORE;
                        gameWon = true;
                    }

                    if(groupType == board::yellow){
                        groupScore = -groupScore;
                    }
                    evaluation += groupScore;
                }
            }

            //                                                  check for south connect                                                                

            if((heightCounter + BOARD_CONNECT - 1) < BOARD_HEIGHT){

                int groupCount = 0;
                int groupType = board::empty;
                for(auto emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){
                    // if test area is not empty, skip
                    if(board.boardVec[heightCounter + emptyCounter][widthCounter] != board::empty){
                        ++groupCount;

                        if(groupType == board::empty){
                            if(board.boardVec[heightCounter + emptyCounter][widthCounter] == board::red){
                                groupType = board::red;
                            }
                            else{
                                groupType = board::yellow;
                            }
                        }
                        else{
                            if((groupType == board::red && board.boardVec[heightCounter + emptyCounter][widthCounter] == board::yellow)
                               ||(groupType == board::yellow && board.boardVec[heightCounter + emptyCounter][widthCounter] == board::red)){
                                groupType = board::both;
                            }
                        }
                    }
                }

                // calculate score (-for yellow + for red)

                if(groupCount > 0 && groupType != board::both){
                    int groupScore = static_cast<int>(pow(groupCount, 2));

                    if(groupCount == BOARD_CONNECT){
                        groupScore = WINNING_SCORE;
                        gameWon = true;
                    }

                    if(groupType == board::yellow){
                        groupScore = -groupScore;
                    }
                    evaluation += groupScore;
                }
            }

            //                                      check for south east connect                                     
            if(((heightCounter + BOARD_CONNECT - 1) < BOARD_HEIGHT) && ((widthCounter + BOARD_CONNECT - 1) < BOARD_WIDTH)){

                int groupCount = 0;
                int groupType = board::empty;
                for(auto emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){

                    if(board.boardVec[heightCounter + emptyCounter][widthCounter + emptyCounter] != board::empty){     // if test area is not empty, skip
                        ++groupCount;

                        if(groupType == board::empty){
                            if(board.boardVec[heightCounter + emptyCounter][widthCounter + emptyCounter] == board::red){
                                groupType = board::red;
                            }
                            else{
                                groupType = board::yellow;
                            }
                        }
                        else{
                            if((groupType == board::red && board.boardVec[heightCounter + emptyCounter][widthCounter + emptyCounter] == board::yellow)
                               ||(groupType == board::yellow && board.boardVec[heightCounter + emptyCounter][widthCounter + emptyCounter] == board::red)){
                                groupType = board::both;
                            }
                        }
                    }
                }

                // calculate score (-for yellow + for red)

                if(groupCount > 0 && groupType != board::both){
                    int groupScore = static_cast<int>(pow(groupCount, 2));

                    if(groupCount == BOARD_CONNECT){
                        groupScore = WINNING_SCORE;
                        gameWon = true;
                    }

                    if(groupType == board::yellow){
                        groupScore = -groupScore;
                    }
                    evaluation += groupScore;
                }
            }
            //                                          check for south west connect                                                
            if(((heightCounter + BOARD_CONNECT - 1) < BOARD_HEIGHT) && ((widthCounter - BOARD_CONNECT + 1) >= 0)){

                int groupCount = 0;
                int groupType = board::empty;
                for(auto emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){
                    // if test area is not empty, skip
                    if(board.boardVec[heightCounter + emptyCounter][widthCounter + -emptyCounter] != board::empty){
                        ++groupCount;

                        if(groupType == board::empty){
                            if(board.boardVec[heightCounter + emptyCounter][widthCounter + -emptyCounter] == board::red){
                                groupType = board::red;
                            }
                            else{
                                groupType = board::yellow;
                            }
                        }
                        else{
                            if((groupType == board::red && board.boardVec[heightCounter + emptyCounter][widthCounter + -emptyCounter] == board::yellow)
                               ||(groupType == board::yellow && board.boardVec[heightCounter + emptyCounter][widthCounter + -emptyCounter] == board::red)){
                                groupType = board::both;
                            }
                        }
                    }
                }

                // calculate score (-for yellow + for red)

                if(groupCount > 0 && groupType != board::both){
                    int groupScore = static_cast<int>(pow(groupCount, 2));

                    if(groupCount == BOARD_CONNECT){
                        groupScore = WINNING_SCORE;
                        gameWon = true;
                    }

                    if(groupType == board::yellow){
                        groupScore = -groupScore;
                    }
                    evaluation += groupScore;
                }
            }
        }
    }

    //                  Check if game won                   
    if(gameWon){
        if(evaluation > 0){
            evaluation = WINNING_SCORE;
        }
        else{
            evaluation = -WINNING_SCORE;
        }
    }
    return evaluation;
}
