#ifndef CONNECT4_OPPONENT_HPP
#define CONNECT4_OPPONENT_HPP

#include "board.hpp"

class opponent{
public:
    opponent();
    
int searchDepth = -1;

    int miniMax(board gameBoard, int depth, int depthPos, bool isRed, int alpha, int beta);
    void setSearchDepth();
};


#endif //CONNECT4_OPPONENT_HPP
