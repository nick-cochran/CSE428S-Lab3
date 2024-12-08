/*
 * HoldEmDeck.cpp
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This source file contains the definitions for the HoldEmDeck class and an enum
 *      of the appropriate card ranks for a game of Texas Hold Em and the << ++prefix operators.
 */

#include "HoldEmDeck.h"


/**
 * HoldEmDeck Constructor which pushes back cards into the cards vector to create the deck.
 */
HoldEmDeck::HoldEmDeck() {
    for(Suit suit = firstSuit; suit != Suit::undefined; ++suit) {
        for(HoldEmRank rank = HoldEmRank::two; rank != HoldEmRank::undefined; ++rank) {
            cards.emplace_back(suit, rank);
        }
    }
}

/**
 * TODO
 *
 * @return
 */
HoldEmRank get_first(HoldEmDeck&) {
    return HoldEmRank::two;
}

/**
 * Overloads the << operator for the HoldEmRank enum to print a string representation.
 *
 * @param ost a reference to an ostream object
 * @param heRank the passed in HoldEmRank by reference
 * @return the passed in ostream object reference
 */
ostream& operator<<(ostream& ost, const HoldEmRank& heRank) {
    switch (heRank) {
        case HoldEmRank::two:
            ost << "2";
            return ost;
        case HoldEmRank::three:
            ost << "3";
            return ost;
        case HoldEmRank::four:
            ost << "4";
            return ost;
        case HoldEmRank::five:
            ost << "5";
            return ost;
        case HoldEmRank::six:
            ost << "6";
            return ost;
        case HoldEmRank::seven:
            ost << "7";
            return ost;
        case HoldEmRank::eight:
            ost << "8";
            return ost;
        case HoldEmRank::nine:
            ost << "9";
            return ost;
        case HoldEmRank::ten:
            ost << "10";
            return ost;
        case HoldEmRank::jack:
            ost << "J";
            return ost;
        case HoldEmRank::queen:
            ost << "Q";
            return ost;
        case HoldEmRank::king:
            ost << "K";
            return ost;
        case HoldEmRank::ace:
            ost << "A";
            return ost;
        default:
            ost << "?";
            return ost;
    }
}

/**
 * TODO
 *
 * @param ist
 * @param heRank
 * @return
 */
istream& operator>>(istream& ist, HoldEmRank& heRank) {
    string rank_name;
    ist >> rank_name;

    if(rank_name == "2") {
        heRank = HoldEmRank::two;
    } else if(rank_name == "3") {
        heRank = HoldEmRank::three;
    } else if(rank_name == "4") {
        heRank = HoldEmRank::four;
    } else if(rank_name == "5") {
        heRank = HoldEmRank::five;
    } else if(rank_name == "6") {
        heRank = HoldEmRank::six;
    } else if(rank_name == "7") {
        heRank = HoldEmRank::seven;
    } else if(rank_name == "8") {
        heRank = HoldEmRank::eight;
    } else if(rank_name == "9") {
        heRank = HoldEmRank::nine;
    } else if(rank_name == "10") {
        heRank = HoldEmRank::ten;
    } else if(rank_name == "J") {
        heRank = HoldEmRank::jack;
    } else if(rank_name == "Q") {
        heRank = HoldEmRank::queen;
    } else if(rank_name == "K") {
        heRank = HoldEmRank::king;
    } else if(rank_name == "A") {
        heRank = HoldEmRank::ace;
    } else {
        heRank = HoldEmRank::undefined;
    }
    return ist;
}

/**
 * Overloads the ++ prefix operator for the HoldEmRank enum to increment to the next card rank.
 *
 * @param heRank a reference to a HoldEmRank object
 * @return the incremented HoldEmRank object
 */
HoldEmRank& operator++(HoldEmRank& heRank) {
    switch (heRank) {
        case HoldEmRank::two:
            return heRank = HoldEmRank::three;
        case HoldEmRank::three:
            return heRank = HoldEmRank::four;
        case HoldEmRank::four:
            return heRank = HoldEmRank::five;
        case HoldEmRank::five:
            return heRank = HoldEmRank::six;
        case HoldEmRank::six:
            return heRank = HoldEmRank::seven;
        case HoldEmRank::seven:
            return heRank = HoldEmRank::eight;
        case HoldEmRank::eight:
            return heRank = HoldEmRank::nine;
        case HoldEmRank::nine:
            return heRank = HoldEmRank::ten;
        case HoldEmRank::ten:
            return heRank = HoldEmRank::jack;
        case HoldEmRank::jack:
            return heRank = HoldEmRank::queen;
        case HoldEmRank::queen:
            return heRank = HoldEmRank::king;
        case HoldEmRank::king:
            return heRank = HoldEmRank::ace;
        case HoldEmRank::ace:
            return heRank = HoldEmRank::undefined;
        default:
            return heRank = HoldEmRank::undefined;
    }
}