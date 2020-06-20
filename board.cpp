#include <iostream>
#include <cmath>
#include "board.hpp"

board::board(){
    emptyGameRow.reserve(BOARD_WIDTH);
    for(int i = 0; i < BOARD_WIDTH; i++){
        emptyGameRow.push_back(counter::empty);
    }
    boardVec.reserve(BOARD_HEIGHT);
    for(int i = 0; i < BOARD_HEIGHT; i++){
        boardVec.push_back(emptyGameRow);
    }
}

board::~board() = default;

void board::calculatescore(){// - for yellow and + for red

    if(groupCount > 0 && groupType != board::counter::both){
        int groupScore = static_cast<int>(pow(groupCount, 4));

        if(groupCount == BOARD_CONNECT){
            groupScore = WINNING_SCORE;
            gameWon = true;
        }

        if(groupType == board::counter::yellow){
            groupScore = -groupScore;
        }
        evaluation += groupScore;
    }
}

void board::draw(){
    for (auto i = 0; i < BOARD_WIDTH; ++i){
        std::cout << " " << i;
    }
    std::cout << " \n";
    for(auto heightCounter = 0; heightCounter < BOARD_HEIGHT; ++heightCounter){
        for(auto widthCounter = 0; widthCounter < BOARD_WIDTH; ++widthCounter){
            std::cout << "|";
            switch(boardVec[heightCounter][widthCounter]){
                case counter::empty: std::cout << " "; break;
                case counter::red: std::cout << "R"; break;
                case counter::yellow: std::cout << "Y"; break;
                case counter::both: std::cout << "B"; break;
            }
        }
        std::cout << "|\n";
    }
    std::cout << "|";
    for(auto baseCounter = 0; baseCounter < BOARD_WIDTH * 2 - 1; ++baseCounter){
        std::cout << "=";
    }
    std::cout << "|\n";

    std::cout << "/";
    for(auto feetCounter = 0; feetCounter < BOARD_WIDTH * 2 - 1; ++feetCounter){
        std::cout << " ";
    }
    std::cout << "\\\n";
}

bool board::applyMove(int movePos, bool isRed){
    if(movePos >= BOARD_WIDTH){
        return false;
    }
    int heightCounter = 0;
    for(heightCounter = 0; heightCounter < BOARD_HEIGHT; ++heightCounter){
        if(boardVec[heightCounter][movePos] != counter::empty){
            break;
        }
    }
    if(heightCounter == 0){
        return false;
    }
    --heightCounter;
    if(isRed){
        boardVec[heightCounter][movePos] = counter::red;
    }
    else{
        boardVec[heightCounter][movePos] = counter::yellow;
    }
    return true;
}

int board::evaluateBoard(){
    evaluation = 0;
    gameWon = false;
    // loop through all game positions
    for(int heightCounter = 0; heightCounter < BOARD_HEIGHT; ++heightCounter){
        for(int widthCounter = 0; widthCounter < BOARD_WIDTH; ++widthCounter){
            //                          check for east connect
            if((widthCounter + BOARD_CONNECT - 1) < BOARD_WIDTH){ // if test area is not within board, skip
                groupCount = 0; // reset group count
                groupType = board::counter::empty;
                for(int emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){
                    if(boardVec[(heightCounter)][(widthCounter + emptyCounter)] != board::counter::empty){ // if test area is not empty, skip
                        ++groupCount;

                        if(groupType == board::counter::empty){
                            if(boardVec[heightCounter][widthCounter + emptyCounter] == board::counter::red){
                                groupType = board::counter::red;
                            }
                            else{
                                groupType = board::counter::yellow;
                            }
                        }
                        else{
                            if((groupType == board::counter::red && boardVec[heightCounter][widthCounter + emptyCounter] == board::counter::yellow)
                               ||(groupType == board::counter::yellow && boardVec[heightCounter][widthCounter + emptyCounter] == board::counter::red)){
                                groupType = board::counter::both;
                            }
                        }
                    }
                }
                calculatescore();
            }
            //                                                  check for south connect
            if((heightCounter + BOARD_CONNECT - 1) < BOARD_HEIGHT){
                groupCount = 0;
                groupType = board::counter::empty;
                for(auto emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){
                    if(boardVec[heightCounter + emptyCounter][widthCounter] != board::counter::empty){
                        ++groupCount;

                        if(groupType == board::counter::empty){
                            if(boardVec[heightCounter + emptyCounter][widthCounter] == board::counter::red){
                                groupType = board::counter::red;
                            }
                            else{
                                groupType = board::counter::yellow;
                            }
                        }
                        else{
                            if((groupType == board::counter::red && this->boardVec[heightCounter + emptyCounter][widthCounter] == board::counter::yellow)
                               ||(groupType == board::counter::yellow && this->boardVec[heightCounter + emptyCounter][widthCounter] == board::counter::red)){
                                groupType = board::counter::both;
                            }
                        }
                    }
                }
                calculatescore();
            }
            //                                      check for south east connect                                     
            if(((heightCounter + BOARD_CONNECT - 1) < BOARD_HEIGHT) && ((widthCounter + BOARD_CONNECT - 1) < BOARD_WIDTH)){

                groupCount = 0;
                groupType = board::counter::empty;
                for(auto emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){

                    if(boardVec[heightCounter + emptyCounter][widthCounter + emptyCounter] != board::counter::empty){     // if test area is not empty, skip
                        ++groupCount;

                        if(groupType == board::counter::empty){
                            if(boardVec[heightCounter + emptyCounter][widthCounter + emptyCounter] == board::counter::red){
                                groupType = board::counter::red;
                            }
                            else{
                                groupType = board::counter::yellow;
                            }
                        }
                        else{
                            if((groupType == board::counter::red && this->boardVec[heightCounter + emptyCounter][widthCounter + emptyCounter] == board::counter::yellow)
                               ||(groupType == board::counter::yellow && this->boardVec[heightCounter + emptyCounter][widthCounter + emptyCounter] == board::counter::red)){
                                groupType = board::counter::both;
                            }
                        }
                    }
                }
                calculatescore();
            }
            //                                          check for south west connect                                                
            if(((heightCounter + BOARD_CONNECT - 1) < BOARD_HEIGHT) && ((widthCounter - BOARD_CONNECT + 1) >= 0)){
                groupCount = 0;
                groupType = board::counter::empty;
                for(auto emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){
                    // if test area is not empty, skip
                    if(boardVec[heightCounter + emptyCounter][widthCounter + -emptyCounter] != board::counter::empty){
                        ++groupCount;

                        if(groupType == board::counter::empty){
                            if(boardVec[heightCounter + emptyCounter][widthCounter + -emptyCounter] == board::counter::red){
                                groupType = board::counter::red;
                            }
                            else{
                                groupType = board::counter::yellow;
                            }
                        }
                        else{
                            if((groupType == board::counter::red && this->boardVec[heightCounter + emptyCounter][widthCounter + -emptyCounter] == board::counter::yellow)
                               ||(groupType == board::counter::yellow && this->boardVec[heightCounter + emptyCounter][widthCounter + -emptyCounter] == board::counter::red)){
                                groupType = board::counter::both;
                            }
                        }
                    }
                }
                calculatescore();
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
