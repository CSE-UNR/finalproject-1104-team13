//Authors: Chase Grundy and Duncan Brown
//Date: 5/2/2024
//Title: Connect 4

#include <stdio.h>
#include <stdbool.h>

#define BOARD_HEIGHT 7
#define BOARD_WIDTH 8

#define SAVE_GAME "saveGame.txt"


void loadGame(char **board[BOARD_HEIGHT][BOARD_WIDTH]){
    FILE* saveGame;
    saveGame = fopen(SAVE_GAME, "r");

//File Validity Check
    if(saveGame == NULL){
        printf("Cannot open saved game\n");
    }

    for(int i = 0; i <= BOARD_HEIGHT; i++){
        for(int j = 0; j<= BOARD_WIDTH; j++)
            fscanf(saveGame, " %c", &board[i][j]);
    }

}

void displayBoard(char **board[BOARD_HEIGHT][BOARD_WIDTH]){
    for(int i = 0; i<=BOARD_HEIGHT; i++){
        for(int j = 0; j<= BOARD_WIDTH; j++)
            printf("%1c", board[i][j]);

    }

}

int main(){
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    char player1, player2;

    loadGame(&board[BOARD_HEIGHT][BOARD_WIDTH]);
    displayBoard(&board[BOARD_HEIGHT][BOARD_WIDTH]);



    return 0;

}