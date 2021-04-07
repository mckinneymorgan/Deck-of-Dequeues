README for Deck of Dequeues
Original author: Morgan McKinney 1/2020

cards.cpp:

Program is intended to play out a turn-based card game.
Given user inputted number of players, cards, and turns, every game will play
out differently. Each player is given 'c' number of cards, where the weight 
of the pile is based on the sum of all cards (in which the depth is 
multiplied by its value). Every turn, a player is able to get rid of a card
from their stack and give it to another player. The goal is to have the lightest deck at the end of the maximum amount of turns, or to reach a weight of 0.

Before anything else, make sure to correctly compile the program:
"g++ cards.cpp cards.h -o cards" or "make" or "make run". 
In order to invoke the program, simply put the following into the command line:
"./randGen.pl # | ./cards # # #".
Each pound sign represents the seed for random dice rolls, 
the number of players, cards, and turns respectively.

The expected output is text detailing every turn of the generated card game,
until a winner is determined and displayed on screen.

cards.h:

Program provides declarations of constants, structures, and functions utilized
in cards.cpp. No input or invocation is necessary. An output is also not to be
expected.

Makefile:

Initial code provided by Dr. Finkel, with minor modifications. Present for easy user compilation of the aforementioned programs. Input is
optional, but can be invoked using "make run", with the same user input as cards.cpp following 'run'. Output is similar to cards.cpp. Running this file is
necessary in order to correctly import randGen.pl, whose output is needed
to run cards.

tmpRun.out:

Temporary output detailing what is outputted by cards.cpp. No input necessary.
Can be read using the 'cat' command. Output is the output of cards.cpp.
