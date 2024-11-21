/*
 * Suit.h
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This header file contains declarations for the Suit enum and relevant operators.
 *
 */

#ifndef LAB0_SUIT_H
#define LAB0_SUIT_H

#include "includes.h"

// color thanks to: https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
const string HEART  = "\033[31m\u2665\033[0m";  //♥
const string DIAMOND = "\033[31m\u2666\033[0m";  //♦
const string CLUB   = "\u2663";  //♣
const string SPADE  = "\u2660";  //♠

enum class Suit {clubs, diamonds, hearts, spades, undefined};
const Suit firstSuit = Suit::clubs;

ostream& operator<<(ostream& ost, const Suit& suit);
Suit& operator++(Suit& suit);

#endif //LAB0_SUIT_H
