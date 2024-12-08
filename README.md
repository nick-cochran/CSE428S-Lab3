# CSE428S-Lab3

### Name: Nick Cochran

### Email: c.nick@wustl.edu

---

## Errors

- I ran into a ton of errors because I did a lot of the later steps before
trying to run 'make', mostly because it all ties together. I ran into a number
of linker errors, partly from not making the Go Fish Game a template header that
includes the source file which I had intended to do but forgot about until I figured
out the error. I also ran into quite a few errors in ways that I wrote my code,
which often came from typos or making simple mistakes that were pretty easy fixes.
I also needed to declare virtual default destructors for my game classes to compile
the code.

## Testing



## Design Choices

### Card Set Changes

- Most changes I made in the card set class template were fairly standard
and followed pretty closely with what the instructions recommended. I did,
however, add a get_size function which proved to be helpful in not needing
to do math with the begin and end pointers to get the size of the card set.
I also did not add typedefs for the suit and rank type as it didn't seem to make
sense even though the instructions recommended that.


### Uno Deck Implementation

- The Uno deck was pretty standard to implement and didn't require anything
major or super different as it was fairly similar to the previous decks I had made.
- I also made substantial changes to the way things are printed because of the
Uno deck having a very colorful deck.


### Go Fish Game

- The Go Fish game is easily where I spent the most time on this lab. TODO
- One big thing I did differently was to sort the hands of the players before
printing them out. The main reason I chose to do this is because if I was playing
Uno, I would definitely have a well-sorted hand to keep track of how many cards
of each rank I have.
- When asking for the input of rank, I chose to make the string for draw two and
draw four have an underscore instead of a space so it is read easier by the input
stream. If a player gets stuck on this or anything else a helpful message with
possible options will print after 5 or more attempts.






## Old README for Lab2

---

# CSE428S-Lab2

### Name: Nick Cochran

### Email: c.nick@wustl.edu

---

## Errors

- I ran into a few warnings that were being thrown because I did not have a copy-assignment operator
    when I did have a copy constructor, so I needed to tell the compiler to default initialize
    the copy-assignment operator.
- As I started testing HoldEm hand ranks I saw: "p9 has hand: 9♣ 3♣ 8♠ 10♠ 7♦ --> This has a rank of Pair"
    which is clearly not true so this was an error that I needed to fix.
    The problem was that I was using the postfix operator to set an iterator that keeps track of the
    next card in the hand so the program was double counting the first card in the hand.

## Testing

### Pinochle Melds

- I ran the program using the Pinochle parameters until I found at least 1 of each
    of the most common melds, and then I ran it until I found 1 of the much rarer 8 card melds.
    I also wanted to find at least one instance where a player had multiple melds.
    The first occurrence of each of these is below.
  - Player p2 has hand:
    
    K♣ Q♦ A♠ Q♥ A♥ J♠ A♦ 9♥ 10♥ K♦ Q♣ Q♠ 

    p2's melds: sixty queens 60
  - Player p3 has hand: 

    9♣ J♣ Q♥ Q♠ 9♦ K♥ J♠ A♣ K♠ J♦ K♥ K♦ 

    p3's melds: pinochle 40
  - Player p3 has hand: 

    9♥ K♦ Q♠ J♠ Q♣ 9♦ Q♠ K♠ Q♥ 10♣ K♣ K♥ 

    p3's melds: eighty kings 80
  - Player p3 has hand: 

    Q♣ K♥ 9♦ J♥ A♦ A♠ 10♠ J♠ J♣ K♣ A♥ A♣ 

    p3's melds: hundred aces 100 
  - Player p2 has hand: 

    K♦ J♣ J♠ 9♥ J♥ J♦ 9♦ A♣ 10♣ K♥ A♠ A♦ 

    p2's melds: forty jacks 40 
  - Player p4 has hand: 

    9♦ Q♠ Q♥ J♦ J♣ J♠ J♥ A♦ Q♠ K♥ J♦ Q♣ 
  
    p4's melds: forty jacks 40 double pinochle 300
  - Player p4 has hand: 

    K♥ K♥ Q♥ 10♦ A♦ K♠ K♠ K♦ J♥ K♣ K♦ K♣ 

    p4's melds: eight hundred kings 800 
    - Of note: This took a (probably broken) script and a long time to get.

## Hold Em Ranks

- I first tested that the program would find every hand rank by repeatedly running the program.
    Below I have listed the first instance of each hand rank that I encountered.
  - **X High:** p1 has hand: A♦ 5♦ 7♥ 9♣ 6♣ --> This has a rank of High Card
  - **Pair:** p4 has hand: 7♦ 4♠ 2♦ 6♣ 6♠ --> This has a rank of Pair 
  - **Two Pair:** p5 has hand: 5♦ 2♥ 2♦ 6♣ 6♠ --> This has a rank of Two Pair 
  - **Three of A Kind:** p5 has hand: 5♥ 9♥ 7♦ 5♠ 5♦ --> This has a rank of Three of a Kind
  - **Straight:** p2 has hand: 7♠ 8♥ 10♥ 9♥ 6♥ --> This has a rank of Straight
  - **Flush:** p5 has hand: 9♥ 3♥ K♥ 4♥ J♥ --> This has a rank of Flush 
  - **Full House:** p4 has hand: J♣ 8♥ J♦ 8♦ 8♣ --> This has a rank of Full House
  - **Four of A Kind** and **Straight Flush** are both very rare, but use the same functionality
    as other hand ranks that have had correct results, so I am using that information to assess
    that these two should be working as well.
- I also tested that the hands were printed using the correct ordering while, finding those
    hand ranks from the previous step.  Here is an example of the correct ordering from a few runs:
  - p2 has hand: J♦ 10♠ Q♦ 9♦ K♥ --> This has a rank of Straight 
    
    p3 has hand: A♥ K♦ Q♦ 9♦ K♥ --> This has a rank of Pair 

    p7 has hand: Q♥ 2♦ Q♦ 9♦ K♥ --> This has a rank of Pair 
    
    p4 has hand: J♠ J♥ Q♦ 9♦ K♥ --> This has a rank of Pair 
    
    p6 has hand: 8♠ 9♥ Q♦ 9♦ K♥ --> This has a rank of Pair 
    
    p9 has hand: 8♦ 9♠ Q♦ 9♦ K♥ --> This has a rank of Pair 

    p1 has hand: 2♥ A♣ Q♦ 9♦ K♥ --> This has a rank of High Card 
    
    p8 has hand: A♠ 3♣ Q♦ 9♦ K♥ --> This has a rank of High Card 
    
    p5 has hand: 7♥ 4♥ Q♦ 9♦ K♥ --> This has a rank of High Card 

## Overall Program Testing

- Most of this testing was done in the previous part of the lab, but I re-tested that 
    incorrect inputs of all kinds, including but not limited to the wrong number of player_hands
    an incorrect game name, and no inputs being provided.


## Design Choices

### Miscellaneous Changes/Choice

- I changed the Card Template, Suit, and both Pinochle and HoldEm Deck implementations
    of the << operator to print the cards in a more readable way, 
    also using the unicode and a red color (for hearts and diamonds) for each of the card suits.

### HoldEmGame Printing and Dealing

- The previous lab instructed me to print the hands and deal the hands inside of the play method,
    but I felt it important to note that I did this slightly differently.  In order to properly
    print the board before the state of the board changed, I called the print_board method inside of 
    the deal method.

### CardSet Copy Constructor

- I decided to implement my own copy constructor for the CardSet class because I felt like that
    was the safer implementation.  This ensures the copy constructor does what I want it to do.

### Meld Values Static Variable

- For the static variable in the PinochleGame Class that holds the values for each of the melds,
    I decided to go with the recommended implementation from the instructions. With this,
    I did hardcode the values on initialization, but because arrays are const,
    it is not at risk of being altered from this correct mapping of each meld to its value,
    therefore, there is still something making it clear what each of these hardcoded values means.

### Suit Independent Evaluation Function

- When implementing this function there were many design choices made that I felt
    I should document here. 
- I chose to create a map of Pinochle ranks to a vector of suits, 
    where each card of that rank would have its rank stored.  I then filled this map's vectors, 
    and was ready to find the melds a hand may have.  To do this, I first check if there are 
    enough of each suit to possibly have a meld for that rank.  If there are, I check
    if there are 8 suits, in which case that hand has all of the cards of that rank,
    meaning they have one of the 8 card melds.  Otherwise, I call a helper function that checks
    if the vector holds at least one of each suit, and if so add one of the 4 card melds
    to the passed in reference of melds.  Finally, I go through and count the number of
    Jacks of Diamonds and Queens of Spades to evaluate if there is a pinochle or double pinochle.
- I also thought about modularity at many times while implementing this function which ended up quite long.
    In the end, I didn't break most things out into other functions that I considered doing so with,
    because I felt it would be more complicated and difficult to follow with the way I had implemented it,
    and the requirements for breaking something off into a separate function.

### HoldEm Hand Evaluation Function

- I decided this function should work fairly differently from the previous function.  This time
    I did sort the hands and then I used 3 helper functions to determine if it is a straight,
    a flush, and how many similar ranks there are in each hand.  The last of these helper functions
    returns a vector of integers that will have the size of the largest grouping of cards
    with the same rank and then going down from there.  This allows me to determine all hand ranks
    that include multiple cards of the same rank or multiple sets of cards of the same rank.

### HoldEm Player Struct < Operator

- I decided it would be beneficial to once again sorted copies of the hands of both player_names.
    I also have a fairly unique implementation of this function that I should explain.
    For this, I create a vector of maps from int to HoldEmRank.  This vector will hold two maps,
    the first is for the first player and the second for the second player.  This vector will be
    created in a helper function called `find_group_rank` where the "group" represents a hand rank
    with multiple cards of the same rank, such as pair, two pair, three of a kind, etc.
    The function will fill the maps with an integer representing the hand rank (for instance, 2 for pair)
    mapped to the rank of that group.
- In the cases where groups are the same rank and it falls to finding the highest other card,
    I created a function, `find_highest_card`, that will loop through all of the cards
    to find the highest card not in the other player_names hand.  This is the fallback case for
    all places where I am instructed to do so, as well as with the cases where we need to
    find the highest card, such as with flushes and straights.
- There are a number of places that I do use hardcoded numbers, but I felt the context of
    where they are used makes it clear why that number is being used and making a constant would not be beneficial.
- A note that I included in comments and want to additionally include here-- because of my 
    implementation using a map, there is a conflict with the two pairs hand rank, which I resolved
    by making the larger ranked pair map from an int of 3 which is indicated in comments in a number of places in the code.

### HoldEm Board Dealing

- While testing my code and making things look nice, I decided to implement a new feature
    based on how cards are normally dealt in poker, by burning a card from the deck before
    dealing cards to the board.  This is overall doing nothing, but I thought it would be a fun addition.
- I also added some other helpful printouts to make it feel more like a game is being played.


### Use of `auto`

- I used auto in a few places in my program.  I tried to avoid using it in most places,
    but I did use it occasionally in for loops or when creating variables where the type
    is pretty clear, usually with variables that are meant to make things cleaner.