#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"
#include "Game.h"
#include <stdio.h>
#include <stdlib.h> 
#include "Stats.h"

int main()
{
	GameStats myStats;
	loadStats(&myStats);
	char board[ROWS][COLS];
	system("chcp 65001 > nul");
	refreshScreen();
	int choice;
	int winner;
	int difficulty = 0;
	do {
		choice = showmenu();
		if (choice>4||choice<1)
		{ 
			
			printf("Invalid input! Please press enter and try again\n");
			while (getchar() != '\n'); 
			getchar();
			choice = 0; 
			refreshScreen();
			continue;
		}
		switch (choice)
		{
		case 1:
			refreshScreen();
			winner = playgame_humen_vs_humen();
			updateStats(&myStats, winner, 1, 0);
			saveStats(myStats); 
			break;
		case 2:
			refreshScreen();
			printf("\n                                                      --- Select Difficulty ---\n\n\n");
			printf("                               1. Easy (Random moves)");
			printf("   2. Medium (Strategic moves)");
			printf("   3. Hard (Future sight)\n\n\n");
			printf("                                                            Choose level: ");
			difficulty = 0;
			scanf_s("%d", &difficulty);
			winner = playgame_humen_Vs_Computer(difficulty);
			updateStats(&myStats, winner, 2, difficulty); 
			saveStats(myStats); 
			break;
		case 3:
			refreshScreen();
			printStats(myStats);
			break;
		case 4:
			printf("good bye...\n");
			break;
		default: 
			printf("try again\n");
			break;
		}

	} while (choice != 4);
	return 0;
}
