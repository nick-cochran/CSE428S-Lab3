/*
 * PinochleDeck.cpp
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This source file contains definitions for the PinochleDeck class which inherits the Deck class
 *      and the Pinochle card ranks enum's operators.
 */

#include "PinochleDeck.h"

/**
 * A PinochleDeck Constructor which pushes back cards into the cards vector.
 */
PinochleDeck::PinochleDeck() {
    for(Suit suit = firstSuit; suit != Suit::undefined; ++suit) {
        for(PinochleRank rank = PinochleRank::nine; rank != PinochleRank::undefined; ++rank) {
            cards.emplace_back(suit, rank);
        }
    }
    // nested for loop used again instead of two push backs in the previous one
    //   because this results in a better ordering
    for(Suit suit = firstSuit; suit != Suit::undefined; ++suit) {
        for(PinochleRank rank = PinochleRank::nine; rank != PinochleRank::undefined; ++rank) {
            cards.emplace_back(suit, rank);
        }
    }
}

/**
 * Returns the first rank in the PinochleRank enum.
 *
 * @return the first rank in the PinochleRank enum.
 */
PinochleRank get_first(PinochleDeck&) {
    return PinochleRank::nine;
}

/**
 * Overloads the << operator for the PinochleRank enum.
 *
 * @param ost a reference to an ostream object
 * @param pRank a const reference to the pinochle rank
 * @return the passed in ostream object
 */
ostream& operator<<(ostream& ost, const PinochleRank& pRank) {
    switch (pRank) {
        case PinochleRank::nine:
            ost << "9";
            return ost;
        case PinochleRank::jack:
            ost << "J";
            return ost;
        case PinochleRank::queen:
            ost << "Q";
            return ost;
        case PinochleRank::king:
            ost << "K";
            return ost;
        case PinochleRank::ten:
            ost << "10";
            return ost;
        case PinochleRank::ace:
            ost << "A";
            return ost;
        default:
            ost << "?";
            return ost;
    }
}

/**
 * Overloads the >> operator for the PinochleRank enum to read in a string representation of a card rank.
 *
 * @param ist a reference to an istream object
 * @param pRank the passed in PinochleRank by reference
 *
 * @return the passed in istream object reference
 */
istream& operator>>(istream& ist, PinochleRank& pRank) {
    string rank_name;
    ist >> rank_name;
    std::transform(rank_name.begin(), rank_name.end(), rank_name.begin(), ::tolower);

    if(rank_name == "9") {
        pRank = PinochleRank::nine;
    } else if(rank_name == "10") {
        pRank = PinochleRank::ten;
    } else if(rank_name == "j") {
        pRank = PinochleRank::jack;
    } else if(rank_name == "q") {
        pRank = PinochleRank::queen;
    } else if(rank_name == "k") {
        pRank = PinochleRank::king;
    } else if(rank_name == "a") {
        pRank = PinochleRank::ace;
    } else {
        pRank = PinochleRank::undefined;
    }
    return ist;
}

/**
 * Overloads the ++prefix operator for the PinochleRank enum.
 *
 * @param pRank a reference to the pinochle rank
 * @return the incremented pinochle rank
 */
PinochleRank& operator++(PinochleRank& pRank) {
    switch (pRank) {
        case PinochleRank::nine:
            return (pRank = PinochleRank::jack);
        case PinochleRank::jack:
            return (pRank = PinochleRank::queen);
        case PinochleRank::queen:
            return (pRank = PinochleRank::king);
        case PinochleRank::king:
            return (pRank = PinochleRank::ten);
        case PinochleRank::ten:
            return (pRank = PinochleRank::ace);
        case PinochleRank::ace:
            return (pRank = PinochleRank::undefined);
        default:
            return (pRank = PinochleRank::undefined);
    }
}