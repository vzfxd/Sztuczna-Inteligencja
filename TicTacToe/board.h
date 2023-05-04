/****************************
Maciej Gębala (CC BY-NC 4.0)
Plansza ver. 0.1
2023-03-30
****************************/
#pragma once
#include <stdio.h>
#include <stdbool.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int board[5][5];
int player;

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

bool winCheck(int player)
{
  bool w=false;
  for(int i=0; i<28; i++)
    if( (board[win[i][0][0]][win[i][0][1]]==player) && (board[win[i][1][0]][win[i][1][1]]==player) && (board[win[i][2][0]][win[i][2][1]]==player) && (board[win[i][3][0]][win[i][3][1]]==player) )
      w=true;
  return w;
}

bool loseCheck(int player)
{
  bool l=false;
  for(int i=0; i<48; i++)
    if( (board[lose[i][0][0]][lose[i][0][1]]==player) && (board[lose[i][1][0]][lose[i][1][1]]==player) && (board[lose[i][2][0]][lose[i][2][1]]==player) )
      l=true;
  return l;
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

int evaluation(int b[5][5]){
  int opponent = 3-player;
  int score = 0;
  for(int i=0; i<28; i++){

    //Sprawdza wygrywające kombinacje, które nieskładają sie tylko z 0
    if(b[win[i][0][0]][win[i][0][1]]!=0 || b[win[i][1][0]][win[i][1][1]]!=0 || b[win[i][2][0]][win[i][2][1]]!=0 || b[win[i][3][0]][win[i][3][1]]!=0){

      //Nie ma żadnego symbolu opponenta, tzn że możliwa jest do ułożenia kombinacja wygrywająca dla playera
      if(b[win[i][0][0]][win[i][0][1]]!=opponent && b[win[i][1][0]][win[i][1][1]]!=opponent && b[win[i][2][0]][win[i][2][1]]!=opponent && b[win[i][3][0]][win[i][3][1]]!=opponent){
        
        //Wygrana playera
        if(b[win[i][0][0]][win[i][0][1]]==player && b[win[i][1][0]][win[i][1][1]]==player && b[win[i][2][0]][win[i][2][1]]==player && b[win[i][3][0]][win[i][3][1]]==player){
          return 1000;
        }
        score++;
      }

      //Nie ma żadnego symbolu playera, tzn że możliwa jest do ułożenia kombinacja wygrywająca dla opponenta
      else if(b[win[i][0][0]][win[i][0][1]]!=player && b[win[i][1][0]][win[i][1][1]]!=player && b[win[i][2][0]][win[i][2][1]]!=player && b[win[i][3][0]][win[i][3][1]]!=player){
        
        //Wygrana opponenta
        if(b[win[i][0][0]][win[i][0][1]]==opponent && b[win[i][1][0]][win[i][1][1]]==opponent && b[win[i][2][0]][win[i][2][1]]==opponent && b[win[i][3][0]][win[i][3][1]]==opponent){
          return -1000;
        }
        score--;
      }
      
    }

  }

  for(int i=0; i<48;i++){

     //Sprawdza przegrywające kombinacje, które nieskładają sie tylko z 0
    if(b[lose[i][0][0]][lose[i][0][1]]!=0 || b[lose[i][1][0]][lose[i][1][1]]!=0 || b[lose[i][2][0]][lose[i][2][1]]!=0){

      //Nie ma żadnego symbolu playera, tzn że możliwa jest do ułożenia kombinacja przegrywająca dla opponenta
      if(b[lose[i][0][0]][lose[i][0][1]]!=player && b[lose[i][1][0]][lose[i][1][1]]!=player && b[lose[i][2][0]][lose[i][2][1]]!=player){
        
        //Przegrana opponenta
        if(b[lose[i][0][0]][lose[i][0][1]]==opponent && b[lose[i][1][0]][lose[i][1][1]]==opponent && b[lose[i][2][0]][lose[i][2][1]]==opponent){
          return 1000;
        }
        score++;
      }
      
      //Nie ma żadnego symbolu opponenta, tzn że możliwa jest do ułożenia kombinacja przegrywająca dla playera
      else if(b[lose[i][0][0]][lose[i][0][1]]!=opponent && b[lose[i][1][0]][lose[i][1][1]]!=opponent && b[lose[i][2][0]][lose[i][2][1]]!=opponent){
        
        //Przegrana playera
        if(b[lose[i][0][0]][lose[i][0][1]]==player && b[lose[i][1][0]][lose[i][1][1]]==player && b[lose[i][2][0]][lose[i][2][1]]==player){
          return -1000;
        }
        score--;
      }
      
    }

  }

  return score;

}

int minimax(int board[5][5], int depth, bool isMax,int player, int alpha, int beta)
{
    int score = evaluation(board);
    if(depth==0 || score==1000 || score==-1000 ) return score;
  
    if (isMax){
        int best = -1111;
        bool stop = false;
        for (int i = 0; i<5; i++){
            for (int j = 0; j<5; j++){
                if (board[i][j]==0){
                    board[i][j] = player;
                    best = MAX( best, minimax(board, depth-1, !isMax, 3-player,alpha,beta) );
                    board[i][j] = 0;
                    alpha = MAX(alpha,best);
                    if(beta<=alpha){
                      stop = true;
                      break;
                    }   
                }
            }
            if(stop)break;
        }
        return best;
    }
  
    else{
        int best = 1111;
        bool stop = false;
        for (int i = 0; i<5; i++){
            for (int j = 0; j<5; j++){
                if (board[i][j]==0){
                    board[i][j] = player;
                    best = MIN(best, minimax(board, depth-1, !isMax, 3-player,alpha,beta));
                    board[i][j] = 0;
                    beta = MIN(beta,best);
                    if(beta<=alpha){
                      stop = true;
                      break;
                    }
                }
            }
            if(stop)break;
        }
        return best;
    }
}

int findBestMove(int board[5][5], int player, int depth)
{
    int bestVal = -1111;
    int bestMove = 11;
  
    for (int i = 0; i<5; i++){
        for (int j = 0; j<5; j++){
            if (board[i][j]==0)
            {
                board[i][j] = player;
                int moveVal = minimax(board, depth, false,3-player,-1111,1111);
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


// int evalTest(int b[5][5]){

//   int opponent = 3-player;
//   int score = 0;

//   // WYGRANE //
//   for(int i=0; i<28; i++){

//     int player_count = 0;
//     int opponent_count = 0;
//     int blank_count = 0;

//     for(int j=0; j<4; j++){

//       if(b[win[i][j][0]][win[i][j][1]]==0){
//         blank_count++;
//       }else if(b[win[i][j][0]][win[i][j][1]]==opponent){
//         opponent_count++;
//       }else{
//         player_count++;
//       }

//     }
    
//     if(blank_count!=4){
//       if(opponent_count==0){
//         if(player_count==4) return 1000;
//         score++;
//       }
//       else if(opponent_count==0){
//         if(opponent_count==4) return -1000;
//         score--;
//       }
//     }

//   }

//   // PRZEGRANE //
//   for(int i=0; i<48;i++){

//     int player_count = 0;
//     int opponent_count = 0;
//     int blank_count = 0;
//     for(int j=0; j<3; j++){

//       if(b[lose[i][j][0]][lose[i][j][1]]==0){
//         blank_count++;
//       }else if(b[lose[i][j][0]][lose[i][j][1]]==opponent){
//         opponent_count++;
//       }else{
//         player_count++;
//       }

//     }

//     if(blank_count!=3){
//       if(player_count==0){
//         if(opponent_count==3) return 1000;
//         score++;
//       }
//       else if(opponent_count==0){
//         if(player_count==3) return -1000;
//         score--;
//       }
//     }

//   }

//   return score;
// }