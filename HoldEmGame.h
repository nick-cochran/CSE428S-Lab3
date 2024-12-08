/*
 * HoldEmGame.h
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This header file contains the HoldEmGame class and its functions as well as
 *      enums for the state of the game and the ranks of texas hold em hands.
 *      Inside the HoldEmGame class, there is also a player struct for which
 *      there is a < operator and helper functions.
 */

#ifndef LAB1_HOLDEMGAME_H
#define LAB1_HOLDEMGAME_H

#include "includes.h"
#include "Game.h"
#include "HoldEmDeck.h"

const int HOLDEM_HAND_SIZE = 2;
const int HOLDEM_RANKS_SIZE = 5;

const int LARGEST_COUNT = 0;
const int SECOND_LARGEST_COUNT = 1;

const int FIRST_CARD = 0;
const int SECOND_CARD = 1;
const int THIRD_CARD = 2;
const int FOURTH_CARD = 3;
const int FIFTH_CARD = 4;

enum class HoldEmState {
    preflop, flop, turn, river, undefined
};
HoldEmState& operator++(HoldEmState& state);

const HoldEmState INIT_STATE = HoldEmState::preflop;

enum class HoldEmHandRank {
    x_high, pair, two_pair, three_of_a_kind, straight, flush, full_house, four_of_a_kind, straight_flush, undefined
};
ostream& operator<<(ostream& ost, const HoldEmHandRank& hand_rank);


class HoldEmGame : public Game {
    // public area first to be able to use the Player struct in private methods
    // it looks cleaner to do it this way
 public:
    HoldEmGame(int argc, const char **argv);
    virtual int play();
    struct Player {
        CardSet<Suit, HoldEmRank> hand;
        string player_name;
        HoldEmHandRank rank;
        Player(CardSet<Suit, HoldEmRank> hand, string player_name, HoldEmHandRank rank);
    };
    virtual ~HoldEmGame() = default;
 private:
    void create_eval_players(vector<Player>& players);
    void print_hands(ostream &ost);
    void print_board(ostream &ost, HoldEmState cur_state);
    void print_players(ostream &ost, vector<Player>& players);
    void collect_cards();
    HoldEmHandRank holdem_hand_eval(const CardSet<Suit, HoldEmRank>& hand);
    static bool is_straight(CardSet<Suit, HoldEmRank>& hand);
    static bool is_flush(CardSet<Suit, HoldEmRank>& hand);
    static vector<int> how_many_same_rank(CardSet<Suit, HoldEmRank>& hand);

 protected:
    HoldEmState state;
    HoldEmDeck deck;
    vector< CardSet<Suit, HoldEmRank> > hands;
    CardSet<Suit, HoldEmRank> common_cards;
    virtual void deal(CardSet<Suit, HoldEmRank>& burned_cards);
};
bool operator<(const HoldEmGame::Player& player1, const HoldEmGame::Player& player2);
bool find_highest_card(vector<Card<Suit, HoldEmRank> > p1_hand, vector<Card<Suit, HoldEmRank> > p2_hand);
vector<std::map<int, HoldEmRank>> find_group_rank(int group_size1, int group_size2,
                                vector< Card<Suit, HoldEmRank> > p1_hand, vector< Card<Suit, HoldEmRank> > p2_hand);


#endif //LAB1_HOLDEMGAME_H
