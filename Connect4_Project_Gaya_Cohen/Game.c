#include "Board.h"
#include "Game.h"
#include <stdio.h>
#include <stdlib.h> 
#include <windows.h>
int getPlayerMove(char board[ROWS][COLS])
{
	int num_of_cols;
	scanf_s("%d", &num_of_cols);
	return num_of_cols;
}

int isvalidMove(char board[ROWS][COLS], int num_of_cols)
{
	if (num_of_cols < 1 || num_of_cols>7)
	{
		printf("Error: Input out of range (1-7 only)!\nPlease press ENTER to confirm and try again\n");

		return 0;
	}
	if (board[0][num_of_cols-1] !=' ')
	{
		printf("Error: Column is full!\nPlease press ENTER to confirm and try again");

		return 0;
	}
	return 1;
}

int dropDisc(char board[ROWS][COLS], int col, int player)
{
    int realcol = col - 1;
    char piece;
    if (player == 1)piece = 'X';
    else piece = 'O';
	for (int i = ROWS - 1; i >= 0; i--)
	{
		if (board[i][realcol] == ' ')
		{
				board[i][realcol] = piece;
            return i;
		}
	}
    return -1;
}
int chekwin(char board[ROWS][COLS], int col, int row, int player)
{
    char piece; 
    int count = 1;//הדיסקית שהופלה אחרונה והתחלת הספירה ממנה 
    int currentRow, currentCol;
    if (player == 1)
        piece = 'X';
    else piece = 'O';
    //בדיקת ניצחון בשורה - מימין לדיסקית ומשמאלה
    for (int i = col - 1; i >= 0; i--)
    {
        if (board[row][i] == piece)
            count++;
        else break;
    }
    for (int i = col + 1; i < COLS; i++)
    {
        if (board[row][i] == piece)
            count++;
        else break;
    }
    if (count >= 4) 
        return player;
    //בדיקת עמודה מתחת לדיסקית שהונחה
    count = 1;
    for (int j = row + 1; j < ROWS; j++)
    {
        if (board[j][col] == piece)
            count++;
        else break;
    }
    if (count >= 4)
        return player;
    //בדיקת אלכסון ראשי - באיזור הדיסקית
    //למעלה ושמאלה
    count = 1;
     currentRow = row - 1;
     currentCol = col - 1;
    while (currentRow >= 0 && currentCol >= 0) 
    {
        if (board[currentRow][currentCol] == piece)
        {
            count++;
            currentRow = currentRow - 1; 
            currentCol = currentCol - 1; 
        }
        else
        {
            break; 
        }
    }
    //למטה וימינה
     currentRow = row + 1;
     currentCol = col + 1;
    while (currentRow < ROWS && currentCol < COLS)
    {
        if (board[currentRow][currentCol] == piece)
        {
            count++;
            currentRow = currentRow + 1;
            currentCol = currentCol + 1;
        }
        else
        {
            break;
        }
    }
    if (count >= 4)
        return player;

    //בדיקת אלכסון משני - באיזור הדסקית
    //למעלה וימינה
    count = 1;
     currentRow = row - 1;
     currentCol = col + 1;
    while (currentRow >= 0 && currentCol < COLS)
    {
        if (board[currentRow][currentCol] == piece)
        {
            count++;
            currentRow = currentRow - 1;
            currentCol = currentCol + 1;
        }
        else
        {
            break;
        }
    }
    //למטה ושמאלה
     currentRow = row + 1;
     currentCol = col - 1;
    while (currentRow < ROWS && currentCol >=0)
    {
        if (board[currentRow][currentCol] == piece)
        {
            count++;
            currentRow = currentRow + 1;
            currentCol = currentCol - 1;
        }
        else
        {
            break;
        }
    }
    if (count >= 4)
        return player;

    return 0;
}

int isboardfull(char board[ROWS][COLS])
{
        for (int j = 0; j < COLS; j++)
        {
            if (board[0][j] == ' ')
                return 0;
        }
    
    return 1;
}
int switchplayer(int currentplayer)
{
    if (currentplayer == 1)
        return 2;
    else return 1;
}
int easyStrategy(char board[ROWS][COLS])
{
    int col;
    do {
        col = (rand() % COLS) + 1;
    } while (board[0][col - 1] != ' '); 
    return col;
}

int getRowForDisc(char board[ROWS][COLS], int col) 
{
    for (int r = ROWS - 1; r >= 0; r--)
    {
        if (board[r][col-1] == ' ') {
            return r;
        }
    }
    return -1; // עמודה מלאה
}

int mediumStrategy(char board[ROWS][COLS], int currentPlayer)
{
    int col, row;
    char computer = 'O', human='X';

    // בודק אם המחשב ינצח בתור הבא 
    for (col = 0; col < COLS; col++) {
        
        row = getRowForDisc(board, col + 1);

        if (row != -1) 
        { 
            board[row][col] = computer; // סימולציה
            if (chekwin(board, col, row, 2) != 0)
            {
                board[row][col] = ' '; 
                return col + 1;
            }
            board[row][col] = ' '; 
        }
    }

    //בודק אם השחקן האנושי יכול לנצח בתור הבא , אם כן חוסם
    for (col = 0; col < COLS; col++) {
        row = getRowForDisc(board, col + 1);

        if (row != -1) 
        {
            board[row][col] = human; // סימולציה של היריב
            if (chekwin(board, col, row, 1) != 0)
            {
                board[row][col] = ' '; 
                return col + 1; 
            }
            board[row][col] = ' '; 
        }
    }
    if (isvalidMove(board, 4)) return 4;//עדיפות לעמודה האמצעית 
    return easyStrategy(board);
}

void undoMove(char board[ROWS][COLS], int col) {
    int realCol = col - 1;
    for (int i = 0; i < ROWS; i++) {
        if (board[i][realCol] != ' ') {
            board[i][realCol] = ' ';
            break;
        }
    }
}
int scoreWindow(char c1, char c2, char c3, char c4) {
    int score = 0;
    int compCount = 0;    // סופר כמה 'O' - מחשב
    int playerCount = 0; // סופר כמה 'X' - שחקן
    int emptyCount = 0;   // סופר כמה רווחים ' '
    char window[4] = { c1, c2, c3, c4 };

    //בדיקה מי נמצא בתאים האלו
    for (int i = 0; i < 4; i++) {
        if (window[i] == 'O') compCount++;
        else if (window[i] == 'X') playerCount++;
        else emptyCount++;
    }

//ניקוד בהתאם לקאונטים
    if (compCount == 4)
    {
        score = score + 10000; // ניצחון 
    }
    else if (compCount == 3 && emptyCount == 1)
    {
        score = score + 100;   // שלוש מחשב , אחד ריק
    }
    else if (compCount == 2 && emptyCount == 2)
    {
        score = score + 10;    //שתיים מחשב , אחד ריק
    }
    if (playerCount == 3 && emptyCount == 1) 
    {
        score = score- 800;   // שלוש שחקן , אחד ריק , דחוף לחסום
    }

    return score;
}

int evaluateBoard(char board[ROWS][COLS]) {
    int score = 0;

    //עמודה האמצעית אסטרטגית , המחשב מקבל בונוס על כל הנחה של דיסקית שם
    for (int r = 0; r < ROWS; r++) 
    {
        if (board[r][3] == 'O')
            score = score + 3;
        else if (board[r][3] == 'X')
            score = score - 3;
    }

    //בכל שורה המחשב בודק 4 תאים צמודים ושולח אותם לפונקציית הניקוד
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c <= COLS - 4; c++)//לא לחרוג מגבולות המערך
        {
            score = score + scoreWindow(board[r][c], board[r][c + 1], board[r][c + 2], board[r][c + 3]);
        }
    }

    //בכל עמודה המחשב בודק 4 תאים צמודים ושולח אותם לפונקציית הניקוד
    for (int c = 0; c < COLS; c++) {
        for (int r = 0; r <= ROWS - 4; r++)
        {
            score = score+ scoreWindow(board[r][c], board[r + 1][c], board[r + 2][c], board[r + 3][c]);
        }
    }

    // בדיקת אלכסון ראשי , יורדים כל פעם אחד ימינה וזזים אחד ימינה , ושולחים לפונקציית ניקוד
    for (int r = 0; r <= ROWS - 4; r++) {
        for (int c = 0; c <= COLS - 4; c++) {
            score = score+ scoreWindow(board[r][c], board[r + 1][c + 1], board[r + 2][c + 2], board[r + 3][c + 3]);
        }
    }

    // // בדיקת אלכסון משני , יורדים כל פעם אחד שמאלה וזזים אחד שמאלה , ושולחים לפונקציית ניקוד
    for (int r = 3; r < ROWS; r++) {
        for (int c = 0; c <= COLS - 4; c++) {
            score = score + scoreWindow(board[r][c], board[r - 1][c + 1], board[r - 2][c + 2], board[r - 3][c + 3]);
        }
    }

    return score;
}

int minimax(char board[ROWS][COLS], int depth, int isMaximizing) 
{
    // אם סיימנו את הבדיקה של השלוש מהלכים או שהלוח מלא - תחזיר את הציון הנוכחי
    if (depth == 0 || isboardfull(board)) 
    {
        return evaluateBoard(board); 
    }
    // סימולציה של תור המחשב
    if (isMaximizing) 
    { 
        int maxEval = -1000000;
        for (int c = 1; c <= COLS; c++) 
        {
            int r = getRowForDisc(board, c);
            if (r != -1) {
                board[r][c - 1] = 'O';

                int eval;

                if (chekwin(board, c - 1, r, 2) != 0)
                {
                    eval = 1000000;
                }
                else
                {
                    eval = minimax(board, depth - 1, 0);
                }

                board[r][c - 1] = ' ';
                if (eval > maxEval)
                    maxEval = eval; // המחשב רוצה להגדיל את הציון
            }
        }
        return maxEval;
    }
    else { // סימולציה של תור השחקן 
        int minEval = 1000000;
        for (int c = 1; c <= COLS; c++) 
        {
            int r = getRowForDisc(board, c);
            if (r != -1) {
                board[r][c - 1] = 'X';

                int eval;

                if (chekwin(board, c - 1, r, 1) != 0)
                {
                    eval = -1000000;
                }
                else
                {
                    eval = minimax(board, depth - 1, 1);
                }

                board[r][c - 1] = ' ';
                if (eval < minEval)
                    minEval = eval; // המחשב מניח שהשחקן ינסה להוריד לו את הציון
            }
        }
        return minEval;
    }
}

int hardStrategy(char board[ROWS][COLS]) {
    int bestScore = -1000000;
    int bestCol = 4; // ברירת מחדל למרכז
    int row;
    //מתחילים לעבוד על העמודות
    for (int col = 1; col <= COLS; col++) 
    {
        row = getRowForDisc(board, col);
        if (row != -1)//אם העמודה לא מלאה
        {
            board[row][col - 1] = 'O';

            if (chekwin(board, col - 1, row, 2) != 0)
            {
                board[row][col - 1] = ' ';
                return col;
            }

            int score = minimax(board, 3, 0);
            board[row][col - 1] = ' ';
            if (score > bestScore) //עדכון העמודה הכי משתלמת
            {
                bestScore = score;
                bestCol = col;
            }
        }
    }
    return bestCol;
}
//פונקציה שמסכמת את כל הסבב בין שחקן לשחקן  
int playgame_humen_vs_humen()
{
    char board[ROWS][COLS];
    int currentPlayer = 1;
    int colChoice, rowFound;
    int isGameOver = 0;
    //הדפסה ואתחול של הלוח
    init_board(board);
    print_board(board);
    //כל עוד אין מנצח או תיקו שהלולאה תרוץ
    while (isGameOver == 0) 
    {
        refreshScreen();
        int valid = 0;
        //בדיקה אם הקלט תקין
        while (!valid)
        {
            print_board(board); 
            printf("\nPlayer %d's Turn , please choose a column (1-7): ", currentPlayer);

            colChoice = getPlayerMove(board);

            if (isvalidMove(board, colChoice)) 
            {
                valid = 1; 
            }
            else {
                
                while (getchar() != '\n'); 
                getchar();    // מחכה ללחיצה
                refreshScreen();
            }
        }

        
        rowFound = dropDisc(board, colChoice, currentPlayer);//הפלת הדסקית
        print_board(board);
        //בדיקה אם יש מנצח או תיקו
        //אם אין עוברים לשחקן הבא
        if (chekwin(board, colChoice - 1, rowFound, currentPlayer) != 0) 
        {
            refreshScreen();
            print_board(board);
            printf("\nPlayer %d Wins!\n", currentPlayer);
            Sleep(2000);
            isGameOver = 1;
            return currentPlayer;
        }
        else if (isboardfull(board) == 1)
        {
            refreshScreen();
            print_board(board);
            printf("\nGame Over: It's a Tie!\n");
            return 0;
            isGameOver = 1;
        }
        else {
            currentPlayer = switchplayer(currentPlayer);
        }
    }

    printf(" Returning to main menu....\n");
    Sleep(2000);
} 



//ניהול המשחק - שחקן מול מחשב 
int playgame_humen_Vs_Computer(int difficulty)
{
        char board[ROWS][COLS];
        int col, row, win = 0 ;
        int currentPlayer = 1; 
        refreshScreen();
        /*בדיקה שהקלט תקין*/
        while ( (difficulty < 1 || difficulty > 3)) {
            printf("Invalid input! Please press enter and try again ");
            while (getchar() != '\n');
            getchar();
            refreshScreen();
            printf("\n                                                      --- Select Difficulty ---\n\n\n");
            printf("                               1. Easy ");
            printf("   2. Medium ");
            printf("   3. Hard \n\n\n");
            printf("                                                            Choose level: ");
            scanf_s("%d", &difficulty);
        }

        init_board(board);
        print_board(board);
        //כל עוד אין מנצח ותיקו
        while (win == 0 && !isboardfull(board))
        {
            refreshScreen();
            if (currentPlayer == 1) 
            {
                int valid = 0;
                //בדיקת קלט
                
                while (!valid) {
                    refreshScreen();
                    print_board(board);
                    printf("\nYour turn . Choose column (1-7): ");

                    if (scanf_s("%d", &col) != 1) {
                        printf("Error: Please enter a NUMBER.\n");
                        while (getchar() != '\n');
                        getchar();
                        refreshScreen(); 
                        print_board(board);
                        continue;
                    }
                    if (isvalidMove(board, col)) 
                    {
                        valid = 1;
                    }
                    else {

                        while (getchar() != '\n');
                        getchar();    // מחכה ללחיצה
                        refreshScreen();
                    }
                }
            }
            else {
                refreshScreen();
                print_board(board);
                printf("\nComputer is thinking");
                for (int i = 0; i < 3; i++)
                { 
                   printf("."); 
                   Sleep(500);
                }
                printf("\n");
                //כניסה לרמה
                switch (difficulty) {
                case 1:
                    col = easyStrategy(board);
                    break;
                case 2:
                    col = mediumStrategy(board, 2);
                    break;
                case 3:
                    col = hardStrategy(board);
                }
                printf("Computer chose column: %d\n", col);
            }

            row = dropDisc(board, col, currentPlayer);

            if (row != -1) {
                win = chekwin(board, col - 1, row, currentPlayer);

                if (win != 0)
                {
                    refreshScreen();
                    print_board(board);
                    if (currentPlayer == 1) {
                        printf("\n*** CONGRATULATIONS! YOU BEAT THE COMPUTER! ***\n");
                        return 1;
                    }
                    else {
                        printf("\n--- THE COMPUTER WON. TRY AGAIN! ---\n");
                        return 2;
                    }
                    break; 
                }
                currentPlayer = switchplayer(currentPlayer);
                
            }
        }
        if (win == 0 && isboardfull(board)) 
        {
            refreshScreen();
            print_board(board);
            printf("\nIt's a tie! The board is full.\n");
            return 0;
        }

        printf("\nReturning to main menu...\n");
        Sleep(2000);
    }