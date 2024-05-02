//Authors: Chase Grundy and Duncan Brown
//Date: 5/2/2024
//Title: Connect 4

#include <stdio.h>
#include <stdbool.h>

#define BOARD_HEIGHT 7
#define BOARD_WIDTH 8

#define SAVE_GAME "saveGame.txt"


void loadGame(char board[BOARD_HEIGHT][BOARD_WIDTH]){
    FILE* saveGame;
    saveGame = fopen(SAVE_GAME, "r");

//File Validity Check
    if(saveGame == NULL){
        printf("Cannot open saved game\n");
    }

    for(int i = 0; i <= BOARD_HEIGHT; i++){
        for(int j = 0; j< BOARD_WIDTH; j++)
            fscanf(saveGame, " %c", &board[i][j]);
    }

}

void displayBoard(char board[BOARD_HEIGHT][BOARD_WIDTH]){
    for(int i = 0; i<=BOARD_HEIGHT; i++){
        for(int j = 0; j< BOARD_WIDTH; j++)
            printf("%1c", board[j][i]);
        printf("\n");
    }

}

void getMove(int turn, bool player1Turn, int move){
    turn = turn + 1; 
    if(turn%2 != 0){
        player1Turn = true;
    }
    
    printf("player 1 turn, enter column: ");
    scanf("%d",&move);
}

void updateMove(char board[BOARD_HEIGHT][BOARD_WIDTH], int move, char *token){
    for(int i = BOARD_HEIGHT; (i - 1) != '.'; i--){
        board[i][move] = *token;
    }

}



int main(){
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    char player1Token, player2Token, token;
    

    int turn = 0;
    bool player1Turn;
    int move = 1;




    loadGame(board);
    displayBoard(board);
    updateMove(board, move, &token);
    displayBoard(board);



    return 0;

}