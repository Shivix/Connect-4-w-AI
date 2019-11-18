#include <iostream>
#include <vector>
#include <cmath>


#define BOARD_WIDTH  7 
#define BOARD_HEIGHT 6 // size of board
#define BOARD_CONNECT 4 // how many to connect for a win

#define STATE_RED    0
#define STATE_YELLOW 1
#define STATE_EMPTY  2

#define COLOUR_RED 0
#define COLOUR_YELLOW 1
#define COLOUR_UNKNOWN 2
#define COLOUR_BOTH 3

#define WINNING_SCORE 1000000 // the score given for connecting 4, may need to adjust to ensure connecting 4 is always the optimal move

#define SEARCH_DEPTH 8 // how many turns the program will look ahead when figuring out the best move

void drawGameBoard(std::vector<std::vector<int>> gameBoard);
bool applyMove(std::vector<std::vector<int>> &gameBoard, bool isRed, int movePosition);
int evaluateBoard(std::vector<std::vector<int>> gameBoard);
int evaluateGroup(int pieceCount);
int miniMax(const std::vector<std::vector<int>>& gameBoard, int depth, int depthPos, bool isRed, int alpha, int beta);

int main()
{
    std::vector<std::vector<int>> gameBoard;
    std::vector<int> emptyGameRow;    
    
    emptyGameRow.reserve(BOARD_WIDTH);
    for(int i = 0; i < BOARD_WIDTH; i++){
        emptyGameRow.push_back(STATE_EMPTY);                                              
    }
    
    gameBoard.reserve(BOARD_HEIGHT);
    for(int i = 0; i < BOARD_HEIGHT; i++){
        gameBoard.push_back(emptyGameRow);                                              
    }

    drawGameBoard(gameBoard);
    
    bool isRed = true;
        while(true){
            int move;
            bool correctMove = false;
            //                            Input Move                                  
            if(isRed){
                std::cout << "type your move: ";
                while(!correctMove){
                    std::cin >> move; // type the number of the column you want to drop a piece into (left most is column 0)
                    if (move > BOARD_WIDTH - 1){
                        std::cout << "Incorrect input, please type a number between 0 and " << BOARD_WIDTH - 1 << "\n";
                    }
                    else{
                        correctMove = true;
                    }
                }
            }
            else{
                std::cout << "Computers turn:";
                
                //                                       minimax move                               
                int alpha = -WINNING_SCORE;
                int beta = WINNING_SCORE;
                move = miniMax(gameBoard, SEARCH_DEPTH, SEARCH_DEPTH, false, alpha, beta);
                std::cout << move << "\n";
            }

            applyMove(gameBoard, isRed, move);
            drawGameBoard(gameBoard);
            
            std::cout << "This board has a score of: " << evaluateBoard(gameBoard) << std::endl;
            
            isRed = !isRed;
            
            if(evaluateBoard(gameBoard) == WINNING_SCORE){
                std::cout << "Red Wins!";
                break;
            }
            else if(evaluateBoard(gameBoard) == -WINNING_SCORE){
                std::cout << "Yellow Wins!";
                break;
            }
        }
    return 0;
}

int miniMax(const std::vector<std::vector<int>>& gameBoard, int depth, int depthPos, bool isRed, int alpha, int beta){
    if(depthPos == 0){
        return evaluateBoard(gameBoard);
        
    }
    if(isRed){
        int maxEvaluation = -WINNING_SCORE;
        int bestMove = -1;
        for(int moveCounter = 0; moveCounter < BOARD_WIDTH; ++moveCounter){
            std::vector<std::vector<int>> testBoard;
            testBoard = gameBoard;
            if (applyMove(testBoard, true, moveCounter)){

                if (evaluateBoard(testBoard) == WINNING_SCORE){  // check if won (no need to look further if it can win)
                    maxEvaluation = WINNING_SCORE;
                    bestMove = moveCounter;
                    break;
                }
                
                int evaluation = miniMax(testBoard, depth, depthPos - 1, false, alpha, beta);
                if(evaluation >= maxEvaluation){
                    maxEvaluation = evaluation;
                    bestMove = moveCounter;
                }
                alpha = std::max(alpha, evaluation);
            }
            
            if(beta < alpha){
                break;
            }
        }
        if(depthPos == depth){
            if (bestMove == -1){
                std::cout << "ERROR: BEST MOVE NOT SET\n";
                return -1;
            }
            else{
                return bestMove; 
            }
        }
        else{
            return maxEvaluation;
        }
    }
    else{
        int minEval = WINNING_SCORE;
        int bestMove = -1;
        for(auto moveCounter = 0; moveCounter < BOARD_WIDTH; ++moveCounter){
            std::vector<std::vector<int>> testBoard;
            testBoard = gameBoard;
            if (applyMove(testBoard, false, moveCounter)){
                if (evaluateBoard(testBoard) == WINNING_SCORE){
                    minEval = -WINNING_SCORE;
                    bestMove = moveCounter;
                    break;
                }
                else{
                    int Eval = miniMax(testBoard, depth, depthPos - 1, true, alpha, beta);
                    if(Eval <= minEval){
                        minEval = Eval;
                        bestMove = moveCounter;
                    }
                    beta=std::min(beta, Eval);
                }
                if(beta < alpha){
                    break;
                }
            }
        }
        if(depthPos == depth){
            if (bestMove == -1){
                std::cout << "ERROR: BEST MOVE NOT SET\n";
                return -1;
            }
            else{
                return bestMove;
            }
        }
        else{
            return minEval;
        }
    }
}


//                                              Evaluate Group Function                                            
int evaluateGroup(int pieceCount){
    return pow(pieceCount, 4);
}

//                                                 Board Evaluation Functions                                        
int evaluateBoard(std::vector<std::vector<int>> gameBoard){
    
    int evaluation = 0;
    bool gameWon = false;
    
    // loop through all game positions
    for(int heightCounter = 0; heightCounter < BOARD_HEIGHT; ++heightCounter){
        for(int widthCounter = 0; widthCounter < BOARD_WIDTH; ++widthCounter){
            //                          check for east connect                          
                
            // if test area is not within board, skip
            
            if((widthCounter + BOARD_CONNECT - 1) < BOARD_WIDTH){
                
                int groupCount = 0;
                int groupType = COLOUR_UNKNOWN;
                for(int emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){
                    if(gameBoard[(heightCounter)][(widthCounter + emptyCounter)] != STATE_EMPTY){ // if test area is not empty, skip
                        ++groupCount;
                        
                        if(groupType == COLOUR_UNKNOWN){
                            if(gameBoard[heightCounter][widthCounter + emptyCounter] == STATE_RED){
                                groupType = COLOUR_RED;
                            }
                            else{
                                groupType = COLOUR_YELLOW;
                            }
                        }
                        else{
                            if((groupType == COLOUR_RED && gameBoard[heightCounter][widthCounter + emptyCounter] == STATE_YELLOW)
                            ||(groupType == COLOUR_YELLOW && gameBoard[heightCounter][widthCounter + emptyCounter] == STATE_RED)){
                                groupType = COLOUR_BOTH;
                            }
                        }
                    }
                }
            
                // calculate score (- for yellow + for red)
                
                if(groupCount > 0 && groupType != COLOUR_BOTH){
                    int groupScore = static_cast<int>(evaluateGroup(groupCount));                                
                    
                    if(groupCount == BOARD_CONNECT){
                        groupScore = WINNING_SCORE;
                        gameWon = true;
                    }
                    
                    if(groupType == COLOUR_YELLOW){
                        groupScore = -groupScore;
                    }
                    evaluation += groupScore;
                }
            }
            
        //                                                  check for south connect                                                                
            
            if((heightCounter + BOARD_CONNECT - 1) < BOARD_HEIGHT){
                
                int groupCount = 0;
                int groupType = COLOUR_UNKNOWN;
                for(auto emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){
                    // if test area is not empty, skip
                    if(gameBoard[heightCounter + emptyCounter][widthCounter] != STATE_EMPTY){
                        ++groupCount;
                        
                        if(groupType == COLOUR_UNKNOWN){
                            if(gameBoard[heightCounter + emptyCounter][widthCounter] == STATE_RED){
                                groupType = COLOUR_RED;
                            }
                            else{
                                groupType = COLOUR_YELLOW;
                            }
                        }
                        else{
                            if((groupType == COLOUR_RED && gameBoard[heightCounter + emptyCounter][widthCounter] == STATE_YELLOW)
                            ||(groupType == COLOUR_YELLOW && gameBoard[heightCounter + emptyCounter][widthCounter] == STATE_RED)){
                                groupType = COLOUR_BOTH;
                            }
                        }
                    }
                }
                
            // calculate score (-for yellow + for red)
            
                if(groupCount > 0 && groupType != COLOUR_BOTH){
                    int groupScore = static_cast<int>(pow(groupCount, 2));                                
                    
                    if(groupCount == BOARD_CONNECT){
                        groupScore = WINNING_SCORE;
                        gameWon = true;
                    }
                    
                    if(groupType == COLOUR_YELLOW){
                        groupScore = -groupScore;
                    }
                    evaluation += groupScore;
                }
            }
            
            //                                      check for south east connect                                     
            if(((heightCounter + BOARD_CONNECT - 1) < BOARD_HEIGHT) && ((widthCounter + BOARD_CONNECT - 1) < BOARD_WIDTH)){
                
                int groupCount = 0;
                int groupType = COLOUR_UNKNOWN;
                for(auto emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){
                    
                    if(gameBoard[heightCounter + emptyCounter][widthCounter + emptyCounter] != STATE_EMPTY){     // if test area is not empty, skip
                        ++groupCount;
                        
                        if(groupType == COLOUR_UNKNOWN){
                            if(gameBoard[heightCounter + emptyCounter][widthCounter + emptyCounter] == STATE_RED){
                                groupType = COLOUR_RED;
                            }
                            else{
                                groupType = COLOUR_YELLOW;
                            }
                        }
                        else{
                            if((groupType == COLOUR_RED && gameBoard[heightCounter + emptyCounter][widthCounter + emptyCounter] == STATE_YELLOW)
                            ||(groupType == COLOUR_YELLOW && gameBoard[heightCounter + emptyCounter][widthCounter + emptyCounter] == STATE_RED)){
                                groupType = COLOUR_BOTH;
                            }
                        }
                    }
                }
                
            // calculate score (-for yellow + for red)
            
                if(groupCount > 0 && groupType != COLOUR_BOTH){
                    int groupScore = static_cast<int>(pow(groupCount, 2));                                
                    
                    if(groupCount == BOARD_CONNECT){
                        groupScore = WINNING_SCORE;
                        gameWon = true;
                    }
                    
                    if(groupType == COLOUR_YELLOW){
                        groupScore = -groupScore;
                    }
                    evaluation += groupScore;
                }
            }
            //                                          check for south west connect                                                
            if(((heightCounter + BOARD_CONNECT - 1) < BOARD_HEIGHT) && ((widthCounter - BOARD_CONNECT + 1) >= 0)){
                
                int groupCount = 0;
                int groupType = COLOUR_UNKNOWN;
                for(auto emptyCounter = 0; emptyCounter < BOARD_CONNECT; ++emptyCounter){
                    // if test area is not empty, skip
                    if(gameBoard[heightCounter + emptyCounter][widthCounter + -emptyCounter] != STATE_EMPTY){
                        ++groupCount;
                        
                        if(groupType == COLOUR_UNKNOWN){
                            if(gameBoard[heightCounter + emptyCounter][widthCounter + -emptyCounter] == STATE_RED){
                                groupType = COLOUR_RED;
                            }
                            else{
                                groupType = COLOUR_YELLOW;
                            }
                        }
                        else{
                            if((groupType == COLOUR_RED && gameBoard[heightCounter + emptyCounter][widthCounter + -emptyCounter] == STATE_YELLOW)
                            ||(groupType == COLOUR_YELLOW && gameBoard[heightCounter + emptyCounter][widthCounter + -emptyCounter] == STATE_RED)){
                                groupType = COLOUR_BOTH;
                            }
                        }
                    }
                }
        
            // calculate score (-for yellow + for red)
            
                if(groupCount > 0 && groupType != COLOUR_BOTH){
                    int groupScore = static_cast<int>(pow(groupCount, 2));                                
                    
                    if(groupCount == BOARD_CONNECT){
                        groupScore = WINNING_SCORE;
                        gameWon = true;
                    }
                    
                    if(groupType == COLOUR_YELLOW){
                        groupScore = -groupScore;
                    }
                    evaluation += groupScore;
                }
            }
        }    
    }
    
    //                  Check if game won                   
    if(gameWon){
        if(evaluation > 0){
            evaluation = WINNING_SCORE;
        }
        else{
            evaluation = -WINNING_SCORE;
        }
    }
    return evaluation;
}


//                                                 Place Piece Function                                                     
bool applyMove(std::vector<std::vector<int>> &gameBoard, bool isRed, int movePosition){
    if(movePosition >= BOARD_WIDTH){
        return false;
    }
    
    int heightCounter = 0;
    for(heightCounter = 0; heightCounter < BOARD_HEIGHT; ++heightCounter){
        if(gameBoard[heightCounter][movePosition] != STATE_EMPTY){
            break;
        }
    }
    
    if(heightCounter == 0){
        return false;
    }
    --heightCounter;
    if(isRed){
        gameBoard[heightCounter][movePosition] = STATE_RED;
    }
    else{
        gameBoard[heightCounter][movePosition] = STATE_YELLOW;
    }
    return true;
}


//                                                   Draw Board Function                                                    
void drawGameBoard(std::vector<std::vector<int>> gameBoard){
    for (auto i = 0; i < BOARD_WIDTH; ++i){
        std::cout << " " << i;
    }
    std::cout << " \n";
    for(auto heightCounter = 0; heightCounter < BOARD_HEIGHT; ++heightCounter){
        for(auto widthCounter = 0; widthCounter < BOARD_WIDTH; ++widthCounter){
            std::cout << "|";
            switch(gameBoard[heightCounter][widthCounter]){
            case STATE_EMPTY: std::cout << " "; break;
            case STATE_RED: std::cout << "R"; break;
            case STATE_YELLOW: std::cout << "Y"; break;
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
