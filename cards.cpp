// Deck of Dequeues
// Original author: Morgan McKinney 1/2020

#include "cards.h"
#include <stdlib.h> // atoi()
#include <iostream>
using namespace std;

card::card() { // Constructor of cards
    weight = 0;
    next = NULL;
    previous = NULL;
}

// (Referenced www.youtube.com/watch?v=YJRRpXYldVQ)
void dequeue::addCard(int player, int cardWeight, dequeue playerDecks[]) { // Add card to dequeue
    playerDecks[player].c = new card;
    playerDecks[player].c->weight = cardWeight;
    // Determine if new card should go on top or bottom of deck
    // Then, create new link and relocate new top or bottom
    if (cardWeight >= playerDecks[player].top->weight) { // Card belongs on top
        // Populate new card, then relocate top
        playerDecks[player].c->next = playerDecks[player].top;
        playerDecks[player].c->previous = NULL;
        playerDecks[player].top = playerDecks[player].c;
    }
    else { // Card belongs on bottom
        // Populate new card, then relocate bottom
        playerDecks[player].c->previous = playerDecks[player].c;
	playerDecks[player].c->next = NULL;
        playerDecks[player].bottom = playerDecks[player].c;
    }
}

// (Referenced www.geeksforgeeks.org/delete-a-given-node-in-linked-list...
// ...-under-given-constraints/ for both removeTop() and removeBottom() )
void dequeue::removeTop(int player, dequeue playerDecks[]) { // Remove top card
    // Copy old data onto head and store address
    playerDecks[player].top->weight = playerDecks[player].top->next->weight;
    playerDecks[player].c = playerDecks[player].top->next;
    // Remove link
    playerDecks[player].top->next = playerDecks[player].top->next->next;
}

void dequeue::removeBottom(int player, dequeue playerDecks[]) { // Remove bottom card
    // Copy old data onto tail and store address
    playerDecks[player].bottom->weight = playerDecks[player].bottom->previous->weight;
    playerDecks[player].c = playerDecks[player].bottom->previous;
    // Remove link
    playerDecks[player].bottom->previous = playerDecks[player].bottom->previous->previous;
}

// (Referenced www.geeksforgeeks.org/linked-list-set-1-introduction/)
int dequeue::calculateWeight(int player, dequeue playerDecks[]) { // Calculate total weight of deck
    int total = 0; // Start with no weight
    playerDecks[player].c = playerDecks[player].top; // Start at top of deck
    while (playerDecks[player].c != NULL) { // Traverse all cards
        total = total + playerDecks[player].c->weight;
	playerDecks[player].c = playerDecks[player].c->next; // Go to next card
    }
    return total;
}

int gameIsWon(int players, int turn, int current, dequeue playerDecks[]) { // Check if game is won
    int winner = 0; // No winner until win condition satisfied
    for (int i = 0; i < players; i++) { // Are any decks empty?
        if (playerDecks[i].calculateWeight(i, playerDecks) == 0) {
            winner = i+1;
        }
    }
    if (turn >= current) { // Max turns reached, find lightest deck
        int min = playerDecks[0].calculateWeight(0, playerDecks); // Assume min
        int temp;
        for (int i = 0; i < players; i++) { // Compare deck sizes to local min
            temp = playerDecks[i].calculateWeight(i, playerDecks);
            if (temp < min) {
                min = temp; // Update min
                winner = i+1;
            }
        }
    }
    return winner;
}

int rollDice(int sides) { // Roll dice of variable sides
    int roll;
    // (Discussed idea with Dina Birioukova)
    cin >> roll; // Random number piped from randGen.pl
    roll = roll % sides + 1; // Use modulus to stay within range
    return roll;
}

int main(int argc, char * argv[]) {
    if (argc != 4) { // Check for correct amount of arguments
        cout << "Usage: ./cards numPlayers numCards numTurns" << endl;
        return 0;
    }
    // Initialize user inputted players, cards, and turns
    // (Referenced www.cplusplus.com/articles/DEN36Up4/)
    int numPlayers = atoi(argv[1]);
    int numCards = atoi(argv[2]);
    int numTurns = atoi(argv[3]);
    // Dynamically allocate array to store player dequeues
    // (Referenced cplusplus.com/doc/tutorial/dynamic)
    dequeue * playerDecks = new dequeue [numPlayers];
    // Create doubly linked list
    // (Referenced youtube.com/watch?v=YJRRpXYldVQ)
    for (int i = 0; i < numPlayers; i++) {
        playerDecks[i].top = NULL;
        playerDecks[i].bottom = NULL;
        for (int j = 1; j <= numCards; j++) {
            playerDecks[i].c = new card;
            playerDecks[i].c->weight = j * j;
            if (j == 1) { // Previous pointer is null if it's the first card
                playerDecks[i].c->previous = NULL;
	        playerDecks[i].top = playerDecks[i].c; // First card is on top
            }
            else {
                playerDecks[i].c->previous = playerDecks[i].bottom;
            }
            playerDecks[i].c->next = playerDecks[i].c;
            playerDecks[i].bottom = playerDecks[i].c; // Last card on bottom
        }
        playerDecks[i].c->next = NULL;
    }
    // Initialize remaining necessary variables
    int gameWinner = 0;
    int currentTurn = 1;
    int advantagedPlayer;
    int receivingPlayer;
    int pileSide;
    int newCardWeight;
    int totalWeight;
    // Play until someone wins or max turns is reached
    while (gameWinner == 0 && currentTurn <= numTurns) {
        advantagedPlayer = rollDice(numPlayers);
        receivingPlayer = rollDice(numPlayers);
        pileSide = rollDice(2); // Two sides to a deck
        // Display turn on screen
        cout << "Turn " << currentTurn << ": player " << advantagedPlayer;
        cout << " sends a card to " << receivingPlayer;
        if (pileSide == 1) { // Determine which side of the pile is discarded
            cout << ", from top" << endl;
            // Remove top card and transfer to receiver    
            newCardWeight = playerDecks[advantagedPlayer-1].top->weight;   
            playerDecks[advantagedPlayer-1].removeTop(advantagedPlayer-1, playerDecks);
            playerDecks[receivingPlayer-1].addCard(receivingPlayer-1, newCardWeight, playerDecks);
        }
        else {
            cout << ", from bottom" << endl;
            // Remove bottom card and transfer to receiver
            newCardWeight = playerDecks[advantagedPlayer-1].bottom->weight;
            playerDecks[advantagedPlayer-1].removeBottom(advantagedPlayer-1, playerDecks);
            playerDecks[receivingPlayer-1].addCard(receivingPlayer-1, newCardWeight, playerDecks);
        }
        for (int i = 0; i < numPlayers; i++) { // Display weight of every deck
            cout << "        Player " << i+1 << ": Weight = ";
            totalWeight = playerDecks[i].calculateWeight(i, playerDecks);
            cout << totalWeight << endl;
        }
        currentTurn += 1; // Increment turn number
        gameWinner = gameIsWon(numPlayers, numTurns, currentTurn, playerDecks); // Check if anyone won
    }
    // Display winner
    if (currentTurn >= numTurns) { // Max turns reached
        cout << "No more turns. Player " << gameWinner << " wins." << endl;
    }
    else { // A player has no cards left
        cout << "Game is over: Player " << gameWinner << " has no cards left." << endl;
    }
    return 0;
}
