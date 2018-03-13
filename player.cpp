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
    testingMinimax = false;

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
    /* use symmetry */
    if (i >= 4)
        i = 7 - i;
    if (j >= 4)
        j = 7 - j;
    if (i == 0 && j == 0)
        return 3;
    if (i == 0 && j == 1)
        return -3;
    if (i == 1 && j == 0)
        return -3;
    return 1;
}

std::pair<int, Move*> Player::minimax(Board *board, int depth, int max_depth,
        Side side, int alpha, int beta)
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
        return std::make_pair(board->score(side), nullptr);
    }

    int bestScore = -1000;
    if (side == opSide)
        bestScore = 1000;

    Move* bestmove = nullptr;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move move(i,j);
            if (board->checkMove(&move, side)) {
                Board *newBoard = board->copy();
                newBoard->doMove(&move, side);
                int newScore;
                if (side == mySide) {
                    newScore = minimax(newBoard, depth+1, max_depth,
                            opSide, alpha, beta).first;
                    if (newScore > bestScore) {
                        bestScore = newScore;
                        if (bestmove != nullptr)
                            delete bestmove;
                        bestmove = new Move(i, j);
                    }
                    alpha = std::max(bestScore, alpha);
                }
                else {
                    newScore = -minimax(newBoard, depth+1, max_depth,
                            mySide, alpha, beta).first;
                    if (newScore < bestScore) {
                        bestScore = newScore;
                        if (bestmove != nullptr)
                            delete bestmove;
                        bestmove = new Move(i, j);
                    }
                    beta = std::min(bestScore, beta);
                }
                delete newBoard;
                if (alpha > beta) 
                    return std::make_pair(bestScore, bestmove);
            }
        }
    }
    return std::make_pair(bestScore, bestmove);
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
        std::pair<int, Move*> minimax_result = minimax(&board, 0, 3, mySide,
                -1000, 1000);
        board.doMove(minimax_result.second, mySide);
        return minimax_result.second;
    }

    return nullptr;
}
