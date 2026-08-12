#ifndef BOARD_H
#define BOARD_H
#define ROWS 6 
#define COLS 7 
#define MARGIN_LEFT "                                     " 
#define MARGIN_TOP "\n"

int showmenu();                                          //הדפסת התפריט
void init_board(char board[ROWS][COLS]);                  //אתחול הלוח
void print_board(char board[ROWS][COLS]);                 //הדפסת הלוח
void refreshScreen();                                     //הדפסת הלוגו וניקוי המסך
void printLogo();                                         //הדפסת הלוגו
#endif

