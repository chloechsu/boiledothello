#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    int minimax(Board *board, int depth, int max_depth, Side side, int alpha,
            int beta);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

    Board board;

private:
    Side mySide, opSide;

};

#endif
