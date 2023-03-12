#include <stdio.h>
#include <stdlib.h>     // For atoi, atof
#include <unistd.h>     // For sleep()
#include <math.h>       //for pow I think
#include <string.h>     
#include <ctype.h>      // isdigit(N) == 0 | (0==no, 1==yes)
#include <stdbool.h>    //for booleans


int getNum();
void printBoard();
void swapMove();
bool gameStillActive();

//length & width
int board[7][7];

int totalOnBoard = 0;

int sizeAll = (int)(sizeof(board) / sizeof(board[0][0]));
int sizeOne = (int)(sizeof(board) / sizeof(board[0]));
int sizeTwo = (int)(sizeof(board[0]) / sizeof(board[0][0]));

void main () {

  int playerNumber = 0;
  char playerText[2][20] = {"Player 1|O's turn!","Player 2|X's turn!"};;
  int N;

  bool gameActive = true;

  printBoard();

  while(gameActive){
    printf("%s\n", playerText[playerNumber%2]);

    N = getNum();

    board[0][N] = playerNumber%2+1;
    totalOnBoard++;

    printBoard();
    
    swapMove();
    playerNumber++;

    gameActive = gameStillActive();
  }

}

int getNum(){
  int N = -1;
  char tempFix[50];//should probs change to 50
  do{
  //printf("ready for input!\n");
  scanf("%s",tempFix);
  N = atoi(tempFix);

  if(N > sizeTwo || N < 1){//&&  isdigit(N) == 0
    printf("%s is bad input!\n", tempFix);
    continue;
  }

  if(!board[0][N-1] <= 0){
    printf("%d is full!\n", N);
    N = -1; //this is needed
    continue;
  }

  }while(N > sizeTwo || N < 1);
  N--;  //so it's now in the range 0 to (sizeTwo-1)

  return N;
}

void printBoard(){

  for(int i = 1; i< sizeTwo+1; i++) {
    printf(" %d", i);
	}
  printf("\n");
	bool extraSpace = false;
	for (int i = 0; i < sizeOne; i++) {
  	for (int j = 0; j < sizeTwo; j++) {
	  	char convert = '.';
	  	if (board[i][j] == 1)
		  	convert = 'O';
			else if (board[i][j] == 2)
		  	convert = 'X';
        
      if(j>9){
        printf(" ");
        extraSpace = true;
      }
      printf("|%c", convert);
		}
    if(extraSpace) printf(" ");
    
    printf("|\n");
	}
  printf("\n");

}

void swapMove(){

  for (int i = 0; i < sizeOne - 1; i++) {
	  for (int j = 0; j < sizeTwo; j++) {
		  if (board[i][j] > 0 && board[i + 1][j] == 0) {
			  board[i + 1][j] = board[i][j];
			  board[i][j] = 0;
			  printBoard();
		  }
		}
	}
  //return board;
}


bool gameStillActive(){//should not edit board

  if (totalOnBoard < 7)
	  return true;
		
	if(totalOnBoard >= sizeAll) {
    printf("It is a Draw!\n");
		return false;
	}

	for (int p = 1; p < 3; p++) {


	  for (int i = 0; i < sizeOne; i++) {
			for (int j = 0; j < sizeTwo - 3; j++) {
				if (board[i][j] == p && board[i][j+1] == p && board[i][j+2] == p && board[i][j+3] == p) {
          printf("Player %d Won!\n", p);
					return false;					}
			}
		}
			
		for (int i = 0; i < sizeOne - 3; i++) {
			for (int j = 0; j < sizeTwo; j++) {
				if (board[i][j] == p && board[i+1][j] == p && board[i+2][j] == p && board[i+3][j] == p) {
					printf("Player %d Won!\n", p);
					return false;
				}
			}
		}
			
			
		for (int i = 0; i < sizeOne - 3; i++) {
			for (int j = 0; j < sizeTwo - 3; j++) {
				if (board[i][j] == p && board[i+1][j+1] == p && board[i+2][j+2] == p && board[i+3][j+3] == p) {
					printf("Player %d Won!\n", p);
					return false;
				}
			}
		}

			
		for (int i = sizeOne - 1; i > 3; i--) {
			for (int j = 0; j < sizeTwo - 3; j++) {
				if (board[i][j] == p && board[i-1][j+1] == p && board[i-2][j+2] == p && board[i-3][j+3] == p) {
					printf("Player %d Won!\n", p);
					return false;
				}
			}
		}

  }

  return true;
}