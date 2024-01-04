#include <stdio.h>
#include <stdlib.h>     // For atoi, atof
#include <unistd.h>     // For sleep()
#include <math.h>       //for pow I think
#include <string.h>     
#include <ctype.h>      // isdigit(N) == 0 | (0==no, 1==yes)
#include <stdbool.h>    //for booleans
#include <pthread.h>	//Importing the Pthread Library

//to run the program
//	gcc -pthread C4V3.c			//C4V3== name so yours might be different
//	./a.out
//should be close to that

int getNum();  
void printBoard();
void swapMove();
bool gameStillActive();

void thread1Fun();
void thread2Fun();
void thread3Fun();

//length & width
int board[7][7];

int totalOnBoard = 0;

int sizeAll = (int)(sizeof(board) / sizeof(board[0][0]));
int sizeOne = (int)(sizeof(board) / sizeof(board[0]));
int sizeTwo = (int)(sizeof(board[0]) / sizeof(board[0][0]));

pthread_t tid1, tid2, tid3;                /* The thread IDs for each thread */
int t0, t1, t2, t3, winningPlayer;

void main () {

  int N;
  int playerNumber = 0;
  char playerText[2][20] = {"Player 1|O's turn!","Player 2|X's turn!"};;

  bool gameActive = true;

  printBoard();

  while(gameActive){
    printf("%s\n", playerText[playerNumber%2]);

    N = getNum();

    board[0][N] = playerNumber%2+1;
    totalOnBoard++;

    printBoard();
    
    swapMove(N);
    playerNumber++;

    gameActive = gameStillActive();
  }

}

int getNum(){
  int N = -1;
  char tempFix[50];//Temp fix to user input error
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

// i = y | j/N = x
void swapMove(int N){					
	for (int i = 0; i < sizeOne - 1; i++) {
		if (board[i][N] > 0 && board[i + 1][N] == 0) {
			board[i + 1][N] = board[i][N];
			board[i][N] = 0;
			printBoard();
		}
	}
}

bool gameStillActive(){//should not edit board

	if (totalOnBoard < 7) return true;
		
	if(totalOnBoard >= sizeAll) {
    	printf("It is a Draw!\n");
		return false;
	}
	pthread_create(&tid1, NULL, (void*)thread1Fun, NULL);
	pthread_create(&tid2, NULL, (void*)thread2Fun, NULL);
	pthread_create(&tid3, NULL, (void*)thread3Fun, NULL);

	int localP;
	//keep this so that all 4 threads are doing something.
	for (int i = 0; i < sizeOne; i++) {		//left to right
		for (int j = 0; j < sizeTwo - 3; j++) {
			if(board[i][j] > 0){
				localP = board[i][j];
				if (board[i][j+1] == localP && board[i][j+2] == localP && board[i][j+3] == localP) {
					t0 = 1;
					winningPlayer = localP;
					break;
					// return false;	//the most common win event (probs)
				}
			} 
		}
	}

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);

		//1 = false, 0 = true || has not responded.
	if(t0 > 0 || t1 > 0 || t2 > 0 || t3 > 0){//false
		int tSum = t0+t1+t2+t3;
		if(tSum >1) printf("Player %d Won in %d ways!\n", winningPlayer, tSum);
		else printf("Player %d Won!\n", winningPlayer);

		return false;
	}

  return true;//no win condition
}
				//Threads below

 //up and down
void thread1Fun(){
	int localP;
	for (int i = 0; i < sizeOne - 3; i++) {
		for (int j = 0; j < sizeTwo; j++) {
			if(board[i][j] > 0){
				localP = board[i][j];
				if (board[i+1][j] == localP && board[i+2][j] == localP && board[i+3][j] == localP) {
					t1 = 1;
					winningPlayer = localP;
					return;		//player won
				}
			}
		}
	}
}

void thread2Fun(){
	int localP;
	for (int i = 0; i < sizeOne - 3; i++) {
		for (int j = 0; j < sizeTwo - 3; j++) {
			if(board[i][j] > 0){
				localP = board[i][j];
				if (board[i+1][j+1] == localP && board[i+2][j+2] == localP && board[i+3][j+3] == localP) {
				t2 = 1;
				winningPlayer = localP;
				return;		//player won
			}
			}
		}
	}
}

void thread3Fun(){
	int localP;
	for (int i = sizeOne - 1; i > 3; i--) {
		for (int j = 0; j < sizeTwo - 3; j++) {
			if(board[i][j] > 0){
				localP = board[i][j];
				if (board[i-1][j+1] == localP && board[i-2][j+2] == localP && board[i-3][j+3] == localP) {
				t3 = 1;
				winningPlayer = localP;
				return;		//player won
			}
			}
		}
	}
}
