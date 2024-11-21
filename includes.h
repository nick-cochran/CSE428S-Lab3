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

using std::ostream;
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
const int INPUTS_PRE_PLAYERS = 2;
const int PINOCHLE_REQUIRED_PLAYERS = 4;
const int HOLDEM_MIN_PLAYERS = 2;
const int HOLDEM_MAX_PLAYERS = 9;

#endif //LAB0_INCLUDES_H
