#ifndef CONNECT4_OPPONENT_HPP
#define CONNECT4_OPPONENT_HPP

#include "board.hpp"

class opponent{
public:
    opponent();
    
    ~opponent();
    

private:

public:
    int miniMax(board gameBoard, int depth, int depthPos, bool isRed, int alpha, int beta); 

};


#endif //CONNECT4_OPPONENT_HPP
