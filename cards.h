// Deck of Dequeues
// Original author: Morgan McKinney 1/2020

using namespace std;

struct card {
    card(); // Constructor
    int weight;
    card * next;
    card * previous;
};
struct dequeue {
    card * top;
    card * bottom;
    card * c;
    void addCard(int player, int cardWeight, dequeue playerDecks[]);
    void removeTop(int player, dequeue playerDecks[]);
    void removeBottom(int player, dequeue playerDecks[]);
    int calculateWeight(int player, dequeue playerDecks[]);
};
int gameIsWon(int players, int turn, int current, dequeue playerDecks[]);
int diceRoll(int sides);
