#ifndef CONNECT4_BOARD_HPP
#define CONNECT4_BOARD_HPP

#include <array>

#define WINNING_SCORE INT_MAX // the score given for connecting 4, may need to adjust to ensure connecting 4 is always the optimal move

class board{
public:
    enum class counter {
        red = -1,
        yellow = 1,
        empty = 0,
        both = 2
    };
    static constexpr auto BOARD_WIDTH = 7;
    static constexpr auto BOARD_HEIGHT = 6; // size of board
    static constexpr auto BOARD_CONNECT = 4; // how many to connect for a win
    std::array<std::array<counter, BOARD_WIDTH>, BOARD_HEIGHT> boardArray = {};
private:
    bool gameWon = false;
    int evaluation = 0; // score given to the board based on connections of the same colour
    int groupCount = 0; // amount of the same colour counters in a row
    counter groupType = counter::empty; // used to keep track of the counter colour it's evaluating
    
public:
    constexpr inline board(){
        for(auto&& i: boardArray){
            for(auto&& j: i){
                j = counter::empty;
            }
        }
    }
    bool applyMove(int move, bool isRed);
    void draw(); // outputs the board state in console
    int evaluateBoard(); // returns a score based on connections of the same colour
private:
    void calculateScore();
};


#endif //CONNECT4_BOARD_HPP
