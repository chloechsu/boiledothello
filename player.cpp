#include <vector>
#include "player.hpp"

/* change for testing git */ 

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
                    int newScore = newBoard->score(mySide) * value(i,j);
                    if (newScore > maxScore) {
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
