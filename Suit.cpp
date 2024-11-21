/*
 * Suit.cpp
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This source file contains the definitions for the operators for the Suit enum.
 */

#include "Suit.h"

/**
 * The << operator to output a string representing the Suit.
 *
 * @param ost a reference to an ostream object
 * @param suit a const reference to a Suit
 * @return the passed in ostream object
 */
ostream& operator<<(ostream &ost, const Suit &suit) {
    switch (suit) {
        case Suit::clubs:
            ost << CLUB;
            return ost;
        case Suit::diamonds:
            ost << DIAMOND;
            return ost;
        case Suit::hearts:
            ost << HEART;
            return ost;
        case Suit::spades:
            ost << SPADE;
            return ost;
        default:
            ost << "?";
            return ost;
    }
}

//
/**
 * Prefix ++ operator for the Suit enum to move to the next suit.
 *
 * @param suit a reference to a Suit
 * @return the incremented Suit that was passed in
 */
Suit& operator++(Suit& suit) {
    switch (suit) {
        case Suit::clubs:
            suit = Suit::diamonds;
            return suit;
        case Suit::diamonds:
            suit = Suit::hearts;
            return suit;
        case Suit::hearts:
            suit = Suit::spades;
            return suit;
        case Suit::spades:
            suit = Suit::undefined;
            return suit;
        default:
            suit = Suit::undefined;
            return suit;
    }
}