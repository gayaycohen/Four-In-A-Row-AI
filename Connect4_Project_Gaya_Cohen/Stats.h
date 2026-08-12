#ifndef STATS_H
#define STATS_H

typedef struct {
    int easyWins, easyLosses, easyDraws;
    int mediumWins, mediumLosses, mediumDraws;
    int smartWins, smartLosses, smartDraws;
    int pvpGames;
    int player1Wins, player2Wins, pvpDraws;
} GameStats;

void initStats(GameStats* stats);
void updateStats(GameStats* stats, int result, int mode, int difficulty);
void printStats(GameStats stats);
void saveStats(GameStats stats);
void loadStats(GameStats* stats);

#endif
