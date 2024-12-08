/*
 * lab3.cpp
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This source file contains the main function to run the code and helpers.
 */

#include "includes.h"
#include "UnoDeck.h"
#include "PinochleGame.h"
#include "HoldEmGame.h"
#include "GoFishGame_T.h"
#include <memory>

using std::shared_ptr; using std::make_shared;

int main(int argc, const char **argv);
int usage(const char **argv, const string& game_name);
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
        return usage(argv, "");
    }

    string game_name = argv[GAME_NAME];

    if(game_name != "Pinochle" && game_name != "HoldEm" && game_name != "GoFish") {
        cout << "Error: invalid game name" << endl;
        return usage(argv, "Pinochle");
    }
    if(game_name == "Pinochle" && argc != (INPUTS_PRE_PLAYERS + PINOCHLE_REQUIRED_PLAYERS)) {
        cout << "Error: There must be 4 player_hands to play Pinochle." << endl;
        return usage(argv, "Pinochle");
    }
    if(game_name == "HoldEm" && (argc < (INPUTS_PRE_PLAYERS + HOLDEM_MIN_PLAYERS)
            || argc > (INPUTS_PRE_PLAYERS + HOLDEM_MAX_PLAYERS))) {
        cout << "Error: There must be between 2 and 9 player_hands to play HoldEm." << endl;
        return usage(argv, "HoldEm");
     }
    if(game_name == "GoFish" && (argc < (GF_INPUTS_PRE_PLAYERS + GF_MIN_PLAYERS)
            || argc > (GF_INPUTS_PRE_PLAYERS + GF_MAX_PLAYERS))) {
        cout << "Error: There must be at least 1 player to play GoFish." << endl;
        return usage(argv, "GoFish");
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
int usage(const char **argv, const string& game_name) {
    if(game_name.empty()) {
        cout << "Usage: " << argv[PROGRAM_NAME] << " <Pinochle | HoldEm> {player1}, {player2}, ..." << endl;
        cout << "OR" << endl;
        cout << "Usage: " << argv[PROGRAM_NAME] << " {GoFish} {Uno | HoldEm | Pinochle} {player1}, {player2}, ..." << endl;
    } else if(game_name == "Pinochle") {
        cout << "Usage: " << argv[PROGRAM_NAME] << " {Pinochle} {player1}, {player2}, {player3}, {player4}" << endl;
    } else if(game_name == "HoldEm") {
        cout << "Usage: " << argv[PROGRAM_NAME] << " {HoldEm} {player1}, {player2}, ... {player9}" << endl;
    } else if(game_name == "GoFish") {
        cout << "Usage: " << argv[PROGRAM_NAME] << " {GoFish} {Uno | HoldEm | Pinochle} {player1}, {player2}, ..." << endl;
    }
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
    } else if(game_name == "GoFish") {
        string deck_type = argv[GO_FISH_DECK];
        try {
            const char **uno_argv = argv+1;
            int uno_argc = argc-1;
            if(deck_type == "Uno") {
                game = make_shared<GoFishGame<Color, UnoRank, UnoDeck> >(uno_argc, uno_argv);
            } else if(deck_type == "HoldEm") {
                game = make_shared<GoFishGame<Suit, HoldEmRank, HoldEmDeck> >(uno_argc, uno_argv);
            } else if(deck_type == "Pinochle") {
                game = make_shared<GoFishGame<Suit, PinochleRank, PinochleDeck> >(uno_argc, uno_argv);
            } else {
                cout << "Error: invalid deck type" << endl;
                throw std::invalid_argument("invalid deck type");
            }
        } catch (std::exception &e) {
            cout << "Error: " << e.what() << endl;
            return nullptr;
        }
    } else {
        cout << "Error: invalid game name" << endl;
        return nullptr;
    }

    return game;
}