import java.util.Scanner;

public class connect_4 {

	public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
		int[][] board = new int[7][7];	//change to 7 6


		boolean gameActive = true;

		int totalOnBoard = 0;
		
		printBoard(board);

		while (gameActive) {
			
			//can fix so while loop up so there are not as many duplicate function calls 
			//by putting in a for loop of max = 2
			//I have not because I am trying to add a bot to this 
			//but might do that after I make the C version of this game
			
			System.out.println("It's player O|1's turn! Where would you like to go? (1 - " + board[0].length + ")");
			
			
			int Player1Placment = getNum(board);

			board[0][Player1Placment] = 1;
			totalOnBoard++;
			printBoard(board);

			swapMove(board);
			
			
			gameActive = gameStillActive(board, totalOnBoard);
			
			if(!gameActive) continue;
			
			System.out.println("It's player X|2's turn! Where would you like to go? (1 - " + board[0].length + ")");


			int Player2Placment = getNum(board);	//call Bot method here
			
			board[0][Player2Placment] = 2;
			totalOnBoard++;
			

			printBoard(board);

			swapMove(board);
			
			gameActive = gameStillActive(board, totalOnBoard);
		}

		//printBoard(board);	//might need this can't remember

		swapMove(board);
	}
	
	public static int getNum(int[][] board) {
		Scanner input = new Scanner(System.in);
		
		int num = 0;
		boolean worked = false;
		

		
		while(!worked){			//yeah a bit of this code doesn't work, lol
			
		try {
			num = input.nextInt() -1;
//			if(input.hasNext()) {		//fix this
//				System.out.println("this hit the moreOnLine Exception");
//				throw new Exception("Exception, there is still more data on the input line (bad ish)");
//			}
			worked = true;
			
		}catch(Exception e) {
			System.out.println("Bad input! Try again!");
			//input.next();
			
			input.nextLine();//probs only works if I use nextInt.
			
			worked = false;
			continue;
		}
		
		if(!validNum(num,board) || board[0][num] != 0) {
			System.out.println("Bad input! Try again!");
			worked = false;
			//maybe continue? (if I add more code after this if)
		}
		
		}//end while
		
		return num;
	}
	
	public static boolean validNum(int num, int[][] baord) {
		
		if(num < baord.length && num >= 0){
			return true;
		}
		
		return false;
	}

	public static void printBoard(int[][] board) {
		
		for(int i = 1; i< board.length+1; i++) {
			System.out.print(" " + i);
		}
		System.out.println();
		
		for (int i = 0; i < board.length; i++) {
			for (int j = 0; j < board[i].length; j++) {
				String convert = ".";
				if (board[i][j] == 1)
					convert = "O";
				else if (board[i][j] == 2)
					convert = "X";
				System.out.print("|" + convert);

			}
			System.out.println("|");
		}
		System.out.println();
//		if (board[i][j] == 1)
//			System.out.println("it's player 1's turn!");
//		if (board[i][j] == 2)
//			System.out.println("it's player 2's turn!");
//		System.out.println();
	}

	public static int[][] swapMove(int[][] board) {
		for (int i = 0; i < board.length - 1; i++) {
			for (int j = 0; j < board[i].length; j++) {
				if (board[i][j] > 0 && board[i + 1][j] == 0) {
					board[i + 1][j] = board[i][j];
					board[i][j] = 0;

					printBoard(board);
				}
			}
		}

		return board;

	}

	public static boolean gameStillActive(int[][] b, int totalOnBoard) {
		if (totalOnBoard < 7)
			return true;
		
		int totalSpots = b.length * b[0].length;	//this draw part might not work, lol
		if(totalOnBoard >= totalSpots) {
			System.out.println("It is a Draw!");
			return false;
		}

		for (int p = 1; p < 3; p++) {
			
			for (int i = 0; i < b.length; i++) {
				for (int j = 0; j < b[i].length - 3; j++) {
					if (b[i][j] == p && b[i][j+1] == p && b[i][j+2] == p && b[i][j+3] == p) {
						System.out.println("Player " + p + " Won!");
						return false;
					}
				}
			}
			
			for (int i = 0; i < b.length - 3; i++) {
				for (int j = 0; j < b[i].length; j++) {
					if (b[i][j] == p && b[i+1][j] == p && b[i+2][j] == p && b[i+3][j] == p) {
						System.out.println("Player " + p + " Won!");
						return false;
					}
				}
			}
			
			
			for (int i = 0; i < b.length - 3; i++) {
				for (int j = 0; j < b[i].length - 3; j++) {
					if (b[i][j] == p && b[i+1][j+1] == p && b[i+2][j+2] == p && b[i+3][j+3] == p) {
						System.out.println("Player " + p + " Won!");
						return false;
					}
				}
			}

			
			for (int i = b.length - 1; i > 3; i--) {
				for (int j = 0; j < b[i].length - 3; j++) {
					if (b[i][j] == p && b[i-1][j+1] == p && b[i-2][j+2] == p && b[i-3][j+3] == p) {
						System.out.println("Player " + p + " Won!");
						return false;
					}
				}
			}
			
			
		}//end of player loop



		return true;
	}//end of method


}//end of class
