#include <vector>
#include "player.hpp"
using namespace std;

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = true;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    board = Board();
    mySide = side;
    if (side == WHITE)
        opSide = BLACK;
    else
        opSide = WHITE;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/* helper function to adjust heuristic score for moves*/
int value(int i, int j) {
    /* static weights (reference: An Analysis of Heuristics in Othello) */
    int values[8][8] = {{10, -3, 2, 2, 2, 2, -3, 10},
                        {-3, -4, -1, -1, -1, -1, -4, -3}, 
                        {2, -4, 1, 0, 0, 1, -1, 2},
                        {2, -1, 0, 1, 1, 0, -1, 2},
                        {2, -1, 0, 1, 1, 0, -1, 2},
                        {2, -1, 1, 0, 0, 1, -1, 2},
                        {-3, -4, -1, -1, -1, -1, -4, -3},
                        {10, -3, 2, 2, 2, 2, -3, 10}};
    return values[i][j];
}

int Player::minimax(Board *board, int depth, int max_depth, Side side, int
        alpha, int beta)
{
    /* outline:
        if depth == max_depth or moves_list == NULL:
            return board->get_score() // board method to be implemented
        LOOP through moves_list:
            best_score = infinity
            Board *new_board = board
            new_board->doMove(moves_list[i], side)
            score = minimax(new_board, depth + 1, max_depth, side)
            IF score < best_score:
                best_score = score
                 
        return score   
    */

    if (depth == max_depth || !board->hasMoves(side)) {
        return board->score(side);
    }

    int maxScore = -10000;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move move(i,j);
            if (board->checkMove(&move, side)) {
                Board *newBoard = board->copy();
                newBoard->doMove(&move, side);
                int newScore;
                if (side == mySide)
                    newScore = minimax(newBoard, depth+1, max_depth, opSide,
                            alpha, beta);
                else
                    newScore = minimax(newBoard, depth+1, max_depth, mySide,
                            alpha, beta);
                if (newScore > maxScore) {
                    maxScore = newScore;
                }
                delete newBoard;
            }
        }
    }
    if (side == mySide)
        return maxScore;
    return -maxScore;
}    

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */
    board.doMove(opponentsMove, opSide);

    if (board.hasMoves(mySide)) {
        /*
        Naive random player:
        vector<Move> valid_moves;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Move move(i,j);
                if (board.checkMove(&move, mySide))
                    valid_moves.push_back(move);
            }
        }
        int rand_ind = rand() % valid_moves.size();
        int X = valid_moves[rand_ind].getX();
        int Y = valid_moves[rand_ind].getY();
        Move* m = new Move(X, Y);
        */

        /* With heuristic score function: */
        Move* bestMove = nullptr;
        int maxScore = -100;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Move move(i,j);
                if (board.checkMove(&move, mySide)) {
                    Board *newBoard = board.copy();
                    newBoard->doMove(&move, mySide);
                    int newScore;
                    if (testingMinimax) 
                        newScore = minimax(newBoard, 1, 3, opSide, -10000, 10000);
                    else
                        newScore = newBoard->score(mySide) * value(i,j);

                    if (newScore > maxScore) {
                        if (bestMove != nullptr)
                            delete bestMove;
                        bestMove = new Move(i,j);
                        maxScore = newScore;
                    }
                    delete newBoard;
                }
            }
        }
        board.doMove(bestMove, mySide);
        return bestMove;
    }

    return nullptr;
}
