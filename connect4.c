//Authors: Chase Grundy and Duncan Brown
//Date: 5/2/2024
//Title: Connect 4

#include <stdio.h>
#include <stdbool.h>

#define BOARD_HEIGHT 7
#define BOARD_WIDTH 7

#define SAVE_GAME "saveGame.txt"
#define TEST "test.txt"

//Load Game From File Pointer//
void loadGame(char board[BOARD_HEIGHT][BOARD_WIDTH]){
	FILE* saveGame;
	saveGame = fopen(SAVE_GAME, "r");

//File Validity Check//
	if(saveGame == NULL){
        	printf("Cannot open saved game.\n");
	}

	for(int i = 0; i <BOARD_WIDTH; i++)
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
	if(turn%2 != 0){
        	player1Turn = true;
	}
	if(player1Turn == true){
	printf("Player 1's Turn! Enter Column: ");
	}
	else{
	printf("Player 2's Turn! Enter Column: ");
	}
    
	//Enact Movement Input//
	scanf("%i",&tempMove);
	if(1 <= tempMove && tempMove <=7){
	}
	else{
    	printf("Invalid move, try again.");
    	scanf(" %i", &tempMove);
	}

//Place Move In Proper Array Index//
	*move = tempMove - 1;
	}

//Update Move in 2D Array//
void updateMove(char board[BOARD_HEIGHT][BOARD_WIDTH], int move, char token, int turn){
	//Gravity Algorithm//
	int j = 0;
	while(board[move][j] == '.' && board[move][j+1]=='.'){
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
	if(turn%2 != 0){
        player1Turn = true;
    	}
	if(player1Turn == true){
		*token = player1Token;
	}
	else{
		*token =  player2Token;
	}
	
}

//Main Function//
int main(){

	//Declarations//
	char board[BOARD_HEIGHT][BOARD_WIDTH];
	int turn = 1;
	bool player1Turn;
	int move;
	char player1Token, player2Token;
	char token;

	//Player Token Prompt//
	printf("Enter a letter for Player One: ");
	scanf(" %c", &player1Token);
	printf("Enter a letter for Player Two: ");
	scanf(" %c", &player2Token);

//Board Initialization//	
loadGame(board);
displayBoard(board);
    
    //Gameplay Loop//
    do{
    whichToken(turn, player1Turn, player1Token, player2Token, &token);
    getMove(turn, &move);
    updateMove(board, move, token, turn); 
    displayBoard(board);
    turn = turn + 1;
    }while(checkWin(board, token)!= true);
	printf("Congratulations, you win!\n"); 
      
    return 0;
}
