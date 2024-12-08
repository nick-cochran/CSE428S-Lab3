/*
 * HoldEmGame.cpp
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This source file contains the definitions for the HoldEmGame class and its functions
 *      as well as enums for the state of the game and the ranks of texas hold em hands.
 *      Inside the HoldEmGame class, there is also a player struct for which
 *      there is a < operator and helper functions.
 */

#include "HoldEmGame.h"

/**
 * Play a game of Texas Hold 'Em.
 *
 * @return an int representing success.
 */
int HoldEmGame::play() {
    while(true) {

        deck.shuffle();

        state = HoldEmState::preflop;
        vector<Player> players;
        CardSet<Suit, HoldEmRank> burned_cards = CardSet<Suit, HoldEmRank>();

        deal(burned_cards); // deal hands
        print_hands(cout);

        deal(burned_cards); // deal flop
        print_board(cout, HoldEmState::flop);


        create_eval_players(players); // create player_hands structs and assign hand ranks
        std::sort(players.begin(), players.end(),
                  [](Player& a, Player& b) {
                            return b < a;
                        });

        print_players(cout, players);

        deal(burned_cards); // deal turn
        print_board(cout, HoldEmState::turn);

        deal(burned_cards); // deal river
        print_board(cout, HoldEmState::river);

        collect_cards();
        deck.collect(common_cards);
        deck.collect(burned_cards);

        int response = askToEndGame();
        if(response == SUCCESS) {
            return SUCCESS;
        }
    }
}

/**
 * Constructor for the HoldEmGame class, uses the inherited Game constructor and initializes the game state.
 *
 * @param argc the length of the input array
 * @param argv the input array of strings
 */
HoldEmGame::HoldEmGame(int argc, const char **argv): Game(argc, argv), state(INIT_STATE) {

    for(int i = FIRST_PLAYER; i < argc; ++i) {
        CardSet<Suit, HoldEmRank> hand;
        hands.push_back(hand);
    }
}

/**
 * Deals out cards depending on the state of the game.
 *
 * @param burned_cards a reference to a vector to burn cards before dealing to the board
 */
void HoldEmGame::deal(CardSet<Suit, HoldEmRank>& burned_cards) {
    const int two_cards = 2;

    switch (state) {
        case HoldEmState::preflop:
            // deal two cards to each player
            for(auto i = 0; i < two_cards; ++i) {
                for(auto& hand : hands) {
                    this->deck >> hand;
                }
            }
            state = HoldEmState::flop;
            break;
        case HoldEmState::flop:
            this->deck >> burned_cards;
            // deal three cards to the board
            this->deck >> common_cards >> common_cards >> common_cards;
            state = HoldEmState::turn;
            break;
        case HoldEmState::turn:
            this->deck >> burned_cards;
            // deal one card to the board
            this->deck >> common_cards;
            state = HoldEmState::river;
            break;
        case HoldEmState::river:
            this->deck >> burned_cards;
            // deal one card to the board
            this->deck >> common_cards;
            state = HoldEmState::undefined;
            break;
        default: // undefined case-- do nothing
            break;
    }
}

/**
 * Initializes the player_hands struct that is passed in and then assigns the appropriate hand rank.
 *
 * @param players a reference to a vector of Players
 */
void HoldEmGame::create_eval_players(vector<Player>& players) {
    size_t i;
    for(i = 0; i < player_names.size(); i++) {
        players.emplace_back(hands[i], player_names[i], HoldEmHandRank::undefined);
    }

    for(Player& player : players) {
        auto common_cards_copy(common_cards);
        CardSet<Suit, HoldEmRank>& hand = player.hand;

        while (!common_cards_copy.is_empty()) {
            common_cards_copy >> hand;
        }

        player.rank = holdem_hand_eval(player.hand);
    }
}

/**
 * Print out the player's hands.
 *
 * @param ost a reference to an ostream object
 */
void HoldEmGame::print_hands(ostream &ost) {
    cout << "\033[1mThe player_hands have been dealt their hands.\033[0m" << endl;
    for(long unsigned int i = 0; i < hands.size(); ++i) {
        ost << "Player \033[1m" << player_names[i] << "\033[0m has hand: ";
        hands[i].print(ost, HOLDEM_HAND_SIZE);
        ost << endl;
    }
    ost << endl;
}

/**
 * Print out the board given the state of the game.
 *
 * @param ost a reference to an ostream object
 * @param cur_state the current state of the game
 */
void HoldEmGame::print_board(ostream &ost, HoldEmState cur_state) {
    switch (cur_state) {
        case HoldEmState::flop:
            ost << "\033[1mThe dealer has dealt the flop.\033[0m" << endl;
            ost << "\033[1mTHE BOARD:\033[0m ";
            common_cards.print(ost, 3);
            break;
        case HoldEmState::turn:
            ost << "\033[1mThe dealer has dealt the turn.\033[0m" << endl;
            ost << "\033[1mTHE BOARD:\033[0m ";
            common_cards.print(ost, 4);
            break;
        case HoldEmState::river:
            ost << "\033[1mThe dealer has dealt the river.\033[0m" << endl;
            ost << "\033[1mTHE BOARD:\033[0m ";
            common_cards.print(ost, 5);
            break;
        default: // do nothing for all other cases
            break;
    }
    ost << endl << endl;
}

/**
 * Print out the player_hands and their current hand rank.
 *
 * @param ost a reference to an ostream object
 * @param players a reference to a vector of Players
 */
void HoldEmGame::print_players(ostream &ost, vector<Player>& players) {
    ost << "\033[1;4mThese are the player_hands current hands from best to worst.\033[0m" << endl;
    for(Player player : players) {
        ost << "\033[1m" << player.player_name << "\033[0m has hand: ";
        // add 1 to hand size to prevent the program from adding a newline
        player.hand.print(ost, HOLDEM_RANKS_SIZE);
        ost << "--> This has a rank of\033[1m " << player.rank << "\033[0m";
        ost << endl;
    }
    ost << endl;
}

/**
 * collect cards from all player_hands
 */
void HoldEmGame::collect_cards() {
    for(auto& hand : hands) {
        deck.collect(hand);
    }
}

/**
 * Player constructor
 *
 * @param hand the player's hand (including the common cards)
 * @param player_name the player's name
 * @param rank the player's current hand rank
 */
HoldEmGame::Player::Player(CardSet<Suit, HoldEmRank> hand, string player_name, HoldEmHandRank rank)
    : hand(hand), player_name(player_name), rank(rank) {
    // empty constructor
}

/**
 * Evaluate a player's hand to return the rank of the hand.
 *
 * @param hand a reference to a CardSet object representing the player's hand
 *
 * @return the hand rank of the hand
 */
HoldEmHandRank HoldEmGame::holdem_hand_eval(const CardSet<Suit, HoldEmRank>& hand) {

    CardSet<Suit, HoldEmRank> hand_copy(hand);
    auto hand_begin = hand_copy.begin();
    auto hand_end = hand_copy.end();
    hand_copy.sort();

    // if the number of cards is not 5, cannot evaluate the hand so return undefined
    if(hand_end - hand_begin != HOLDEM_RANKS_SIZE) {
        return HoldEmHandRank::undefined;
    }

    bool straight = is_straight(hand_copy);
    bool flush = is_flush(hand_copy);
    vector<int> counts = how_many_same_rank(hand_copy); // counts should have 2 ints at minimum

    if(straight && flush) {
        return HoldEmHandRank::straight_flush;
    }
    // NOTE: some of these values are hardcoded on purpose, because the return makes it clear what it means
    if(counts[LARGEST_COUNT] == 4) {
        return HoldEmHandRank::four_of_a_kind;
    }
    if(counts[LARGEST_COUNT] == 3 && counts[SECOND_LARGEST_COUNT] == 2) {
        return HoldEmHandRank::full_house;
    }
    if(flush) {
        return HoldEmHandRank::flush;
    }
    if(straight) {
        return HoldEmHandRank::straight;
    }
    if(counts[LARGEST_COUNT] == 3) {
        return HoldEmHandRank::three_of_a_kind;
    }
    if(counts[LARGEST_COUNT] == 2 && counts[SECOND_LARGEST_COUNT] == 2) {
        return HoldEmHandRank::two_pair;
    }
    if(counts[LARGEST_COUNT] == 2) {
        return HoldEmHandRank::pair;
    }
    return HoldEmHandRank::x_high;

}


/**
 * Find if a player has a straight in their hand.
 *
 * @param hand the player's hand
 *
 * @return true if the player has a straight, false otherwise
 */
bool HoldEmGame::is_straight(CardSet<Suit, HoldEmRank>& hand) {
    HoldEmRank rank_iter = hand.begin()->rank;


    if(rank_iter == HoldEmRank::jack || rank_iter == HoldEmRank::queen || rank_iter == HoldEmRank::king) {
        return false; // cannot have a straight starting at these ranks
    }

    auto iter = hand.begin();
    for(; iter != hand.end(); ++iter) {
        // if the next card in hand is not the next card in the straight
        if(iter->rank != rank_iter) {
            return false;
        }

        if(rank_iter == HoldEmRank::five && iter == hand.end() - 1) {
            // wrap around to ace since that would be the next card in the straight based on ordering
            rank_iter = HoldEmRank::ace;
        } else {
            ++rank_iter;
        }
    }

    return true;
}


/**
 * Find if a player has a flush in their hand.
 *
 * @param hand the player's hand
 *
 * @return true if the player has a flush, false otherwise
 */
bool HoldEmGame::is_flush(CardSet<Suit, HoldEmRank>& hand) {
    Suit to_match = hand.begin()->suit;

    return std::all_of(hand.begin(), hand.end(),
                [to_match](Card<Suit, HoldEmRank> card) {
                    return card.suit == to_match;
                });
}


/**
 * Return a vector holding the number of cards with the same rank.
 *
 * @param hand the player's hand
 *
 * @return a vector of ints
 *
 * @note Example: if you have a hand of {J, J, J, Q, K} it will return 3, 1, 1
 */
vector<int> HoldEmGame::how_many_same_rank(CardSet<Suit, HoldEmRank>& hand) {
    auto iter1 = hand.begin();
    auto iter2 = hand.begin()+1;
    int count = 1;
    vector<int> counts = vector<int>();

    // use iterators to count similar cards while moving through the hand
    while(iter1 != hand.end()) {
        if(iter2 != hand.end() && (*iter1).rank == (*iter2).rank) {
            count++;
            iter2++;
        } else {
            counts.push_back(count);
            count = 1;
            iter1 = iter2;
            if(iter2 != hand.end()) {
                iter2++;
            }
        }
    }

    // Note: I am getting a Clang warning on std::greater but I am using cppreference example, so ignoring it
    std::sort(counts.begin(), counts.end(), std::greater<int>());
    return counts;
}


/**
 * Less than operator to compare two player_hands' hand's ranks.
 *
 * @param player1 a reference to the first player
 * @param player2 a reference to the second player
 *
 * @return true if the value of the rank of player1's hand is less than the rank of player2's hand, otherwise false
 *
 * @relatesalso HoldEmGame::Player
 */
bool operator<(const HoldEmGame::Player& player1, const HoldEmGame::Player& player2) {
    // instantly return if they are not the same rank
    if(player1.rank < player2.rank) {
        return true;
    } else if(player1.rank > player2.rank) {
        return false;
    }

    CardSet<Suit, HoldEmRank> p1 = player1.hand;
    CardSet<Suit, HoldEmRank> p2 = player2.hand;

    // sorting the hands to make later operations better
    p1.sort();
    p2.sort();

    auto p1_begin = p1.begin();
    auto p1_end = p1.end();
    auto p2_begin = p2.begin();
    auto p2_end = p2.end();

    // create copies of the vectors to be able to manipulate the hands in the function
    vector<Card<Suit, HoldEmRank> > p1_hand(p1_begin, p1_end);
    vector<Card<Suit, HoldEmRank> > p2_hand(p2_begin, p2_end);

    int size1 = 0; int size2 = 0;
    // a vector of maps where the first element is a map of player1's group ranks and the second is player2's map
    vector<std::map<int, HoldEmRank>> group_ranks;
    const int p1_index = 0; const int p2_index = 1;

    // by this point, they must have the same rank in hand, so only check player1's hand rank
    if(player1.rank == HoldEmHandRank::pair) {
        // higher pair, or if same, higher other card
        size1 = 2; size2 = 1;
        group_ranks = find_group_rank(size1, size2, p1_hand, p2_hand);
        if(group_ranks[p1_index][size1] < group_ranks[p2_index][size1]) {
            return true;
        } else if (group_ranks[p1_index][size1] > group_ranks[p2_index][size1]) {
            return false;
        } else {
            return find_highest_card(p1_hand, p2_hand);
        }
    }
    if(player1.rank == HoldEmHandRank::two_pair) {
        size1 = 2; size2 = 2;
        group_ranks = find_group_rank(size1, size2, p1_hand, p2_hand);
        size1++; // increment size1 since the larger rank pair will be mapped to 3 to avoid conflict in the mapping
        if(group_ranks[p1_index][size1] < group_ranks[p2_index][size1]) {
            return true;
        } else if (group_ranks[p1_index][size1] > group_ranks[p2_index][size1]) {
            return false;
        } else {
            if(group_ranks[p1_index][size2] < group_ranks[p2_index][size2]) {
                return true;
            } else if (group_ranks[p1_index][size2] > group_ranks[p2_index][size2]) {
                return false;
            } else {
                return find_highest_card(p1_hand, p2_hand);
            }
        }
    }
    if(player1.rank == HoldEmHandRank::three_of_a_kind) {
        size1 = 3; size2 = 1;
        group_ranks = find_group_rank(size1, size2, p1_hand, p2_hand);
        if(group_ranks[p1_index][size1] < group_ranks[p2_index][size1]) {
            return true;
        } else {
            return false;
        }
    }
    if(player1.rank == HoldEmHandRank::straight || player1.rank == HoldEmHandRank::straight_flush
        || player1.rank == HoldEmHandRank::x_high || player1.rank == HoldEmHandRank::flush) {
        return find_highest_card(p1_hand, p2_hand);
    }
    if(player1.rank == HoldEmHandRank::full_house) {
        size1 = 3; size2 = 2;
        group_ranks = find_group_rank(size1, size2, p1_hand, p2_hand);
        if(group_ranks[p1_index][size1] < group_ranks[p2_index][size1]) {
            return true;
        } else if (group_ranks[p1_index][size1] > group_ranks[p2_index][size1]) {
            return false;
        } else {
            if(group_ranks[p1_index][size2] < group_ranks[p2_index][size2]) {
                return true;
            } else {
                // the set of two cards are greater than or equal to each other
                return false;
            }
        }
    }
    if(player1.rank == HoldEmHandRank::four_of_a_kind) {
        size1 = 4; size2 = 1;
        group_ranks = find_group_rank(size1, size2, p1_hand, p2_hand);
        if(group_ranks[p1_index][size1] < group_ranks[p2_index][size1]) {
            return true;
        } else {
            return false;
        }
    }

    // should never reach here, but if it does, return false
    return false;
}

/**
 * Loops through the (sorted) cards to find which hand has the highest non-equal card.
 *
 * @param p1_hand the first player's hand
 * @param p2_hand the second player's hand
 *
 * @return true if player1's hand is less than player2's hand, otherwise false
 */
bool find_highest_card(vector<Card<Suit, HoldEmRank> > p1_hand, vector<Card<Suit, HoldEmRank> > p2_hand) {
    // go backwards through the (sorted) cards to find who has the larger final card
    for(int i = HOLDEM_RANKS_SIZE-1; i >= 0; i--) {
        HoldEmRank p1_card = p1_hand[i].rank;
        HoldEmRank p2_card = p2_hand[i].rank;
        if(p1_card < p2_card) {
            return true;
        } else if(p1_card > p2_card) {
            return false;
        }
    }
    // should very rarely reach this as the hands must be equal, still would return false (since it's strictly less than)
    return false;
}

/**
 * Find the rank of a "group" of cards.  See below for explanation on groups.
 *
 * @param group_size1 the size of the first group
 * @param group_size2 the size of the second group
 * @param p1_hand the first player's (sorted) hand
 * @param p2_hand the second player's (sorted) hand
 *
 * @return a vector of maps from int to HoldEmRank representing the ranks of each player's card groupings
 *
 * @note For example: a group could be a pair, therefore group_size1 would be 2 and group_size2 would just be 1.
 *      Alternatively for two pair, both group sizes would be 2 to show there are 2 "groups" of size 2.
 *
 * @note In the case of two pairs, the map will use a key of 3 for the larger of the two pairs to avoid a conflict.
 */
vector<std::map<int, HoldEmRank> > find_group_rank(int group_size1, int group_size2,
                                          vector< Card<Suit, HoldEmRank> > p1_hand,
                                          vector< Card<Suit, HoldEmRank> > p2_hand) {
    std::map<int, HoldEmRank> p1_map;
    std::map<int, HoldEmRank> p2_map;
    int p1_count = 1;
    int p2_count = 1;

    // we are only finding the rank of one group
    if(group_size2 == 1) {
        for(int i = FIRST_CARD; i < HOLDEM_RANKS_SIZE; i++) {
            for(int j = i+1; j < HOLDEM_RANKS_SIZE; j++) {

                if(p1_hand[i].rank == p1_hand[j].rank) {
                    // if the count is the same as the number of cards we are looking for, add it to the map
                    if(++p1_count == group_size1) {
                        p1_map[group_size1] = p1_hand[i].rank;
                    }
                }
                if(p2_hand[i].rank == p2_hand[j].rank) {
                    // if the count is the same as the number of cards we are looking for, add it to the map
                    if(++p2_count == group_size1) {
                        p2_map[group_size1] = p2_hand[i].rank;
                    }
                }
            }
        }
    }
    if(group_size2 == 2) {

        // two pair
        if(group_size1 == 2) {
            // loop for only first two cards as the first pair must be in the first 3 cards
            for(int i = FIRST_CARD; i < THIRD_CARD; i++) {
                if(p1_hand[i].rank == p1_hand[i+1].rank) {
                    p1_map[group_size2] = p1_hand[i].rank;
                }
                if(p2_hand[i].rank == p2_hand[i+1].rank) {
                    p2_map[group_size2] = p2_hand[i].rank;
                }
            }
            // loop for only third and fourth cards as the second pair must be in the last 3 cards
            for(int i = THIRD_CARD; i < FIFTH_CARD; i++) {
                // NOTE: These are being stored in group_size1+1 because 2 cannot be used twice in a map
                //          as a result, I am using 3 to store the larger of the pairs for two pairs
                if(p1_hand[i].rank == p1_hand[i+1].rank) {
                    p1_map[group_size1+1] = p1_hand[i].rank;
                }
                if(p2_hand[i].rank == p2_hand[i+1].rank) {
                    p2_map[group_size1+1] = p2_hand[i].rank;
                }
            }
        }

        // full house
        if(group_size1 == 3) {
            // if the grouping of 3 is in the first 3 cards, else in the last 3 cards
            if(p1_hand[FIRST_CARD].rank == p1_hand[THIRD_CARD].rank) {
                p1_map[group_size1] = p1_hand[FIRST_CARD].rank;
                p1_map[group_size2] = p1_hand[FOURTH_CARD].rank;
            } else {
                // group of 2 is in the first 2 cards
                p1_map[group_size2] = p1_hand[FIRST_CARD].rank;
                p1_map[group_size1] = p1_hand[THIRD_CARD].rank;
            }

            // same for player 2
            if(p2_hand[FIRST_CARD].rank == p2_hand[THIRD_CARD].rank) {
                p2_map[group_size1] = p2_hand[FIRST_CARD].rank;
                p2_map[group_size2] = p2_hand[FOURTH_CARD].rank;
            } else {
                // group of 2 is in the first 2 cards
                p2_map[group_size2] = p2_hand[FIRST_CARD].rank;
                p2_map[group_size1] = p2_hand[THIRD_CARD].rank;
            }
        }
    }

    vector< std::map<int, HoldEmRank> > vec{p1_map, p2_map};
    return vec;
}


// placed at the end because it is annoyingly large and fairly intuitive
/**
 * Overload the << operator to print a string representative of a hold em hand rank.
 *
 * @param ost a reference to an ostream object
 * @param hand_rank the passed in hand rank
 *
 * @return the reference to an ostream object that was passed in
 */
ostream& operator<<(ostream& ost, const HoldEmHandRank& hand_rank) {
    switch (hand_rank) {
        case HoldEmHandRank::x_high:
            ost << "High Card ";
            break;
        case HoldEmHandRank::pair:
            ost << "Pair ";
            break;
        case HoldEmHandRank::two_pair:
            ost << "Two Pair ";
            break;
        case HoldEmHandRank::three_of_a_kind:
            ost << "Three of a Kind ";
            break;
        case HoldEmHandRank::straight:
            ost << "Straight ";
            break;
        case HoldEmHandRank::flush:
            ost << "Flush ";
            break;
        case HoldEmHandRank::full_house:
            ost << "Full House ";
            break;
        case HoldEmHandRank::four_of_a_kind:
            ost << "Four of a Kind ";
            break;
        case HoldEmHandRank::straight_flush:
            ost << "Straight Flush ";
            break;
        default:
            ost << "Undefined ";
            break;
    }
    return ost;
}
