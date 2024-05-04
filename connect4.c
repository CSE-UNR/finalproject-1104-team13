//Authors: Chase Grundy and Duncan Brown
//Date: 5/2/2024
//Title: Connect 4

#include <stdio.h>
#include <stdbool.h>

#define BOARD_HEIGHT 7
#define BOARD_WIDTH 7

#define SAVE_GAME "saveGame.txt"
#define TEST "test.txt"

void loadGame(char board[BOARD_HEIGHT][BOARD_WIDTH]){
    FILE* saveGame;
    saveGame = fopen(SAVE_GAME, "r");

//File Validity Check
    if(saveGame == NULL){
        printf("Cannot open saved game\n");
    }

    for(int i = 0; i <BOARD_WIDTH; i++)
        for(int j = 0; j < BOARD_HEIGHT; j++)
            fscanf(saveGame, " %c", &board[i][j]);
//Close the File
    fclose(saveGame);
}

void displayBoard(char board[BOARD_HEIGHT][BOARD_WIDTH]){
    for(int i = 0; i < BOARD_HEIGHT; i++){
        for(int j = 0; j < BOARD_WIDTH; j++)
            printf("%c", board[j][i]);
        printf("\n");
    }

}

void getMove(int turn, int *move){
    int tempMove = 0;
    bool player1Turn; 
    if(turn%2 != 0){
        player1Turn = true;
    }
    if(player1Turn == true){printf("player 1 turn, enter column: ");
    }
    else{printf("Player 2 Turn. Enter Column:");
    }
    
    //Actually get the move
    scanf("%i",&tempMove);
    if(tempMove > 7){
        printf("Invalid Move, Try Again: ");
        scanf("%i", move);
    }
    *move = tempMove - 1;
}

void updateMove(char board[BOARD_HEIGHT][BOARD_WIDTH], int move, char token, int turn){
    //gravity
    int i = 0;
    while(board[move][i] == '.' && board[move][i+1]=='.'){
        i++;
    }
    board[move][i] = token;
}
    

bool checkWin(char board[BOARD_HEIGHT][BOARD_WIDTH], char token){
//horizontal win
   bool win = false;
   
    for(int j = 0; j < BOARD_WIDTH; j++){
        for(int i = 0; i + 4 < BOARD_HEIGHT; i++){
            if(board[i][j] == board [i+1][j] && board [i+1][j] == board[i+2][j] && board[i+2][j] == board[i+3][j] && board [i][j] == token){
                win = true;
             }
        }    
    }
	for(int j = 0; j < BOARD_WIDTH; j++){
        	for(int i = 0; i + 4 < BOARD_HEIGHT; i++){
          	  	if(board[i][j] == board [i+1][j] && board [i+1][j] == board[i+2][j] && board[i+2][j] == board[i+3][j] && board [i][j] == token){
            	   		 win = true;
             		}
       		}    
    }    
	return win;
}

int main(){

    char board[BOARD_HEIGHT][BOARD_WIDTH];
    int turn = 1;
    bool player1Turn;
    int move;
    char token = 'd';

    loadGame(board);
    displayBoard(board);
    
    //Gameplay Loop
    do{
    getMove(turn, &move);
    updateMove(board, move, token, turn); 
    displayBoard(board);
    turn = turn + 1;
    }while(checkWin(board, token)!= true);
   printf("congrats, you win!");
   
   
    return 0;
}
