/*
 * Deck_T.cpp
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This source file contains the declarations for the Deck template class functions.
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

/**
 * takes all cards from the inputted CardSet and pushes them into this deck
 *
 * @tparam Suit card suit template parameter
 * @tparam Rank card rank template parameter
 * @param card_set the CardSet to empty
 */
template<typename Suit, typename Rank>
void Deck<Suit, Rank>::collect(CardSet<Suit, Rank>& card_set) {

    if(card_set.is_empty()) {
        return; // nothing to collect
    }

    while(!card_set.is_empty()) {
        card_set >> *this;
    }

}