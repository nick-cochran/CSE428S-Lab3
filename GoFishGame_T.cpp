/*
 * GoFishGame.cpp
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This source file contains the GoFishGame template class function definitions.
 */

#include "GoFishGame_T.h"


/**
 * Play function to run the game of Go Fish.
 *
 * @tparam GF_Suit the template suit type for this game of Go Fish.
 * @tparam GF_Rank the template rank type for this game of Go Fish.
 * @tparam GF_Deck the template deck type for this game of Go Fish.
 *
 * @return an integer representing success.
 */
template<typename GF_Suit, typename GF_Rank, typename GF_Deck>
int GoFishGame<GF_Suit, GF_Rank, GF_Deck>::play() {
    deal();
    int num_players = player_names.size();

    for(int p_num = 0; p_num < num_players; ++p_num) {
        while(collect_books(p_num));
    }

    // run the game one round at a time
    int round_num = 1;
    vector<int> players_num_books = vector(num_players, 0);
    while(true) {
        cout << endl;
        cout << BOLD << "STARTING ROUND " << round_num << RESET << endl;
        // run the round
        for(int p = 0; p < num_players; ++p) {
            if(!player_still_in[p]) {
                continue;
            }
            if(std::count(player_still_in.begin(), player_still_in.end(), true) == 1) {
                break;
            }

            while(turn(p));
        }

        // end of the round
        cout << BOLD << "END OF ROUND " << round_num << RESET << endl;
        ++round_num;

        cout << BOLD << "Books Made By Each Player: " << RESET << endl;
        for(int p = 0; p < num_players; ++p) {
            int num_books = (books[p].get_size())/FOUR_OF_A_KIND;
            cout << player_names[p] << ": " << num_books << endl;
            players_num_books[p] = num_books;
        }

        // check if the game is over
        bool game_over = false;
        bool hands_empty = std::all_of(player_hands.begin(), player_hands.end(),
                                       [](cardSet_t hand) -> bool {
                                            return hand.is_empty();
                                        });
        if(deck.is_empty() && hands_empty) {
            game_over = true;
        }

        int players_in = count(player_still_in.begin(), player_still_in.end(), true);
        if(players_in <= 1) {
            game_over = true;
        }

        if(game_over) {
            break;
        }
    }

    // game over, print out winner(s)
    int max = *std::max_element(players_num_books.begin(), players_num_books.end()).base();
    for(int p = 0; p < num_players; ++p) {
        if(players_num_books[p] == max) {
            cout << player_names[p] << " is a winner with " << max << " books!" << endl;
        }
    }
    return SUCCESS;
}

/**
 * Constructor for the Go Fish Game class.
 *
 * @tparam GF_Suit the template suit type for this game of Go Fish.
 * @tparam GF_Rank the template rank type for this game of Go Fish.
 * @tparam GF_Deck the template deck type for this game of Go Fish.
 *
 * @param argc the length of the input array.
 * @param argv the input array of strings.
 */
template<typename GF_Suit, typename GF_Rank, typename GF_Deck>
GoFishGame<GF_Suit, GF_Rank, GF_Deck>::GoFishGame(int argc, const char **argv) : Game(argc, argv) {

    deck = GF_Deck();
    for(GF_Rank rank = get_first(deck); rank != GF_Rank::undefined; ++rank) {
        int count = std::count_if(deck.begin(), deck.end(),
              [rank](card_t card) -> auto {
                return card.rank == rank;
              });
        if(count < FOUR_OF_A_KIND) {
            throw std::logic_error("The Go Fish Deck Does Not Have 4 Cards of Each Rank.");
        }
    }

    int num_players = player_names.size();
    player_hands = vector(num_players, CardSet<GF_Suit, GF_Rank>());
    books = vector(num_players, CardSet<GF_Suit, GF_Rank>());
    player_still_in = vector(num_players, true);
}

/**
 * Deal out the cards to each player in the game.
 *
 * @tparam GF_Suit the template suit type for this game of Go Fish.
 * @tparam GF_Rank the template rank type for this game of Go Fish.
 * @tparam GF_Deck the template deck type for this game of Go Fish.
 */
template<typename GF_Suit, typename GF_Rank, typename GF_Deck>
void GoFishGame<GF_Suit, GF_Rank, GF_Deck>::deal() {
    deck.shuffle();
    int num_players = player_names.size();

    int hand_size;
    // if only two players, deal 7 cards, else deal 5
    if(num_players == 2) {
        hand_size = HAND_SIZE_2PLAYERS;
    } else {
        hand_size = HAND_SIZE_MORE_PLAYERS;
    }

    for(auto &player : player_hands) {
        for(int i = 0; i < hand_size; ++i) {
            deck >> player;
        }
    }
}

/**
 * Run a turn for a player in the game of Go Fish.
 *
 * @tparam GF_Suit the template suit type for this game of Go Fish.
 * @tparam GF_Rank the template rank type for this game of Go Fish.
 * @tparam GF_Deck the template deck type for this game of Go Fish.
 *
 * @param player_num the number (in the vectors) of the player whose turn it is.
 *
 * @return true if the player found the card they were looking for, false otherwise.
 */
template<typename GF_Suit, typename GF_Rank, typename GF_Deck>
bool GoFishGame<GF_Suit, GF_Rank, GF_Deck>::turn(unsigned int player_num) {
    cardSet_t& player_hand = player_hands[player_num];
    cardSet_t& player_books = books[player_num];

    // print their hand and books
    cout << BOLD << "Player " << player_names[player_num] << "'s Hand:" << RESET << endl;
    player_hand.sort();
    player_hand.print(cout, GF_CARDS_PER_LINE);
    cout << endl;
    cout << BOLD << "Player " << player_names[player_num] << "'s Books:" << RESET << endl;
    player_books.print(cout, FOUR_OF_A_KIND);
    cout << endl;

    // ask the player for the rank they want to ask for
    GF_Rank rank_req;
    cout << "What card rank would you like to ask for?" << endl;
    cin >> rank_req;
    int times_asked = 0;
    while(rank_req == GF_Rank::undefined) {
        ++times_asked;
        cout << "Please try again with a valid rank." << endl;
        if(times_asked >= 5) {
            GF_Rank ranks = get_first(deck);
            cout << "Valid Ranks: ";
            while(ranks != GF_Rank::undefined) {
                GF_Rank test_rank = ranks;
                if(++test_rank != GF_Rank::undefined) {
                    cout << ranks << ", ";
                } else {
                    cout << ranks << endl;
                }
                ++ranks;
            }
        }
        cin >> rank_req;
    }
    // ask the player who they want to ask
    size_t player_ask;
    cout << "What player (number) would you like to ask for this card?" << endl;
    cin >> player_ask;
    --player_ask; // decrement so that the inputs are 1 indexed and it matches the vector being 0 indexed
    while(player_ask >= player_hands.size() || player_ask == player_num || !player_still_in[player_ask]) {
        cout << "Please try again with a valid player number.";
        if(player_ask == player_num) {
            cout << " You must select a different player than yourself.";
        }
        if(!player_still_in[player_ask]) {
            cout << " That player is out of the game.";
        }
        cout << endl;
        cin >> player_ask;
        --player_ask;
    }

    // request that rank from that player and return true if successful
    if(player_hand.request(player_hands[player_ask], rank_req)) {
        cout << "You got a " << rank_req << " from Player " << player_names[player_ask] << "!" << endl;
        while(collect_books(player_num));
        return true;
    }

    // tell them to go fish
    cout << BOLD << "Oh No!" << RESET << " Player " << player_names[player_ask]
        << " does not have a " << rank_req << "." << endl;
    cout << BOLD << "GO FISH!" << RESET << endl;

    // draw from the deck and lose if the deck is empty
    if(!deck.is_empty()) {
        cardSet_t old_player_hand(player_hand);
        deck >> player_hand;
        // check the last card because >> pushes the card to the back
        if((*(player_hand.end()-1)).rank == rank_req) {
            cout << "You got lucky and drew the card you asked for. Ask again!" << endl << endl;
            while(collect_books(player_num));
            return true;
        } else {
            cout << endl;
            return false;
        }
    }
    cout << endl;
    deck.collect(player_hand);
    cout << BOLD << "You Are Out! Better luck next time!" << RESET << endl << endl;
    player_still_in[player_num] = false;
    return false;
}

/**
 * Collect the books from a player's hand.
 *
 * @tparam GF_Suit the template suit type for this game of Go Fish.
 * @tparam GF_Rank the template rank type for this game of Go Fish.
 * @tparam GF_Deck the template deck type for this game of Go Fish.
 *
 * @param player_num the number (in the vectors) of the player whose books are being collected.
 *
 * @return true if a book was collected, false otherwise.
 */
template <typename GF_Suit, typename GF_Rank, typename GF_Deck>
bool GoFishGame<GF_Suit, GF_Rank, GF_Deck>::collect_books(unsigned int player_num) {
    cardSet_t &hand = player_hands[player_num];

    auto base_iter = hand.begin();
    auto end_iter = hand.end();
    while(base_iter < end_iter) {
        int num_of_rank = std::count_if(base_iter, end_iter,
                                        [base_iter](card_t card) {
                                            return card.rank == base_iter->rank;
                                        });
        if(num_of_rank >= FOUR_OF_A_KIND) {

            GF_Rank rank = base_iter->rank;
            std::function<bool(card_t&)> predicate = [rank](card_t card) {
                return card.rank == rank;
            };

            books[player_num].collect_if(hand, predicate);
            end_iter = hand.end();
            return true;
        }
        ++base_iter;
    }

    return false;
}