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
 * Takes all cards from the inputted card set and pushes them into this card set.
 *
 * @tparam Suit card suit template parameter
 * @tparam Rank card rank template parameter
 * @param card_set the CardSet to empty
 */
template<typename Suit, typename Rank>
void CardSet<Suit, Rank>::collect(CardSet<Suit, Rank>& card_set) {
    std::move(card_set.begin(), card_set.end(), std::back_inserter(this->cards));
    card_set.cards.clear();
}

/**
 * Takes all cards from the inputted card set and pushes them into this card set depending on the predicate.
 *
 * @tparam Suit TODO
 * @tparam Rank
 *
 * @param card_set
 * @param pred
 */
template <typename Suit, typename Rank>
void CardSet<Suit, Rank>::collect_if(CardSet<Suit, Rank>& card_set, std::function<bool(Card<Suit, Rank>&)> pred) {
    std::copy_if(card_set.begin(), card_set.end(), std::back_inserter(this->cards), pred);
    iter_t undefined_region = std::remove_if(card_set.begin(), card_set.end(), pred);
    card_set.cards.erase(undefined_region, card_set.end());
}

/**
 * TODO
 *
 * @tparam Suit
 * @tparam Rank
 * @param card_set
 * @param rank
 * @return
 */
template <typename Suit, typename Rank>
bool CardSet<Suit, Rank>::request(CardSet<Suit, Rank>& card_set, Rank rank) {

    iter_t found_card = std::find(card_set.begin(), card_set.end(), rank);
    if(found_card == card_set.end()) {
        return false;
    } else {
        this->cards.push_back(found_card.base());
        card_set.cards.erase(found_card);
        return true;
    }
}

/**
 * Accessor function to return the cards vector begin iterator.
 *
 * @tparam Suit card suit template parameter
 * @tparam Rank card rank template parameter
 *
 * @return the begin iterator of the cards vector, using decltype to make it more readable.
 */
template<typename Suit, typename Rank>
auto CardSet<Suit, Rank>::begin() -> iter_t {
    return cards.begin();
}

/**
 * Accessor function to return the cards vector end iterator.
 *
 * @tparam Suit card suit template parameter
 * @tparam Rank card rank template parameter
 *
 * @return the end iterator of the cards vector, using decltype to make it more readable.
 */
template<typename Suit, typename Rank>
auto CardSet<Suit, Rank>::end() -> iter_t {
    return cards.end();
}

/**
 * TODO
 *
 * @tparam Suit
 * @tparam Rank
 */
template<typename Suit, typename Rank>
void CardSet<Suit, Rank>::sort() {

    std::sort(cards.begin(), cards.end(),
              [](Card<Suit, Rank> a, Card<Suit, Rank> b) {
                        return lt_rank_suit(a,b);
                    });
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