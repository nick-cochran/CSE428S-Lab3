/*
 * Card_T.cpp
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This source file contains the definitions for the Card struct, a << operator for it,
 *      and two less than functions to compare cards.
 */

#include "Card_T.h"

/**
 * Constructor for Card Struct
 *
 * @tparam Suit card suit template parameter
 * @tparam Rank card rank template parameter
 * @param suit the suit of the card
 * @param rank the rank of the card
 */
template<typename Suit, typename Rank>
Card<Suit, Rank>::Card(Suit suit, Rank rank): suit(suit), rank(rank) {}

/**
 * Output operator for the card struct
 *
 * @tparam Suit card suit template parameter
 * @tparam Rank card rank template parameter
 * @param ost reference to an ostream object
 * @param card the card to output
 * @return the same ostream reference
 */
template<typename Suit, typename Rank>
ostream& operator<<(ostream& ost, const Card<Suit, Rank>& card) {
    ost << card.rank << card.suit;
    return ost;
}

/**
 * Compares if cards are less than each other, using rank first and then suit
 *
 * @tparam Suit card suit template parameter
 * @tparam Rank card rank template parameter
 * @param card1 first card to compare
 * @param card2 second card to compare
 * @return true if card1 is less than card2, else false
 */
template<typename Suit, typename Rank>
bool lt_rank_suit(const Card<Suit, Rank>& card1, const Card<Suit, Rank>& card2) {
    if(card1.rank < card2.rank) {
        return true;
    }
    if(card1.rank == card2.rank && card1.suit < card2.suit) {
        return true;
    }
    return false;
}

/**
 * Compares if cards are less than each other, using suit first and then rank
 *
 * @tparam Suit card suit template parameter
 * @tparam Rank card rank template parameter
 * @param card1 first card to compare
 * @param card2 second card to compare
 * @return true if card1 is less than card2, else false
 */
template<typename Suit, typename Rank>
bool lt_suit_rank(const Card<Suit, Rank>& card1, const Card<Suit, Rank>& card2) {
    if(card1.suit < card2.suit) {
        return true;
    }
    if(card1.suit == card2.suit && card1.rank < card2.rank) {
        return true;
    }
    return false;
}
