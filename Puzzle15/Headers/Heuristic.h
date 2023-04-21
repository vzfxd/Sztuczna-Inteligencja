#include <complex>
#include "State.h"
#include <iostream>
#include "Algorithms.h"


int cnvp[16] = {0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};
int conv[16] = {0,1,5,9,13,2,6,10,14,3,7,11,15,4,8,12};
int rows[16] = {3,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3};
int cols[16] = {3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2};

int linear_conflict2(State* state){
    int conflicts = 0;
    int distance = 0;
    for(int i=0; i<BOARD_SIZE;i++){
        int tile1 = state->get_tile(i);
        int tile1_row = (i / BITS_PER_TILE);
        int tile1_col = (i % BITS_PER_TILE);
        
        if(tile1!=0){
            distance+=abs(tile1_row-rows[tile1]) + abs(tile1_col-cols[tile1]);
        }
        
        for(int tile2_col=tile1_col+1; tile2_col<4; tile2_col++){
            if(tile1==0)break;
            int tile2_row = tile1_row;
            int tile2 = state->get_tile(tile2_col+tile2_row*BITS_PER_TILE);
            if(tile2==0)continue;
            
            if(tile1_row==rows[tile1] && tile2_row==rows[tile2] && tile1>tile2){
                conflicts++;
                int next_col = tile2_col + 1;
                if(next_col<4){
                    int next_row = tile2_row;
                    int next_tile = state->get_tile(next_col+next_row*BITS_PER_TILE);
                    if(tile2>next_tile && next_tile!=0)break;
                }
            }
        }

        std::swap(tile1_row,tile1_col);
        tile1 = state->get_tile(tile1_col+tile1_row*BITS_PER_TILE);

        for(int tile2_row=tile1_row+1; tile2_row<4; tile2_row++){
            if(tile1==0)break;
            int tile2_col = tile1_col;
            int tile2 = state->get_tile(tile2_col+tile2_row*BITS_PER_TILE);
            if(tile2==0)continue;

            if(tile1_col==cols[tile1] && tile2_col==cols[tile2] && tile1>tile2){
                conflicts++;
                int next_row = tile2_row+1;
                if(next_row<4){
                    int next_col = tile2_col;
                    int next_tile = state->get_tile(next_col+next_row*BITS_PER_TILE);
                    if(tile2>next_tile && next_tile!=0)break;
                }
            }
        }    
    }
    return 2*conflicts + distance;    
}

int inversion_distance(State* state) {
    int vertical = 0;
    int horizontal = 0;
    int distance = 0;
    for(int i=0; i<BOARD_SIZE; i++){
        int tile1 = state->get_tile(i);
        if(tile1==0)continue;
        int actual_row = (i / BITS_PER_TILE);
        int actual_col = (i % BITS_PER_TILE);
        distance+=abs(actual_row-rows[tile1]) + abs(actual_col-cols[tile1]);
        for(int j=i+1;j<BOARD_SIZE;j++){

            int tile2 = state->get_tile(j);
            tile1 = state->get_tile(i);
            if(tile2!=0 && tile1>tile2)vertical++;
            
            tile1 = conv[state->get_tile(cnvp[i])];
            int tile3 = conv[state->get_tile(cnvp[j])];
            
            if(tile3!=0 && tile1>tile3)horizontal++;
        }
    }
    return std::max((vertical/3+vertical%3)+(horizontal/3 +vertical%3),distance);
}