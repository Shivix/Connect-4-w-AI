#ifndef CONNECT4_OPPONENT_HPP
#define CONNECT4_OPPONENT_HPP

class board;

class opponent{
public:
    opponent();
    opponent(int);
    
    int miniMax(board gameBoard, int depth, int depthPos, bool isRed, int alpha, int beta);
    [[nodiscard]] int getSearchDepth() const noexcept;
private:
    int searchDepth = -1;
    int setSearchDepth();
};


#endif //CONNECT4_OPPONENT_HPP
