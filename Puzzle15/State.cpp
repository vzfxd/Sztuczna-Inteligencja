#include "Headers/State.h"
#include <iostream>


void State::printBoard()const{
    std::string board = "";
    int k = 0;
    for(int i=0; i<16;i++){
        k+=1;
        if(this->get_tile(i)<10){
            board =  board+" "+ "0"+std::to_string(this->get_tile(i));
        }else{
            board = board+" "+ std::to_string(this->get_tile(i));
        }
        
        if(k==4) {
            std::cout<<board<<std::endl;
            board = "";
            k=0;
        }
    }
    std::cout<<std::endl<<std::endl;
}

int State::get_tile(int idx) const {
    return (this->board >> ((15-idx)*BITS_PER_TILE)) & MASK;
}

void State::set_tile(int idx, int value){
    this->board &= ~(MASK << ((15-idx) * BITS_PER_TILE)); // zerowanie bitów
    this->board |= static_cast<Board>(value) << ((15-idx) * BITS_PER_TILE); // ustawianie bitów
}

const char blank_offset[] = {-1, 1, -4, 4};


State::State(State* parent, char move){
    this->parent = parent;
    this->board = parent->board;
    this->blank_pos = parent->blank_pos + blank_offset[move];
    this->parentMove = move;
    this->g_cost = parent->g_cost + 1;
}

State::State(Board board){
    this->parent = nullptr;
    this->board = board;
    this->g_cost = 0;
    this->parentMove = 4;
    unsigned short i;
    for(i=0; i<16; i++){
        if(get_tile(i)==0) break;
    }
    this->blank_pos = i;
}
