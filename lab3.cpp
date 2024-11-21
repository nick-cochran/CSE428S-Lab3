/*
 * lab3.cpp
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This source file contains the main function to run the code and helpers.
 */

#include "includes.h"
#include "Game.h"
#include "PinochleGame.h"
#include "HoldEmGame.h"
#include <memory>

using std::shared_ptr; using std::make_shared;

int main(int argc, const char **argv);
int usage(const char **argv);
shared_ptr<Game> create(int argc, const char **argv);


//
/**
 * The main function to run the code.
 *
 * @param argc the length of the input array
 * @param argv the input array of strings
 * @return an integer representing success or failure values
 */
int main(int argc, const char **argv) {

    if (argc < 2) {
        cout << "Error: not enough arguments" << endl;
        return usage(argv);
    }

    string game_name = argv[GAME_NAME];

    if(game_name != "Pinochle" && game_name != "HoldEm") {
        cout << "Error: invalid game name" << endl;
        return usage(argv);
    }
    if(game_name == "Pinochle" && argc != (INPUTS_PRE_PLAYERS + PINOCHLE_REQUIRED_PLAYERS)) {
        cout << "Error: There must be 4 players to play Pinochle." << endl;
        return usage(argv);
    }
    if(game_name == "HoldEm" && (argc < (INPUTS_PRE_PLAYERS + HOLDEM_MIN_PLAYERS)
            || argc > (INPUTS_PRE_PLAYERS + HOLDEM_MAX_PLAYERS))) {
        cout << "Error: There must be between 2 and 9 players to play HoldEm." << endl;
        return usage(argv);
     }

    shared_ptr<Game> game = create(argc, argv);
    if(game) {
        return game->play();
    } else {
        cout << "Error: game not created" << endl;
        return NULL_GAME_POINTER;
    }

}

/**
 * A usage function to run/return with bad arguments.
 *
 * @param argv the input array of strings
 * @return an integer representing an invalid input
 */
int usage(const char **argv) {
    cout << "Usage: " << argv[PROGRAM_NAME] << " <\033[3mPinochle\033[0m | \033[3mHoldEm\033[0m> {player1}, {player2}, ..." << endl;
    return INVALID_PROGRAM_ARGUMENTS;
}

/**
 * Creates a game based on the given arguments.
 *
 * @param argc the length of the input array
 * @param argv the input array of strings
 * @return a shared pointer to an object of type Game
 */
shared_ptr<Game> create(int argc, const char **argv) {
    shared_ptr<Game> game;

    string game_name = argv[GAME_NAME];
    if (game_name == "Pinochle") {
        game = make_shared<PinochleGame>(argc, argv);
    } else if (game_name == "HoldEm") {
        game = make_shared<HoldEmGame>(argc, argv);
    }

    return game;
}