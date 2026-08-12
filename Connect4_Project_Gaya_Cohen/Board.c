#include <stdio.h>
#include <stdlib.h>
#include "Board.h"
#include <string.h>
#define BG_CREAM "\033[107m"
#define BG_PINK "\033[48;2;245;222;179m"
#define BG_PER "\033[48;2;255;255;255m"
#define RESET "\033[0m"
void printLogo()
{

printf("                            ______ ____  _    _ _____    _____ _   _           _____    ______          __  \n");
printf("                           |  ____/ __ \\| |  | |  __ \\  |_   _| \\ | |    /\\    |  __ \\ / __ \\ \\        / / \n");
printf("                           | |__ | |  | | |  | | |__) |   | | |  \\| |   /  \\   | |__) | |  | \\ \\  /\\  / /  \n");
printf("                           |  __|| |  | | |  | |  _  /    | | | . ` |  / /\\ \\  |  _  /| |  | |\\ \\/  \\/ /   \n");
printf("                           | |   | |__| | |__| | | \\ \\   _| |_| |\\  | / ____ \\ | | \\ \\| |__| | \\  /\\  /    \n");
printf("                           |_|    \\____/ \\____/|_|  \\_\\ |_____|_| \\_|/_/    \\_\\|_|  \\_\\\\____/   \\/  \\/     \n");
printf("\n");
}
void refreshScreen() 
{
    system("cls"); 
    printLogo();   
}
int showmenu()
{
    int choice;
    printf("\n\n");
    printf("                         1 - Player vs Player   ");
    printf("2 - Player vs Computer   ");
    printf("3 - View Statistics   ");
    printf("4 - Exit Game   ");
    printf("\n\n\n                                                       Please enter your choice: ");
    scanf_s("%d", &choice);
    return choice;
}
//פונקציה שמאתחלת את המערך לתאים ריקים
void init_board(char board[ROWS][COLS]) 
{
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = ' ';
        }
    }
}

//פונקציה שמדפיסה את המערך
void print_board(char board[ROWS][COLS])
{
    printf(MARGIN_TOP);
    printf("\n");

    for (int i = 0; i < ROWS; i++) {
        for (int row_part = 0; row_part < 3; row_part++) {
            printf(MARGIN_LEFT "  |");

            for (int j = 0; j < COLS; j++) {
                if (board[i][j] == 'X') {
                    printf(BG_PINK "       " RESET "|");
                }
                else if (board[i][j] == 'O') {
                    printf(BG_PER "       " RESET "|");
                }
                else {
                    printf( "       " RESET "|");
                }
            }
            printf("\n");
        }

        printf(MARGIN_LEFT "  |-------|-------|-------|-------|-------|-------|-------|\n");
    }
    printf("\n");
    printf(MARGIN_LEFT "      1       2       3       4       5       6       7\n");
}

