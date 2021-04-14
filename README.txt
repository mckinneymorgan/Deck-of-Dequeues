README for Deck of Dequeues
Original author: Morgan McKinney 1/2020

Turn-based card game where the randomized outcome is dependent on user input. The user can decide the number of players, cards, and turns. During the game, each player can get rid of a card from their hand and transfer it to another player. The goal of the game is for each player to have the lighest deck or reach a weight deck of 0.

cards.cpp: Contains entire implementation of card game. Each player is given 'c' number of cards, where the weight of the pile is based on the sum of all cards (in which the depth is multiplied by its value). The expected output is text detailing every turn of the generated card game,
until a winner is determined and displayed on screen.

cards.h: Program provides declarations of constants, structures, and functions utilized in cards.cpp. No input or invocation is necessary. An output is also not to be expected.

Makefile: Initial code provided by Dr. Finkel, with minor modifications. Present for easy user compilation of the aforementioned programs. Input is optional, but can be invoked using "make run", with the same user input as cards.cpp following 'run'. Output is similar to cards.cpp. Running this file is necessary in order to correctly import randGen.pl, whose output is neededto run cards.

tmpRun.out: Temporary output detailing what is outputted by cards.cpp. No input necessary. Can be read using the 'cat' command. Output is the output of cards.cpp.

Before anything else, make sure to correctly compile the program:
"g++ cards.cpp cards.h -o cards" or "make" or "make run". 
In order to invoke the program, simply put the following into the command line:
"./randGen.pl # | ./cards # # #".
Each pound sign represents the seed for random dice rolls, 
the number of players, cards, and turns respectively.
