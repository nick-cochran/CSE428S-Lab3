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
#include <algorithm>
#include <functional>

template <typename Suit, typename Rank> class CardSet {
 protected:
    vector< Card<Suit, Rank> > cards;

 public:
    typedef Card<Suit, Rank> card_t;
    typedef typename vector<card_t>::iterator iter_t;

    CardSet() = default;
    CardSet(const CardSet<Suit, Rank>& card_set);
    CardSet& operator=(const CardSet<Suit, Rank>&) = default;
    void print(ostream& ost, size_t size);
    CardSet& operator>>(CardSet<Suit, Rank>& card_set);
    void collect(CardSet<Suit, Rank>& card_set);
    void collect_if(CardSet<Suit, Rank>& card_set, std::function<bool(Card<Suit, Rank>&)> pred);
    bool request(CardSet<Suit, Rank>& card_set, Rank rank);
    auto begin() -> iter_t;
    auto end() -> iter_t;
    void sort();
    bool is_empty();
    int get_size();
    virtual ~CardSet() = default; // need to include virtual destructor because this is a base class
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE

#include "CardSet_T.cpp"

#endif // TEMPLATE_HEADERS_INCLUDE_SOURCE

#endif //LAB1_CARDSET_H
