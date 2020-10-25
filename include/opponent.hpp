#ifndef CONNECT4_OPPONENT_HPP
#define CONNECT4_OPPONENT_HPP

#include <climits>

class board;

class opponent{
public:
    opponent();
    explicit opponent(int);
    
    int evaluateMove(board, int);
    [[nodiscard]] int getSearchDepth() const noexcept;
    int alpha = -INT_MAX;
    int beta = INT_MAX;
private:
    int searchDepth = -1;
    int setSearchDepth();
    int minimax(board, int, bool);
};


#endif //CONNECT4_OPPONENT_HPP
