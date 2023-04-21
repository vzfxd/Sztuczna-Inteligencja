#ifndef PUZZLE15_ALGORITHMS_H
#define PUZZLE15_ALGORITHMS_H

#include <queue>
#include <unordered_set>
#include <cstdio>
#include <complex>
#include "State.h"
#include <iostream>
#include "Heuristic.h"
#include <random>
#include <algorithm>
#include <cstring>

static const Board GOAL_STATE = 0x123456789abcdef0ULL;
static const int possible_moves[4][16] = {     // GDZIE MOŻNA RUSZYĆ PUSTYM POLEM 
        {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1}, // LEWO
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0}, // PRAWO
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // GORA
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0} // DOL
};
const int opp_moves[] = {1, 0, 3, 2,777};

struct pq_cmp {
    bool operator()(const State* s1, const State* s2) const
    {
        return s1->f_cost > s2->f_cost;
    }
};

struct set_cmp {
    bool operator()(const State* s1,const State* s2) const
    {
        return s1->board == s2->board;
    }
};

struct Hash{
    size_t operator()(const State* state)const{
        return std::hash<Board>()(state->board);
    }
};

int inv_count(State* state){
    int inv = 0;
    for(int i=0; i<BOARD_SIZE; i++){
        int tile1 = state->get_tile(i);
        if(tile1==0)continue;
        for(int j=i+1;j<BOARD_SIZE;j++){
            int tile2 = state->get_tile(j);
            if(tile2==0)continue;
            if(tile1>tile2)inv++;
        }
    }
    return inv;
}

bool isSolvable(State* state){
    int blankX = 3-(state->blank_pos/4)+1;
    int inv = inv_count(state);
    if(blankX & 1){
        return !(inv & 1);
    }else{
        return inv & 1;
    }
}

State* create_random_state(){
    int nums[15];
    for (int i = 1; i < 16; i++) {
        nums[i-1] = i;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(nums, nums + 15, g);

    Board board = 0x0ULL;
    for (int i = 0; i < 15; i++) {
        board |= static_cast<Board>(nums[i]) << ((15-i)*4);
    }

    State* randomState = new State(board);
    bool solvable = isSolvable(randomState);
    if(!solvable){
        delete randomState;
        return create_random_state();
    }else{
        return randomState;
    }   
}


void printSolution(State* goal){
    State* current = goal;
    while(current->parent){
        current->printBoard();
        current = current->parent;
    }
    current->printBoard();
    std::cout<<"rozwiązano w: "<<goal->g_cost<<" ruchach"<<std::endl;
}

void a_star(State* initial){

    initial->printBoard();
    
    if(!isSolvable(initial)){
        std::cout<<"not solvable"<<std::endl;
        return;
    }
    
    initial->f_cost = linear_conflict2(initial);

    int i = 0;
    std::unordered_set<State*,Hash,set_cmp> visited;
    std::priority_queue<State*,std::vector<State*>,pq_cmp> pq;
    pq.push(initial);
    visited.insert(initial);

    while(true){
        State* state = pq.top();
        pq.pop();

        auto diffrent = visited.find(state);
        if(state->f_cost != (*diffrent)->f_cost){
            delete state;
            continue;
        }

        if(state->board==GOAL_STATE){
            printSolution(state);
            break;
        }

        i++;

        for(char move=0; move<4; move++){
            if(!possible_moves[move][state->blank_pos]) continue;
            if(opp_moves[move]==state->parentMove) continue; 
            
            State* child = new State(state,move);
            child->set_tile(state->blank_pos, state->get_tile(child->blank_pos));
            child->set_tile(child->blank_pos,0);
            child->f_cost = child->g_cost + linear_conflict2(child); 
            
            auto search = visited.find(child);
            if(search == visited.end()){
                visited.insert(child);
                pq.push(child);      
            }else if(child->f_cost < (*search)->f_cost){
                pq.push(child);
                visited.erase(search);
                visited.insert(child);
            }else delete child;
    
        }      
    }
    std::cout<<"odwiedzonych elementów:"<<i<<std::endl;
    for (auto &element : visited){
        delete element;
    }
}

#endif //PUZZLE15_ALGORITHMS_H
