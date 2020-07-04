#ifndef CONNECT4_BOARD_HPP
#define CONNECT4_BOARD_HPP

#include <array>

#define BOARD_WIDTH  7
#define BOARD_HEIGHT 6 // size of board
#define BOARD_CONNECT 4 // how many to connect for a win

#define WINNING_SCORE 1000000 // the score given for connecting 4, may need to adjust to ensure connecting 4 is always the optimal move

class board{
public:
    enum class counter {
        red = -1,
        yellow = 1,
        empty = 0,
        both = 2
    };
    std::array<std::array<counter, BOARD_WIDTH>, BOARD_HEIGHT> boardArray = {};
private:
    bool gameWon = false;
    int evaluation = 0;
    int groupCount = 0;
    counter groupType = counter::empty;
    
public:
    constexpr board(){
        for(auto&& i: boardArray){
            for(auto&& j: i){
                j = counter::empty;
            }
        }
    }
    bool applyMove(int move, bool isRed);
    void draw();
    int evaluateBoard();
private:
    void calculateScore();
};


#endif //CONNECT4_BOARD_HPP
