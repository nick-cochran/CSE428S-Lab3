/*
 * HoldEmDeck.h
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This header file contains declarations for the HoldEmDeck class which inherits the Deck class
 *      and an enum of the appropriate card ranks for a game of Texas Hold Em and the << ++prefix operators.
 */

#ifndef LAB0_HOLDEMDECK_H
#define LAB0_HOLDEMDECK_H

#include "includes.h"
#include "Deck_T.h"
#include "Card_T.h"

enum class HoldEmRank {
    two, three, four, five, six, seven, eight, nine, ten,
        jack, queen, king, ace, undefined
};
ostream& operator<<(ostream& ost, const HoldEmRank& heRank);
HoldEmRank& operator++(HoldEmRank& heRank);


class HoldEmDeck : public Deck<Suit, HoldEmRank> {
 public:
    HoldEmDeck();
};

#endif //LAB0_HOLDEMDECK_H
