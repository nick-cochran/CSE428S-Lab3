/*
 * UnoDeck.cpp
 * Author: Nick Cochran
 * Email: c.nick@wustl.edu
 *
 * This source file contains the definitions for the UnoDeck class and the functions
 *      for the overloaded operators for the Color and UnoRank enums.
 */

#include "UnoDeck.h"


/**
 * Constructor for the UnoDeck Class that creates the deck of cards.
 */
UnoDeck::UnoDeck() {

    // one zero of each color
    for(Color color = Color::red; color != Color::black; ++color) {
        cards.emplace_back(color, UnoRank::zero);
    }

    // two cards of each color for ranks one through nine, skip, reverse, and draw_two
    for(UnoRank rank = UnoRank::one; rank != UnoRank::draw_four; ++rank) {
        for(Color color = Color::red; color != Color::black; ++color) {
            cards.emplace_back(color, rank);
            cards.emplace_back(color, rank);
        }
    }

    // four black cards of ranks draw_four, wild, and blank
    for(UnoRank rank = UnoRank::draw_four; rank != UnoRank::undefined; ++rank) {
        cards.emplace_back(Color::black, rank);
        cards.emplace_back(Color::black, rank);
        cards.emplace_back(Color::black, rank);
        cards.emplace_back(Color::black, rank);
    }
}

/**
 * Overloads the << operator for the Color enum to print a string representation.
 *
 * @param ost a reference to an ostream object
 * @param uno_color the passed in Color by reference
 *
 * @return the passed in ostream object reference
 */
ostream& operator<<(ostream& ost, const Color& uno_color) {
    switch(uno_color) {
        case Color::red:
            ost << RED_WHITE << " Red ";
            return ost;
        case Color::green:
            ost << GREEN_WHITE << " Green ";
            return ost;
        case Color::blue:
            ost << BLUE_WHITE << " Blue ";
            return ost;
        case Color::yellow:
            ost << YELLOW_WHITE << " Yellow ";
            return ost;
        case Color::black:
            ost << BLACK_WHITE << " Black ";
            return ost;
        default:
            ost << " ? ";
            return ost;
    }
}

/**
 * Overloads the ++prefix operator for the Color enum to increment to the next color.
 *
 * @param uno_color a reference to a Color object
 *
 * @return the incremented Color object
 */
Color& operator++(Color& uno_color) {
    switch(uno_color) {
        case Color::red:
            return uno_color = Color::green;
        case Color::green:
            return uno_color = Color::blue;
        case Color::blue:
            return uno_color = Color::yellow;
        case Color::yellow:
            return uno_color = Color::black;
        default:
            return uno_color = Color::undefined;
    }
}

/**
 * Overloads the << operator for the UnoRank enum to print a string representation.
 *
 * @param ost a reference to an ostream object
 * @param uno_rank the passed in UnoRank by reference
 *
 * @return the passed in ostream object reference
 */
ostream& operator<<(ostream& ost, const UnoRank& uno_rank) {
    switch(uno_rank) {
        case UnoRank::zero:
            ost << "0";
            return ost;
        case UnoRank::one:
            ost << "1";
            return ost;
         case UnoRank::two:
            ost << "2";
            return ost;
        case UnoRank::three:
            ost << "3";
            return ost;
        case UnoRank::four:
            ost << "4";
            return ost;
        case UnoRank::five:
            ost << "5";
            return ost;
        case UnoRank::six:
            ost << "6";
            return ost;
        case UnoRank::seven:
            ost << "7";
            return ost;
        case UnoRank::eight:
            ost << "8";
            return ost;
        case UnoRank::nine:
            ost << "9";
            return ost;
        case UnoRank::skip:
            ost << "Skip";
            return ost;
        case UnoRank::reverse:
            ost << "Reverse";
            return ost;
        case UnoRank::draw_two:
            ost << "Draw Two";
            return ost;
        case UnoRank::draw_four:
            ost << "Draw Four";
            return ost;
        case UnoRank::wild:
            ost << "Wild";
            return ost;
        case UnoRank::blank:
            ost << "Blank";
            return ost;
        default:
            ost << "?";
            return ost;
    }
}

/**
 * Overloads the >> operator for the UnoRank enum to read in a string representation of a card rank.
 *
 * @param ist a reference to an istream object
 * @param uno_rank the passed in UnoRank by reference
 *
 * @return the passed in istream object reference
 */
istream& operator>>(istream& ist, UnoRank& uno_rank) {
    string rank_name;
    ist >> rank_name;
    std::transform(rank_name.begin(), rank_name.end(), rank_name.begin(), ::tolower);

    if(rank_name == "0") {
        uno_rank = UnoRank::zero;
    } else if(rank_name == "1") {
        uno_rank = UnoRank::one;
    } else if(rank_name == "2") {
        uno_rank = UnoRank::two;
    } else if(rank_name == "3") {
        uno_rank = UnoRank::three;
    } else if(rank_name == "4") {
        uno_rank = UnoRank::four;
    } else if(rank_name == "5") {
        uno_rank = UnoRank::five;
    } else if(rank_name == "6") {
        uno_rank = UnoRank::six;
    } else if(rank_name == "7") {
        uno_rank = UnoRank::seven;
    } else if(rank_name == "8") {
        uno_rank = UnoRank::eight;
    } else if(rank_name == "9") {
        uno_rank = UnoRank::nine;
    } else if(rank_name == "skip") {
        uno_rank = UnoRank::skip;
    } else if(rank_name == "reverse") {
        uno_rank = UnoRank::reverse;
    } else if(rank_name == "draw_two") {
        uno_rank = UnoRank::draw_two;
    } else if(rank_name == "draw_four") {
        uno_rank = UnoRank::draw_four;
    } else if(rank_name == "wild") {
        uno_rank = UnoRank::wild;
    } else if(rank_name == "blank") {
        uno_rank = UnoRank::blank;
    } else {
        uno_rank = UnoRank::undefined;
    }
    return ist;
}

/**
 * Overloads the ++prefix operator for the UnoRank enum to increment to the next card rank.
 *
 * @param uno_rank a reference to a UnoRank object
 *
 * @return the incremented UnoRank object
 */
UnoRank& operator++(UnoRank& uno_rank) {
    switch(uno_rank) {
        case UnoRank::zero:
            return uno_rank = UnoRank::one;
        case UnoRank::one:
            return uno_rank = UnoRank::two;
        case UnoRank::two:
            return uno_rank = UnoRank::three;
        case UnoRank::three:
            return uno_rank = UnoRank::four;
        case UnoRank::four:
            return uno_rank = UnoRank::five;
        case UnoRank::five:
            return uno_rank = UnoRank::six;
        case UnoRank::six:
            return uno_rank = UnoRank::seven;
        case UnoRank::seven:
            return uno_rank = UnoRank::eight;
        case UnoRank::eight:
            return uno_rank = UnoRank::nine;
        case UnoRank::nine:
            return uno_rank = UnoRank::skip;
        case UnoRank::skip:
            return uno_rank = UnoRank::reverse;
        case UnoRank::reverse:
            return uno_rank = UnoRank::draw_two;
        case UnoRank::draw_two:
            return uno_rank = UnoRank::draw_four;
        case UnoRank::draw_four:
            return uno_rank = UnoRank::wild;
        case UnoRank::wild:
            return uno_rank = UnoRank::blank;
        default:
            return uno_rank = UnoRank::undefined;
    }
}

/**
 * Returns the first rank in the UnoRank enum.
 *
 * @return the first rank in the UnoRank enum
 */
UnoRank get_first(UnoDeck&) {
    return UnoRank::zero;
}