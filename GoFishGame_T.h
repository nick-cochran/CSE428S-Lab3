//
// Created by Nick Cochran on 11/30/24.
//

#ifndef LAB3_GOFISHDECK_H
#define LAB3_GOFISHDECK_H

#include "includes.h"
#include "Deck_T.h"
#include "Card_T.h"
#include "UnoDeck.h"
#include "HoldEmGame.h"
#include "PinochleGame.h"

const int FOUR_OF_A_KIND = 4;
const int GF_CARDS_PER_LINE = 10;

const int HAND_SIZE_2PLAYERS = 7;
const int HAND_SIZE_MORE_PLAYERS = 5;


template<class GF_Suit = Suit, class GF_Rank = HoldEmRank, class GF_Deck = HoldEmDeck>
class GoFishGame : public Game {
    typedef Card<GF_Suit, GF_Rank> card_t;
    typedef CardSet<GF_Suit, GF_Rank> cardSet_t;
    static_assert(std::is_base_of<cardSet_t, GF_Deck>::value, "GF_Deck must be a subclass of Deck");
 protected:
    GF_Deck deck;
    vector<cardSet_t> player_hands;
    vector<cardSet_t> books;
    vector<bool> player_still_in; // keep track of the players still in the game
    virtual void deal();
    bool turn(unsigned int player_num);
    bool collect_books(unsigned int player_num);
 public:
    GoFishGame(int argc, const char **argv);
    virtual int play();
    virtual ~GoFishGame() = default;
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE

#include "GoFishGame_T.cpp"

#endif // TEMPLATE_HEADERS_INCLUDE_SOURCE

#endif //LAB3_GOFISHDECK_H
