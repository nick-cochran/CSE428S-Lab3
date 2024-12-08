/*
 * PinochleGame.h
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This header file contains the PinochleGame class and its functions as well as
 *      an enum for the melds of Pinochle hands and an << operator.
 */

#ifndef LAB1_PINOCHLEGAME_H
#define LAB1_PINOCHLEGAME_H

#include "includes.h"
#include "Game.h"
#include "PinochleDeck.h"

enum class PinochleMeld : unsigned int {
    dix, off_suit_marriage, forty_jacks, pinochle, in_suit_marriage, sixty_queens,
    eighty_kings, hundred_aces, in_suit_run, double_pinochle, four_hundred_jacks,
    six_hundred_queens, eight_hundred_kings, thousand_aces, in_suit_double_run
};
ostream& operator<<(ostream& ost, const PinochleMeld& meld);

const int PINOCHLE_HAND_SIZE = 12;

class PinochleGame : public Game {

    void print_hands_and_melds(ostream& ost);
    void collect_cards();
    void suit_independent_eval(const CardSet<Suit, PinochleRank>& hand, vector<PinochleMeld>& melds);
    bool find_all_suits(const vector<Suit>& suit_vec);

 protected:
    PinochleDeck deck;
    vector< CardSet<Suit, PinochleRank> > hands;
    virtual void deal();

 public:
    static const unsigned int meld_values[];
    PinochleGame(int argc, const char **argv);
    virtual int play();
    virtual ~PinochleGame() = default;
};

#endif //LAB1_PINOCHLEGAME_H
