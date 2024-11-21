/*
 * CardSet_T.h
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This header file contains the declaration of the CardSet template base class and its functions.
 */

#ifndef LAB1_CARDSET_H
#define LAB1_CARDSET_H

#include "includes.h"
#include "Card_T.h"

template <typename Suit, typename Rank> class CardSet {
 protected:
    vector< Card<Suit, Rank> > cards;

 public:
    CardSet() = default;
    CardSet(const CardSet<Suit, Rank>& card_set);
    CardSet& operator=(const CardSet<Suit, Rank>&) = default;
    void print(ostream& ost, size_t size);
    CardSet& operator>>(CardSet<Suit, Rank>& card_set);
    // public function to return pointer to member variable cards which is protected
    static vector< Card<Suit, Rank> > CardSet::* get_cards() { return &CardSet::cards; }
    bool is_empty();
    virtual ~CardSet() = default; // need to include virtual destructor because this is a base class
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE

#include "CardSet_T.cpp"

#endif // TEMPLATE_HEADERS_INCLUDE_SOURCE

#endif //LAB1_CARDSET_H
