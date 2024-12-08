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
the code. I also ran into a problem with straights not being found in HoldEm because
of a change to fix my error in the previous lab, but I caught that through testing
both HoldEm and Pinochle again and fixed it once I figured that out.

## Testing

- I did extensive testing which consisted of running the program with all previous
requirements and then doing a lot of testing with both Go Fish and the Uno deck
in particular. I also did a lot of play testing to find all the bugs in the
program, of which there were many. One that kept plaguing me was a problem in
collecting the books, resulting in an infinite loop. I learned after a while that
my code was fine other than a simple missing '&'. It was not a reference to the
hand so it wasn't actually changing. In my play testing, I finally made it to the
end of a game and found out that it didn't end even with 1 player left which helped
me to find a bug where it would not end if the last player left is after the player
that just lost as the for loop would just continue to that last player left. They 
then would be completely unable to do anything because there are no other players to
ask for cards from.

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

- The Go Fish game is easily where I spent the most time on this lab.
- One big thing I did differently was to sort the hands of the players before
printing them out. The main reason I chose to do this is because if I was playing
Uno, I would definitely have a well-sorted hand to keep track of how many cards
of each rank I have.
- When asking for the input of rank, I chose to make the string for draw two and
draw four have an underscore instead of a space so it is read easier by the input
stream. If a player gets stuck on this or anything else a helpful message with
possible options will print after 5 or more attempts.
- I also wanted to mention that the instructions weren't 100% clear to me on
whether I should be printing how many books a player got that round or how many
they have total, but I went with printing how many each player has total so we
have a constant tally of that.
- I also made a change to how argc and argv were input into the go fish constructor
to make up for the extra input of the deck type so the player names lined up correctly.