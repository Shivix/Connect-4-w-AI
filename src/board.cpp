#include <iostream>
#include <cmath>
#include "../include/board.hpp"


void board::calculateScore(){// - for yellow and + for red
    if(groupCount > 0 && groupType != counter::both){
        int groupScore = static_cast<int>(pow(groupCount, 4));

        if(groupCount == BOARD_CONNECT){
            groupScore = WINNING_SCORE;
            gameWon = true;
        }

        if(groupType == counter::yellow){
            groupScore = -groupScore;
        }
        evaluation += groupScore;
    }
}

void board::draw() const{
    for (auto i = 0; i < BOARD_WIDTH; ++i){
        std::cout << " " << i;
    }
    std::cout << " \n";
    for(auto&& i: boardArray){
        for(auto&& boardSlot: i){
            std::cout << "|";
            switch(boardSlot){
                case counter::empty: std::cout << " "; break;
                case counter::red: std::cout << "R"; break;
                case counter::yellow: std::cout << "Y"; break;
                case counter::both: std::cout << "B"; break;
            }
        }
        std::cout << "|\n";
    }
    std::cout << "|";
    for(auto baseIter = 0; baseIter < BOARD_WIDTH * 2 - 1; ++baseIter){
        std::cout << "=";
    }
    std::cout << "|\n";

    std::cout << "/";
    for(auto feetIter = 0; feetIter < BOARD_WIDTH * 2 - 1; ++feetIter){
        std::cout << " ";
    }
    std::cout << "\\\n";
}

bool board::applyMove(int movePos){
    if(movePos >= BOARD_WIDTH){
        return false;
    }
    int emptySlot; // track which slot of the board is empty
    for(emptySlot = 0; emptySlot < BOARD_HEIGHT; ++emptySlot){
        if(boardArray[emptySlot][movePos] != counter::empty){
            break;
        }
    }
    if(emptySlot == 0){
        return false;
    }
    --emptySlot;
    boardArray[emptySlot][movePos] = getTurn();
    return true;
}

int board::evaluateBoard(){
    evaluation = 0;
    gameWon = false;
    // loop through all game positions
    for(int heightIter = 0; heightIter < BOARD_HEIGHT; ++heightIter){
        for(int widthIter = 0; widthIter < BOARD_WIDTH; ++widthIter){
            //                          check for east connect
            if((widthIter + BOARD_CONNECT - 1) < BOARD_WIDTH){ // if test area is not within board, skip
                groupCount = 0; // reset group count
                groupType = counter::empty;
                for(int emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){
                    if(boardArray[(heightIter)][(widthIter + emptyCounter)] != counter::empty){ // if test area is not empty, skip
                        ++groupCount;

                        if(groupType == counter::empty){
                            if(boardArray[heightIter][widthIter + emptyCounter] == counter::red){
                                groupType = counter::red;
                            }
                            else{
                                groupType = counter::yellow;
                            }
                        }
                        else{
                            if((groupType == counter::red && boardArray[heightIter][widthIter + emptyCounter] == counter::yellow)
                               ||(groupType == counter::yellow && boardArray[heightIter][widthIter + emptyCounter] == counter::red)){
                                groupType = counter::both;
                            }
                        }
                    }
                }
                calculateScore();
            }
            //                                                  check for south connect
            if((heightIter + BOARD_CONNECT - 1) < BOARD_HEIGHT){
                groupCount = 0;
                groupType = counter::empty;
                for(auto emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){
                    if(boardArray[heightIter + emptyCounter][widthIter] != counter::empty){
                        ++groupCount;

                        if(groupType == counter::empty){
                            if(boardArray[heightIter + emptyCounter][widthIter] == counter::red){
                                groupType = counter::red;
                            }
                            else{
                                groupType = counter::yellow;
                            }
                        }
                        else{
                            if((groupType == counter::red && this->boardArray[heightIter + emptyCounter][widthIter] == counter::yellow)
                               ||(groupType == counter::yellow && this->boardArray[heightIter + emptyCounter][widthIter] == counter::red)){
                                groupType = counter::both;
                            }
                        }
                    }
                }
                calculateScore();
            }
            //                                      check for south east connect                                     
            if(((heightIter + BOARD_CONNECT - 1) < BOARD_HEIGHT) && ((widthIter + BOARD_CONNECT - 1) < BOARD_WIDTH)){

                groupCount = 0;
                groupType = counter::empty;
                for(auto emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){

                    if(boardArray[heightIter + emptyCounter][widthIter + emptyCounter] != counter::empty){     // if test area is not empty, skip
                        ++groupCount;

                        if(groupType == counter::empty){
                            if(boardArray[heightIter + emptyCounter][widthIter + emptyCounter] == counter::red){
                                groupType = counter::red;
                            }
                            else{
                                groupType = counter::yellow;
                            }
                        }
                        else{
                            if((groupType == counter::red && this->boardArray[heightIter + emptyCounter][widthIter + emptyCounter] == counter::yellow)
                               ||(groupType == counter::yellow && this->boardArray[heightIter + emptyCounter][widthIter + emptyCounter] == counter::red)){
                                groupType = counter::both;
                            }
                        }
                    }
                }
                calculateScore();
            }
            //                                          check for south west connect                                                
            if(((heightIter + BOARD_CONNECT - 1) < BOARD_HEIGHT) && ((widthIter - BOARD_CONNECT + 1) >= 0)){
                groupCount = 0;
                groupType = counter::empty;
                for(auto emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){
                    // if test area is not empty, skip
                    if(boardArray[heightIter + emptyCounter][widthIter + -emptyCounter] != counter::empty){
                        ++groupCount;

                        if(groupType == counter::empty){
                            if(boardArray[heightIter + emptyCounter][widthIter + -emptyCounter] == counter::red){
                                groupType = counter::red;
                            }
                            else{
                                groupType = counter::yellow;
                            }
                        }
                        else{
                            if((groupType == counter::red && this->boardArray[heightIter + emptyCounter][widthIter + -emptyCounter] == counter::yellow)
                               ||(groupType == counter::yellow && this->boardArray[heightIter + emptyCounter][widthIter + -emptyCounter] == counter::red)){
                                groupType = counter::both;
                            }
                        }
                    }
                }
                calculateScore();
            }
        }
    }
    //                  Check if game won                   
    if(gameWon){
        if(evaluation > 0){
            evaluation = WINNING_SCORE; // ensures the evaluation of a winning move is always prioritized over other moves
        }
        else{
            evaluation = -WINNING_SCORE;
        }
    }
    return evaluation;
}

void board::switchTurn(){ // switch between the red and yellow player's turn
    if(turn == counter::red){
        turn = counter::yellow;
    }
    else{
        turn = counter::red;
    }
}

board::counter board::getTurn(){
    return turn;
}
