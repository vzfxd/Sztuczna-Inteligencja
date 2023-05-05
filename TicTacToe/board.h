/****************************
Maciej Gębala (CC BY-NC 4.0)
Plansza ver. 0.1
2023-03-30
****************************/
#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int board[5][5];
int _player;

const int win[28][4][2] = { 
  { {0,0}, {0,1}, {0,2}, {0,3} },
  { {1,0}, {1,1}, {1,2}, {1,3} },
  { {2,0}, {2,1}, {2,2}, {2,3} },
  { {3,0}, {3,1}, {3,2}, {3,3} },
  { {4,0}, {4,1}, {4,2}, {4,3} },
  { {0,1}, {0,2}, {0,3}, {0,4} },
  { {1,1}, {1,2}, {1,3}, {1,4} },
  { {2,1}, {2,2}, {2,3}, {2,4} },
  { {3,1}, {3,2}, {3,3}, {3,4} },
  { {4,1}, {4,2}, {4,3}, {4,4} },
  { {0,0}, {1,0}, {2,0}, {3,0} },
  { {0,1}, {1,1}, {2,1}, {3,1} },
  { {0,2}, {1,2}, {2,2}, {3,2} },
  { {0,3}, {1,3}, {2,3}, {3,3} },
  { {0,4}, {1,4}, {2,4}, {3,4} },
  { {1,0}, {2,0}, {3,0}, {4,0} },
  { {1,1}, {2,1}, {3,1}, {4,1} },
  { {1,2}, {2,2}, {3,2}, {4,2} },
  { {1,3}, {2,3}, {3,3}, {4,3} },
  { {1,4}, {2,4}, {3,4}, {4,4} },
  { {0,1}, {1,2}, {2,3}, {3,4} },
  { {0,0}, {1,1}, {2,2}, {3,3} },
  { {1,1}, {2,2}, {3,3}, {4,4} },
  { {1,0}, {2,1}, {3,2}, {4,3} },
  { {0,3}, {1,2}, {2,1}, {3,0} },
  { {0,4}, {1,3}, {2,2}, {3,1} },
  { {1,3}, {2,2}, {3,1}, {4,0} },
  { {1,4}, {2,3}, {3,2}, {4,1} }
};

const int lose[48][3][2] = {
  { {0,0}, {0,1}, {0,2} }, { {0,1}, {0,2}, {0,3} }, { {0,2}, {0,3}, {0,4} }, 
  { {1,0}, {1,1}, {1,2} }, { {1,1}, {1,2}, {1,3} }, { {1,2}, {1,3}, {1,4} }, 
  { {2,0}, {2,1}, {2,2} }, { {2,1}, {2,2}, {2,3} }, { {2,2}, {2,3}, {2,4} }, 
  { {3,0}, {3,1}, {3,2} }, { {3,1}, {3,2}, {3,3} }, { {3,2}, {3,3}, {3,4} }, 
  { {4,0}, {4,1}, {4,2} }, { {4,1}, {4,2}, {4,3} }, { {4,2}, {4,3}, {4,4} }, 
  { {0,0}, {1,0}, {2,0} }, { {1,0}, {2,0}, {3,0} }, { {2,0}, {3,0}, {4,0} }, 
  { {0,1}, {1,1}, {2,1} }, { {1,1}, {2,1}, {3,1} }, { {2,1}, {3,1}, {4,1} }, 
  { {0,2}, {1,2}, {2,2} }, { {1,2}, {2,2}, {3,2} }, { {2,2}, {3,2}, {4,2} }, 
  { {0,3}, {1,3}, {2,3} }, { {1,3}, {2,3}, {3,3} }, { {2,3}, {3,3}, {4,3} }, 
  { {0,4}, {1,4}, {2,4} }, { {1,4}, {2,4}, {3,4} }, { {2,4}, {3,4}, {4,4} }, 
  { {0,2}, {1,3}, {2,4} }, { {0,1}, {1,2}, {2,3} }, { {1,2}, {2,3}, {3,4} }, 
  { {0,0}, {1,1}, {2,2} }, { {1,1}, {2,2}, {3,3} }, { {2,2}, {3,3}, {4,4} }, 
  { {1,0}, {2,1}, {3,2} }, { {2,1}, {3,2}, {4,3} }, { {2,0}, {3,1}, {4,2} }, 
  { {0,2}, {1,1}, {2,0} }, { {0,3}, {1,2}, {2,1} }, { {1,2}, {2,1}, {3,0} }, 
  { {0,4}, {1,3}, {2,2} }, { {1,3}, {2,2}, {3,1} }, { {2,2}, {3,1}, {4,0} }, 
  { {1,4}, {2,3}, {3,2} }, { {2,3}, {3,2}, {4,1} }, { {2,4}, {3,3}, {4,2} }
};

void setBoard()
{
  for(int i=0; i<5; i++)
    for(int j=0; j<5; j++)
      board[i][j]=0;
}

void printBoard()
{
  printf("  1 2 3 4 5\n");
  for(int i=0; i<5; i++) {
    printf("%d",i+1);
    for(int j=0; j<5; j++ )
      switch(board[i][j]) {
        case 0: printf(" -"); break;
        case 1: printf(" X"); break;
        case 2: printf(" O"); break;
      }
    printf("\n");
  }
  printf("\n");
}

bool setMove(int move, int player)
{
  int i,j;
  i = (move/10)-1;
  j = (move%10)-1;
  if( (i<0) || (i>4) || (j<0) || (j>4) ) return false; 
  if( board[i][j]!=0 ) return false;
  board[i][j] = player;
  return true;
}

bool wCheck(int b[5][5],int player)
{
  for(int i=0; i<28; i++)
    if( (b[win[i][0][0]][win[i][0][1]]==player) && (b[win[i][1][0]][win[i][1][1]]==player) && (b[win[i][2][0]][win[i][2][1]]==player) && (b[win[i][3][0]][win[i][3][1]]==player) )
      return true;
  return false;
}

bool lCheck(int b[5][5],int player)
{
  for(int i=0; i<48; i++)
    if( (b[lose[i][0][0]][lose[i][0][1]]==player) && (b[lose[i][1][0]][lose[i][1][1]]==player) && (b[lose[i][2][0]][lose[i][2][1]]==player) )
      return true;
  return false;
}

int evalTestxd(int b[5][5]){

  int opponent = 3-_player;
  int score = 0;

  ///////////////////// WYGRANE ////////////////
  for(int i=0; i<28; i++){

    int player_count = 0;
    int opponent_count = 0;

    for(int j=0; j<4; j++){

      if(b[win[i][j][0]][win[i][j][1]]==_player){
        player_count++;
      }else if(b[win[i][j][0]][win[i][j][1]]==opponent){
        opponent_count++;
      }

    }

    if(opponent_count == 4) return -10000;
    else if(player_count == 4) return 10000;
    else if(player_count == 1 && opponent_count == 0) score += 2;
    else if(player_count == 0 && opponent_count == 1) score -= 2;
    else if(player_count == 2 && opponent_count == 0) score += 5;
    else if(player_count == 0 && opponent_count == 2) score -= 4;
    else if(player_count == 3 && opponent_count == 0) score += 9;
    else if(player_count == 0 && opponent_count == 3) score -= 9;

  }
  ////////////////////////////////////////////////////



  ////////////////// PRZEGRANE //////////////////////
  for(int i=0; i<48;i++){

    int player_count = 0;
    int opponent_count = 0;

    for(int j=0; j<3; j++){

      if(b[lose[i][j][0]][lose[i][j][1]]==_player){
        player_count++;
      }else if(b[lose[i][j][0]][lose[i][j][1]]==opponent){
        opponent_count++;
      }

    }

    if(player_count == 3) return -20000;
    else if(opponent_count == 3) return 20000;
    else if(player_count == 2 && opponent_count == 0) score -= 3;
    else if(player_count == 0 && opponent_count == 2) score += 4;
    else if(player_count == 1 && opponent_count == 0) score -= 1;
    else if(player_count == 0 && opponent_count == 1) score += 2;

  }

  return score;
}

const int rows[25] = {0,0,0,0,0, 1,1,1,1,1, 2,2,2,2,2, 3,3,3,3,3, 4,4,4,4,4};
const int cols[25] = {0,1,2,3,4, 0,1,2,3,4, 0,1,2,3,4, 0,1,2,3,4, 0,1,2,3,4};
const int order[25] = {0,1,2,3,4, 9,14,19,24, 23,22,21,20, 15,10,5, 6,7,8, 13,18, 17,16, 11, 12};

int min(int a, int b){
    return a > b ? b : a;
}

int max(int a, int b){
    return a > b ? a : b;
}

int minimax(int board[5][5], int depth, bool isMax,int player, int alpha, int beta)
{
    if(depth==0 || wCheck(board,_player) || wCheck(board,3-_player) || lCheck(board,3-_player) || lCheck(board,_player)){
      return evalTestxd(board);
    }
  
    if (isMax){
      int best = INT_MIN;
      for (int i = 0; i<25; i++){
        if(board[rows[i]][cols[i]]==0){
          board[rows[i]][cols[i]] = player;
          best = max( best, minimax(board, depth-1, !isMax, 3-player,alpha,beta) );
          board[rows[i]][cols[i]] = 0;
          alpha = max(alpha,best);
          if(beta<=alpha){
            break;
          }
        }
      }
      return best;
    }
  
    else{
      int best = INT_MAX;
      for (int i = 0; i<25; i++){
        if (board[rows[i]][cols[i]]==0){
          board[rows[i]][cols[i]] = player;
          best = min(best, minimax(board, depth-1, !isMax, 3-player,alpha,beta));
          board[rows[i]][cols[i]] = 0;
          beta = min(beta,best);
          if(beta<=alpha){
            break;
          }
        }
      }
      return best;
    }
}

int findBestMove(int board[5][5], int depth)
{
    int bestVal = INT_MIN;
    int bestMove = 11;
  
    for (int i = 0; i<5; i++){
        for (int j = 0; j<5; j++){
            if (board[i][j]==0)
            {
                board[i][j] = _player;
                int moveVal = minimax(board, depth-1, false,3-_player,INT_MIN,INT_MAX);
                board[i][j] = 0;
                if (moveVal > bestVal)
                {
                    bestMove = (i+1)*10 + j+1;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}