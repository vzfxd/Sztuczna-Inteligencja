#ifndef PUZZLE15_STATE_H
#define PUZZLE15_STATE_H
typedef unsigned long long Board;

const int BITS_PER_TILE = 4;
const Board MASK = (1ULL << BITS_PER_TILE) - 1ULL;
const int BOARD_SIZE = 16;

class State {
public:
    Board board;
    unsigned int g_cost;
    unsigned int f_cost;
    unsigned char blank_pos;
    char parentMove;
    State* parent;

    State(State* parent, char move);
    State(Board board);
    int get_tile(int idx) const;
    void set_tile(int idx, int value);
    void printBoard() const;

};


#endif //PUZZLE15_STATE_H
