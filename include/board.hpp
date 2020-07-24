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
    counter turn = counter::red; // tracks who's turn it is
    
public:
    constexpr board(){
        for(auto&& i: boardArray){
            i.fill(counter::empty);
        }
    }
    constexpr explicit board(counter turn):
    turn(turn)
    {
        for(auto&& i: boardArray){
            i.fill(counter::empty);
        }
    }
    bool applyMove(int move);
    void draw() const; // outputs the board state in console
    int evaluateBoard(); // returns a score based on connections of the same colour
    void switchTurn();
    counter getTurn();
private:
    void calculateScore();
};


#endif //CONNECT4_BOARD_HPP
