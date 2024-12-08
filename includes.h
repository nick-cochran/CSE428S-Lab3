/*
 * includes.h
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This header file contains include statements and constants used in most files.
 *
 */

#ifndef LAB0_INCLUDES_H
#define LAB0_INCLUDES_H

#include <iostream>
#include <ostream>
#include <vector>
#include <random>
#include <algorithm>
#include <map>

using std::ostream; using std::istream;
using std::vector; using std::string;
using std::cout; using std::endl; using std::cin;
using std::runtime_error;

// return value constants
const int SUCCESS = 0;
const int CONTINUE_GAME = 1;
const int INVALID_PROGRAM_ARGUMENTS = 2;
const int NULL_GAME_POINTER = 3;

// program input index constants
const int PROGRAM_NAME = 0;
const int GAME_NAME = 1;
const int GO_FISH_DECK = 2;
const int INPUTS_PRE_PLAYERS = 2;
const int GF_INPUTS_PRE_PLAYERS = 3;

const int PINOCHLE_REQUIRED_PLAYERS = 4;
const int HOLDEM_MIN_PLAYERS = 2;
const int HOLDEM_MAX_PLAYERS = 9;
const int GF_MIN_PLAYERS = 2;
const int GF_MAX_PLAYERS = 5;

const int FIRST_PLAYER = 2;

const string BOLD = "\033[1m";
const string BLACK_WHITE = "\033[47;30m";
const string RED_WHITE = "\033[47;31m";
const string GREEN_WHITE = "\033[47;32m";
const string BLUE_WHITE = "\033[47;34m";
const string YELLOW_WHITE = "\033[47;33m";
const string RESET = "\033[0m";

#endif //LAB0_INCLUDES_H
