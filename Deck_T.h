/*
 * Deck_T.h
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This header file contains the declaration for the Deck template class
 *      which publicly inherits CardSet and can be inherited itself.
 */

#ifndef LAB0_DECK_H
#define LAB0_DECK_H

#include "includes.h"
#include "CardSet_T.h"

template<typename Suit, typename Rank> class Deck : public CardSet<Suit, Rank> {
 public:
    void shuffle();
    void collect(CardSet<Suit, Rank>& card_set);
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE

#include "Deck_T.cpp"

#endif // TEMPLATE_HEADERS_INCLUDE_SOURCE

#endif //LAB0_DECK_H
