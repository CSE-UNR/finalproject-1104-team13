//Authors: Chase Grundy and Duncan Brown//
//Date: 5/2/2024//
//Title: Connect Four//

#include <stdio.h>
#include <stdbool.h>

#define BOARD_HEIGHT 7
#define BOARD_WIDTH 7

#define SAVE_GAME "saveGame.txt"
#define TEST "test.txt"

//Load Game From File Pointer//
void loadGame(char board[BOARD_HEIGHT][BOARD_WIDTH], const char* filename){
	FILE* saveGame;
	saveGame = fopen(filename, "r");

//File Validity Check//
	if(saveGame == NULL){
        	printf("Cannot open saved game from %s.\n", filename);
        for(int i = 0; i < BOARD_HEIGHT; i++) {
        	for(int j = 0; j < BOARD_WIDTH; j++) {
                	board[i][j] = '.';
		}
	}
        return;
}

	for(int i = 0; i < BOARD_WIDTH; i++)
		for(int j = 0; j < BOARD_HEIGHT; j++)
			fscanf(saveGame, " %c", &board[i][j]);
            
//Close the File//
	fclose(saveGame);
}

//Board Display//
void displayBoard(char board[BOARD_HEIGHT][BOARD_WIDTH]){
	for(int i = 0; i < BOARD_HEIGHT; i++){
        	for(int j = 0; j < BOARD_WIDTH; j++)
            		printf("%c", board[j][i]);
        printf("\n");
	}
}

//Movement Input Prompt//
void getMove(int turn, int *move){
	int tempMove = 0;
	bool player1Turn;
	if(turn % 2 != 0){
        	player1Turn = true;
	} else {
        	player1Turn = false;
    	}
	printf(player1Turn ? "Player 1's Turn! Enter Column: " : "Player 2's Turn! Enter Column: ");
	
	//Enact Movement Input//
	scanf("%i", &tempMove);
	while(tempMove < 1 || tempMove > 7){
	        printf("Invalid move, try again: ");
        	scanf("%i", &tempMove);
	}
	//Place Move in Proper Array Index//
	*move = tempMove - 1;
}

//Update Move in 2D Array//
void updateMove(char board[BOARD_HEIGHT][BOARD_WIDTH], int move, char token, int turn){
	//Gravity Algorithm//
	int j = 0;
	while(board[move][j] == '.' && board[move][j+1] == '.'){
		j++;
	}
	board[move][j] = token;
}

//Win Conditions//
bool checkWin(char board[BOARD_HEIGHT][BOARD_WIDTH], char token){

	//Horizontal Win Condition//
	bool win = false;
   
	for(int j = 0; j < BOARD_WIDTH; j++){
        	for(int i = 0; i + 4 < BOARD_HEIGHT; i++){
        		if(board[i][j] == board [i+1][j] && board [i+1][j] == board[i+2][j] && board[i+2][j] == board[i+3][j] && board [i][j] == token){
                win = true;
			}
		}    
	}
    
	//Vertical Win Condition//
	for(int i = 0; i + 3 < BOARD_WIDTH; i++){
        	for(int j = 0; j + 4 < BOARD_WIDTH; j++){
          	  	if(board[i][j] == board [i][j+1] && board [i][j+1] == board[i][j+2] && board[i][j+2] == board[i][j+3] && board [i][j] == token){
             	   		win = true;
            		}
       		}
   	}
   	
 	//Diagonal Win Condition '/'//
	for (int i = 3; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j <= BOARD_WIDTH - 4; j++) {
			if (board[i][j] == token && board[i-1][j+1] == token && board[i-2][j+2] == token && board[i-3][j+3] == token) {
                win = true;
			}
		}
	}
	//Diagonal Win Condition '\'//
	for (int i = 3; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j <= BOARD_WIDTH - 4; j++) {
			if (board[i][j] == token && board[i-1][j+1] == token && board[i-2][j+2] == token && board[i-3][j+3] == token) {
		win = true;
			}
		}
	}
   	     return win;
}

//Player Token Per Turn//
void whichToken(int turn, bool player1Turn, char player1Token, char player2Token, char *token){
	*token = (turn % 2 != 0) ? player1Token : player2Token;
}

//Menu Display//
void displayMenu() {
	printf("Connect Four!\n");
	printf("1: Start a new game\n");
	printf("2: Load a saved game\n");
	printf("3: Exit\n");
	printf("Choose an option: ");
}

//Main Function
int main(){

	//Declarations//
	char board[BOARD_HEIGHT][BOARD_WIDTH];
	int turn = 1;
	int move;
	char player1Token, player2Token;
	char token;
	int choice;

	//Menu Operations//
	displayMenu();
	scanf("%d", &choice);
	switch (choice) {
        case 1:
        	loadGame(board, SAVE_GAME);
        	break;
        case 2:
        	loadGame(board, TEST);
        	break;
        case 3:
        	printf("Exiting game.\n");
        	return 0;
        default:
        	printf("Invalid choice, exiting.\n");
        	return 0;
	}

	//Player Token Prompt//
	printf("Player 1, enter your letter: ");
	scanf(" %c", &player1Token);
	printf("Player 2, enter your letter: ");
	scanf(" %c", &player2Token);
	
	//Board Initialization//
	displayBoard(board);

	//Gameplay Loop//
	do {
        	whichToken(turn, turn % 2 != 0, player1Token, player2Token, &token);
        	getMove(turn, &move);
        	updateMove(board, move, token, turn);
        	displayBoard(board);
        	turn++;
	} while (!checkWin(board, token));
		printf("Congratulations, you win!\n");

return 0;
}
