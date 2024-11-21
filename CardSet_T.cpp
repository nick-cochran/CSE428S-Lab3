/*
 * CardSet_T.cpp
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This source file contains the definition of the CardSet template base class and its functions.
 */

#include "CardSet_T.h"

/**
 * The copy constructor for the CardSet struct which creates a deep copy.
 *
 * @tparam Suit card suit template parameter
 * @tparam Rank card rank template parameter
 * @param card_set the CardSet object to copy from
 */
template <typename Suit, typename Rank>
CardSet<Suit, Rank>::CardSet(const CardSet<Suit, Rank>& card_set) {
    for(Card<Suit, Rank> card : card_set.cards) {
        this->cards.push_back(card);
    }
}

/**
 * A function to print out the cards in the card set.
 *
 * @tparam Suit card suit template parameter
 * @tparam Rank card rank template parameter
 * @param ost a reference to an ostream object
 * @param size the number of cards to print on each line
 */
template<typename Suit, typename Rank>
void CardSet<Suit, Rank>::print(std::ostream &ost, size_t size) {
    size_t count = 0;
    for(Card<Suit, Rank> card : cards) {
        count++;
        ost << card << " ";
        if(count >= size) {
            // only add a new line when not at the end of the vector
            if(count != cards.size()) {
                ost << endl;
            }
            count = 0;
        }
    }
}

/**
 * The input operator for the CardSet struct which takes a card from this card set and puts
 *      it into the inputted card set.
 *
 * @tparam Suit card suit template parameter
 * @tparam Rank card rank template parameter
 * @param card_set the card set to input a card into
 * @return the CardSet the function was called on
 */
template<typename Suit, typename Rank>
CardSet<Suit, Rank>& CardSet<Suit, Rank>::operator>>(CardSet<Suit, Rank>& card_set) {

    if(this->is_empty()) {
        throw runtime_error("Card set is empty");
    }

    card_set.cards.push_back(this->cards.back());
    this->cards.pop_back();

    return *this;
}

/**
 * Checks if the cards vector is empty
 *
 * @tparam Suit card suit template parameter
 * @tparam Rank card rank template parameter
 * @return true if it is empty, otherwise false
 */
template<typename Suit, typename Rank>
bool CardSet<Suit, Rank>::is_empty() {
    return this->cards.empty();
}