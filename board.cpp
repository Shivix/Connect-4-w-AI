#include <iostream>
#include "board.hpp"
board::board(){
    emptyGameRow.reserve(BOARD_WIDTH);
    for(int i = 0; i < BOARD_WIDTH; i++){
        emptyGameRow.push_back(empty);
    }
    boardVec.reserve(BOARD_HEIGHT);
    for(int i = 0; i < BOARD_HEIGHT; i++){
        boardVec.push_back(emptyGameRow);
    }
}

board::~board() = default;

void board::draw(){
    for (auto i = 0; i < BOARD_WIDTH; ++i){
        std::cout << " " << i;
    }
    std::cout << " \n";
    for(auto heightCounter = 0; heightCounter < BOARD_HEIGHT; ++heightCounter){
        for(auto widthCounter = 0; widthCounter < BOARD_WIDTH; ++widthCounter){
            std::cout << "|";
            switch(boardVec[heightCounter][widthCounter]){
                case empty: std::cout << " "; break;
                case red: std::cout << "R"; break;
                case yellow: std::cout << "Y"; break;
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
        if(boardVec[heightCounter][movePos] != empty){
            break;
        }
    }

    if(heightCounter == 0){
        return false;
    }
    --heightCounter;
    if(isRed){
        boardVec[heightCounter][movePos] = red;
    }
    else{
        boardVec[heightCounter][movePos] = yellow;
    }
    return true;
}






