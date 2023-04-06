#include <stdio.h>
#include <stdlib.h>     // For atoi, atof
#include <unistd.h>     // For sleep()
#include <math.h>       //for pow I think
#include <string.h>     
#include <ctype.h>      // isdigit(N) == 0 | (0==no, 1==yes)
#include <stdbool.h>    //for booleans
#include <pthread.h>	//Importing the Pthread Library


//to run the program
//	gcc -pthread C4Updated.c		//C4Updated == name so yours might be different
//	./a.out
//should be close to that
//also could do 
//	gcc -pthread C4Updated.c -w		//removes the warnings
//	./a.out

int getNum();  
void printBoard();
void swapMove();
bool gameStillActive();

void thread1Fun(int* p);
void thread2Fun(int* p);
void thread3Fun(int* p);

//length & width
int board[7][7];

int totalOnBoard = 0;

int sizeAll = (int)(sizeof(board) / sizeof(board[0][0]));
int sizeOne = (int)(sizeof(board) / sizeof(board[0]));
int sizeTwo = (int)(sizeof(board[0]) / sizeof(board[0][0]));

pthread_t tid1, tid2, tid3;                /* The thread ids for each thread */
int t1, t2, t3, t4;

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

	for (int p = 1; p < 3; p++) {//would be cool to remove this loop (if done well)

		pthread_create(&tid1, NULL, thread1Fun, &p);
		pthread_create(&tid2, NULL, thread2Fun, &p);
		pthread_create(&tid3, NULL, thread3Fun, &p);


		//keep this so that all 4 threads are doing something.
		for (int i = 0; i < sizeOne; i++) {		//left to right
			for (int j = 0; j < sizeTwo - 3; j++) {
				if (board[i][j] == p && board[i][j+1] == p && board[i][j+2] == p && board[i][j+3] == p) {
    				printf("Player %d Won!\n", p);
					void pthread_exit(void* tid1);
					void pthread_exit(void* tid2);	//void* might be wrong idk
					void pthread_exit(void* tid3);
					return false;	//the most common win event (probs)
									//so it could be the shortest
				}
			}
		}


		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
		pthread_join(tid3, NULL);
		//1 = false, 2 = true, 0 = has not responded.
		while(t1 == 0 || t2 == 0 || t3 == 0);
		//printf("t1:%d t2:%d t3:%d\n",t1,t2,t3);
		if(t1 == 1 | t2 == 1 | t3 == 1){//false
			printf("Player %d Won!\n", p);
			return false;
		}

//https://www.educative.io/answers/what-are-pthreads-in-c-cpp
  }
  return true;
}

				//Threads below

 //up and down
void thread1Fun(int* p){
	for (int i = 0; i < sizeOne - 3; i++) {
		for (int j = 0; j < sizeTwo; j++) {
			if (board[i][j] == *p && board[i+1][j] == *p && board[i+2][j] == *p && board[i+3][j] == *p) {
				t1 = 1;
				return;		//player won
			}
		}
	}
	t1 = 2;
}

void thread2Fun(int* p){
	for (int i = 0; i < sizeOne - 3; i++) {
		for (int j = 0; j < sizeTwo - 3; j++) {
			if (board[i][j] == *p && board[i+1][j+1] == *p && board[i+2][j+2] == *p && board[i+3][j+3] == *p) {
				t2 = 1;
				return;		//player won
			}
		}
	}
	t2 = 2;
}

void thread3Fun(int* p){
	for (int i = sizeOne - 1; i > 3; i--) {
		for (int j = 0; j < sizeTwo - 3; j++) {
			if (board[i][j] == *p && board[i-1][j+1] == *p && board[i-2][j+2] == *p && board[i-3][j+3] == *p) {
				t3 = 1;
				return;		//player won
			}
		}
	}
	t3 = 2;
}