/*
 * UnoDeck.h
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This header file contains declarations for the UnoDeck class which inherits the Deck class,
 *      an enum for Uno card ranks, and an enum for the Uno colors with useful operators for both.
 */

#ifndef LAB3_UNODECK_H
#define LAB3_UNODECK_H

#include "includes.h"
#include "Deck_T.h"
#include "Card_T.h"


enum class Color {
    red, blue, green, yellow, black, undefined
};
ostream& operator<<(ostream& ost, const Color& uno_color);
Color& operator++(Color& uno_color);

enum class UnoRank {
    zero, one, two, three, four, five, six, seven, eight, nine,
        skip, reverse, draw_two, draw_four, wild, blank, undefined
};
ostream& operator<<(ostream& ost, const UnoRank& uno_rank);
istream& operator>>(istream& ist, UnoRank& uno_rank);
UnoRank& operator++(UnoRank& uno_rank);


class UnoDeck : public Deck<Color, UnoRank> {
 public:
    UnoDeck();
};

UnoRank get_first(UnoDeck&);


#endif //LAB3_UNODECK_H
