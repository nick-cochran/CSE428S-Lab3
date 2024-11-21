/*
 * PinochleDeck.h
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This header file contains declarations for the PinochleDeck class which inherits the Deck class
 *      and an enum for Pinochle card ranks with useful operators.
 */

#ifndef LAB0_PINOCHLEDECK_H
#define LAB0_PINOCHLEDECK_H

#include "includes.h"
#include "Deck_T.h"
#include "Card_T.h"

enum class PinochleRank {
    nine, jack, queen, king, ten, ace, undefined
};
ostream& operator<<(ostream& ost, const PinochleRank& pRank);
PinochleRank& operator++(PinochleRank& pRank);

class PinochleDeck : public Deck<Suit, PinochleRank> {
 public:
    PinochleDeck();
};

#endif //LAB0_PINOCHLEDECK_H
