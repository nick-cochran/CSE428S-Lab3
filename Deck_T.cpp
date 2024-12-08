/*
 * Deck_T.cpp
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This source file contains the definitions for the Deck template class functions.
 */

#include "Deck_T.h"


/**
 * shuffles the deck of cards
 *
 * @tparam Suit card suit template parameter
 * @tparam Rank card rank template parameter
 */
template<typename Suit, typename Rank>
void Deck<Suit, Rank>::shuffle() {
    std::random_device random_device;
    auto rng = std::mt19937(random_device());

    std::shuffle(this->cards.begin(), this->cards.end(), rng);
}
