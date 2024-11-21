/*
 * Game.cpp
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This source file contains the definition for the Game class's constructor and one basic function.
 */

#include "Game.h"

/**
 * Game constructor that pushes inputted player names into the appropriate vector.
 *
 * @param argc stardard length of input array
 * @param argv array of input strings
 */
Game::Game(int argc, const char **argv) {
    for(int i = FIRST_PLAYER; i < argc; i++) {
        player_names.push_back(argv[i]);
    }
}

/**
 * Asks the user if they would like to end the current game.
 *
 * @return Int representing either end the game or continue the game.
 */
int Game::askToEndGame() {
    cout << "Would you like to end the game? (yes/[no]): " << endl;
    string response;
    cin >> response;
    if(response == "yes") {
        cout << "Successfully Ended Game." << endl;
        return SUCCESS;
    } else {
        return CONTINUE_GAME;
    }
}