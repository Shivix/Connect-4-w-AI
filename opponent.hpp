#ifndef CONNECT4_OPPONENT_HPP
#define CONNECT4_OPPONENT_HPP

#include <vector>
#include "board.hpp"

class opponent{
public:
    opponent();
    
    ~opponent();
    

private:

public:
    int miniMax(const board& gameBoard, int depth, int depthPos, bool isRed, int alpha, int beta); 
    int evaluateBoard(board board);
};


#endif //CONNECT4_OPPONENT_HPP
