/*
 * Card_T.h
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This header file contains the declarations for the Card struct, a << operator for it,
 *      and two less than functions to compare cards.
 */

#ifndef LAB0_CARD_T_H
#define LAB0_CARD_T_H

#include "includes.h"
#include "Suit.h"

template<typename Suit, typename Rank> struct Card {
    Suit suit;
    Rank rank;

    Card(Suit suit, Rank rank);
};

template<typename Suit, typename Rank>
ostream& operator<<(ostream& ost, const Card<Suit, Rank>& card);

template<typename Suit, typename Rank>
bool lt_rank_suit(const Card<Suit, Rank>& card1, const Card<Suit, Rank>& card2);
template<typename Suit, typename Rank>
bool lt_suit_rank(const Card<Suit, Rank>& card1, const Card<Suit, Rank>& card2);


#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE

#include "Card_T.cpp"

#endif // TEMPLATE_HEADERS_INCLUDE_SOURCE

#endif //LAB0_CARD_T_H
