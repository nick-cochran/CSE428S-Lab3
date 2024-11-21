/*
 * Game.h
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This header file contains the declaration for the Game abstract base class.
 */

#ifndef LAB1_GAME_H
#define LAB1_GAME_H

#include "includes.h"

const int FIRST_PLAYER = 2;

// abstract Game class
class Game {
 protected:
    vector<string> player_names;
    static int askToEndGame();
 public:
    Game(int argc, const char **argv);
    virtual int play() = 0;
    virtual ~Game() = default;
};

#endif //LAB1_GAME_H
