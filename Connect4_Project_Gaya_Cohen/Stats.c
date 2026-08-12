#define _CRT_SECURE_NO_WARNINGS
#include "Stats.h"
#include "Board.h" 
#include <stdio.h>
// אתחול כל הנתונים לאפס
void initStats(GameStats* stats) {
    (*stats).easyWins = 0;    (*stats).easyLosses = 0; (*stats).easyDraws = 0;
    (*stats).mediumWins = 0;  (*stats).mediumLosses = 0; (*stats).mediumDraws = 0;
    (*stats).smartWins = 0;   (*stats).smartLosses = 0; (*stats).smartDraws = 0;
    (*stats).pvpGames = 0;
    (*stats).player1Wins= 0;   (*stats).player2Wins = 0; (*stats).pvpDraws = 0;
    
}

// עדכון הסטטיסטיקה בסיום משחק
void updateStats(GameStats* stats, int result, int mode, int difficulty) {
    if (mode == 2) { // מצב נגד מחשב
        if (difficulty == 1) { 
            if (result == 1) (*stats).easyWins++;
            else if (result == 2) (*stats).easyLosses++;
            else (*stats).easyDraws++; 
        }
        else if (difficulty == 2) {
            if (result == 1) (*stats).mediumWins++;
            else if (result == 2) (*stats).mediumLosses++;
            else (*stats).mediumDraws++; 
        }
        else if (difficulty == 3) { 
            if (result == 1) (*stats).smartWins++;
            else if (result == 2) (*stats).smartLosses++;
            else (*stats).smartDraws++; 
        }
    }
    else {
        (*stats).pvpGames++;
        if (result == 1) (*stats).player1Wins++;
        else if (result == 2) (*stats).player2Wins++;
        else (*stats).pvpDraws++; 
    }
}

void saveStats(GameStats stats) {
    FILE* f = fopen("stats.txt", "w");
    if (f == NULL) return;
    fprintf(f, "%d %d %d\n", stats.easyWins, stats.easyLosses, stats.easyDraws);
    fprintf(f, "%d %d %d\n", stats.mediumWins, stats.mediumLosses, stats.mediumDraws);
    fprintf(f, "%d %d %d\n", stats.smartWins, stats.smartLosses, stats.smartDraws);
    fprintf(f, "%d %d %d %d\n", stats.player1Wins, stats.player2Wins, stats.pvpDraws, stats.pvpGames);
    fclose(f);
}


void loadStats(GameStats* stats) {
    FILE* f = fopen("stats.txt", "r");

    if (f == NULL) { 
        initStats(stats); 
        return;
    }
    fscanf(f, "%d %d %d", &(*stats).easyWins, &(*stats).easyLosses, &(*stats).easyDraws);
    fscanf(f, "%d %d %d", &(*stats).mediumWins, &(*stats).mediumLosses, &(*stats).mediumDraws);
    fscanf(f, "%d %d %d", &(*stats).smartWins, &(*stats).smartLosses, &(*stats).smartDraws);
    fscanf(f, "%d %d %d %d", &(*stats).player1Wins, &(*stats).player2Wins, &(*stats).pvpDraws, &(*stats).pvpGames);

    fclose(f); 
}
void printStats(GameStats stats) {
    printf("\n\n\n\n\n                                               =================================================\n");
    printf("                                                               GAME STATISTICS         \n");
    printf("                                               =================================================\n");
    printf("                                               EASY:   CompLosses: %d |CompWins:  %d | Draws: %d\n", stats.easyWins, stats.easyLosses, stats.easyDraws);
    printf("                                               MEDIUM: CompLosses: %d |CompWins:  %d | Draws: %d\n", stats.mediumWins, stats.mediumLosses, stats.mediumDraws);
    printf("                                               HARD:   CompLosses: %d |CompWins:  %d | Draws: %d\n", stats.smartWins, stats.smartLosses, stats.smartDraws);
    printf("                                               -------------------------------------------------\n");
    printf("                                               PLAYER VS PLAYER:\n");
    printf("                                               Games: %d | P1 Wins: %d | P2 Wins: %d | Draws: %d\n",stats.pvpGames, stats.player1Wins, stats.player2Wins, stats.pvpDraws);
    printf("                                               =================================================\n");
    printf("\n                                                         Press Enter to return...");
    while (getchar() != '\n'); getchar();
}