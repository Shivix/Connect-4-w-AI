#ifndef CONNECT4_BOARD_HPP
#define CONNECT4_BOARD_HPP

#include <vector>

#define BOARD_WIDTH  7
#define BOARD_HEIGHT 6 // size of board
#define BOARD_CONNECT 4 // how many to connect for a win

#define WINNING_SCORE 1000000 // the score given for connecting 4, may need to adjust to ensure connecting 4 is always the optimal move

#define SEARCH_DEPTH 8 // how many turns the program will look ahead when figuring out the best move

class board{
public:
    enum counter {
        red = 0,
        yellow,
        empty,
        both
    };
    std::vector<std::vector<int>> boardVec;
    std::vector<int> emptyGameRow;
    
public:
    board();
    ~board();
    void draw();
    bool applyMove(int move, bool isRed);
    int evaluateBoard();
};


#endif //CONNECT4_BOARD_HPP
