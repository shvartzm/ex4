#include <stdio.h>
#include <string.h>


/***************************
******** Menu Items ********
****************************/

#define REVERSE 1
#define PALINDROME 2
#define SENTENCES 3
#define ZIP 4
#define SUDOKU 5
#define EXIT 6


/***************************
*** DIMENSION PARAMETERS ***
****************************/

#define LONGEST_TERM 20
#define LONGEST_SENTENCE 62
#define MAX_NUMBER_OF_TERMS 10

#define ZIP_MAX_GRID_SIZE 20

#define SUDOKU_GRID_SIZE 9
#define SUDOKU_SUBGRID_SIZE 3


/***************************
* USER INTEFACE PROTOTYPES *
****************************/

void task1ReversePhrase();
void task2CheckPalindrome();
void task3GenerateSentences();
void task4SolveZipBoard();
void task5SolveSudoku();


/****************************
* IMPLEMENTATION PROTOTYPES *
*****************************/

void task1ReversePhraseImplementation();
int task2CheckPalindromeImplementation(int);
void task3GenerateSentencesImplementation(char[][LONGEST_TERM+1], int, char[][LONGEST_TERM+1], int, char[][LONGEST_TERM+1], int);
int task4SolveZipBoardImplementation(int[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], char[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], int, int, int, int);
int task5SolveSudokuImplementation(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]);


/******************************
* HELPER FUNCTIONS PROTOTYPES *
*******************************/

int readTerms(char[][LONGEST_TERM+1], int, char[]);
void printSudoku(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]);
void printObjects(char[],char[],char[][LONGEST_TERM+1],int,int,int);
void printVerbs(char[],char[][LONGEST_TERM+1],int,char[][LONGEST_TERM+1],int,int,int);
int isInBounds(int,int,int,int);
int task4SolveZipBoardRec(int[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],char[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],int,int,int,int,int,int);
int solveSudokuRec(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int,int);
int numberAttempt(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int,int,int);
int isBoxPerfectRec(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int,int,int,int);
int checkBoxLoopRec(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int,int,int,int,int);
int checkBottomRightBox(int,int,int);
int checkCollumn(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int,int,int,int);
int checkRow(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int,int,int,int);










/******************************
********** MAIN MENU **********
*******************************/

int main()
{
    int task;
    do
    {
        printf("Please choose a task (1-5) or 6 to exit:\n");
        printf("%d. Reverse a phrase\n", REVERSE);
        printf("%d. Check Palindrome\n", PALINDROME);
        printf("%d. Generate sentences\n", SENTENCES);
        printf("%d. Solve Zip Board\n", ZIP);
        printf("%d. Solve Sudoku\n", SUDOKU);
        printf("%d. Exit\n", EXIT);

        scanf(" %d", &task);
        scanf("%*c");
        switch (task)
        {
        case REVERSE:
            task1ReversePhrase();
            break;
        case PALINDROME:
            task2CheckPalindrome();
            break;
        case SENTENCES:
            task3GenerateSentences();
            break;
        case ZIP:
            task4SolveZipBoard();
            break;
        case SUDOKU:
            task5SolveSudoku();
            break;
        case EXIT:
            printf("Goodbye!\n");
            break;
        default:
            printf("Please choose a task number from the list.\n");
            break;
        }
        printf("\n=============================\n\n");
    } while (task != EXIT);

    return 0;
}


/***************************
****** USER INTERFACE ******
****************************/


void task1ReversePhrase()
{
    printf("Please insert the phrase to reverse:\n");
    task1ReversePhraseImplementation();
    printf("\n");
}


void task2CheckPalindrome()
{
    printf("Please insert the phrase length:\n");
    int n;
    scanf("%d", &n);
    printf("Please insert the phrase to check:\n");
    scanf(" ");
    if (task2CheckPalindromeImplementation(n))
        printf("The phrase is a palindrome.\n");
    else
        printf("The phrase is not a palindrome.\n");
}


void task3GenerateSentences()
{
    char subjects[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    char verbs[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    char objects[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    int subjectsCount, verbsCount, objectsCount;

    subjectsCount=readTerms(subjects, MAX_NUMBER_OF_TERMS, "subjects");
    verbsCount=readTerms(verbs, MAX_NUMBER_OF_TERMS, "verbs");
    objectsCount=readTerms(objects, MAX_NUMBER_OF_TERMS, "objects");
    printf("List of Sentences:\n");
    task3GenerateSentencesImplementation(subjects, subjectsCount, verbs, verbsCount, objects, objectsCount);
}


void task4SolveZipBoard()
{
    int size;
    int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
    char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
    int row, col;
    int highest=0;
    printf("Please enter the board size:\n");
    scanf("%d", &size);
    if (size < 1 || size > ZIP_MAX_GRID_SIZE)
    {
        printf("Invalid board size.\n");
        return;
    }

    printf("Please enter the grid:\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 1)
            {
                row = i;
                col = j;
            }
            if(board[i][j]>highest){
                highest=board[i][j];
            }
        }
    }
    if (task4SolveZipBoardImplementation(board, solution, size, row, col, highest))
    {
        printf("Solution:\n");
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%c ", solution[i][j] ? solution[i][j] : 'X');
            }
            printf("\n");
        }
    }
    else
    {
        printf("No solution exists.\n");
    }
}


void task5SolveSudoku()
{
    printf("Please enter the sudoku board:\n");
    int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE] = {0};
    for (int i = 0; i < SUDOKU_GRID_SIZE; i++)
    {
        for (int j = 0; j < SUDOKU_GRID_SIZE; j++)
        {
            scanf("%d", &board[i][j]);
        }
    }
    if (task5SolveSudokuImplementation(board))
    {
        printf("Solution found:\n");
        printSudoku(board);
    }
    else
    {
        printf("No solution exists.\n");
    }
}


/***************************
********* HELPERS **********
****************************/


int readTerms(char terms[][LONGEST_TERM+1], int maxNumOfTerms, char type[]){
    int termsCount;
    printf("Please insert number of %s:\n", type);
    scanf("%d", &termsCount);
    if(termsCount < 1 || termsCount > maxNumOfTerms){
        termsCount = maxNumOfTerms;
    }
    printf("Please insert the list of %s:\n", type);
    for(int i=0;i<termsCount;i++){
        printf("%d. ",i+1);
        scanf(" %[^\n]",terms[i]);
    }
    return termsCount;
}

void printObjects(char subject[], char verb[], char objects[][LONGEST_TERM+1], int objectsCount, int pos, int objectNum){
    if (pos > 0){
        printObjects(subject,verb,objects,objectsCount, pos - 1, objectNum - 1);
    }
    char sentence[LONGEST_SENTENCE];
    strcpy(sentence, subject);
    strcat(sentence," ");
    strcat(sentence,verb);
    strcat(sentence," ");
    strcat(sentence,objects[pos]);
    printf("%d. %s\n",objectNum,sentence);

}

void printVerbs(char subject[], char verbs[][LONGEST_TERM+1], int verbsCount, char objects[][LONGEST_TERM+1], int objectsCount, int pos,int verbNum){
    if (pos >0){
        printVerbs(subject,verbs,verbsCount,objects,objectsCount,pos - 1,verbNum);
    }
    int startNum = verbNum + (pos * objectsCount);
    printObjects(subject,verbs[pos],objects,objectsCount,objectsCount - 1,startNum);
}

int isInBounds(int rows, int cols, int row, int col){
    return (row >= 0 && row < rows) && (col >= 0 && col < cols);
}

int task4SolveZipBoardRec(int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], int size, int currR, int currC, int highest,int currHighest, int counter){
    int temp;
    if(board[currR][currC] == highest && counter == size*size){
        solution[currR][currC] = 'X';
        return 1;
    }
    if (board[currR][currC] == currHighest + 1 || board[currR][currC] == 0){
        if (board[currR][currC] == currHighest + 1) currHighest = board[currR][currC];
        temp = board[currR][currC];
        board[currR][currC] = -1;
        if (isInBounds(size,size,currR - 1, currC)){
            if (task4SolveZipBoardRec(board,solution,size,currR -1, currC,highest,currHighest,counter + 1)){
               solution[currR][currC] = 'U';
               return 1;
            }
        }
        if (isInBounds(size,size,currR + 1, currC)){
            if (task4SolveZipBoardRec(board,solution,size,currR +1, currC,highest,currHighest,counter + 1)){
               solution[currR][currC] = 'D';
               return 1;
            }
        }
        if (isInBounds(size,size,currR, currC - 1)){
            if (task4SolveZipBoardRec(board,solution,size,currR, currC -1,highest,currHighest,counter + 1)){
               solution[currR][currC] = 'L';
               return 1;
            }
        }
        if (isInBounds(size,size,currR, currC + 1)){
            if (task4SolveZipBoardRec(board,solution,size,currR, currC +1,highest,currHighest,counter + 1)){
               solution[currR][currC] = 'R';
               return 1;
            }
        }
        board[currR][currC] = temp;
        return 0;
    }
    return 0;
    
}
// function check duplicates in cube starting from bottom left

int solveSudokuRec(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int row, int col){
    if (row == 9){ // win
        return 1;
    }
    if(board[row][col] == 0){
        return numberAttempt(board,row,col,1);
    }
    if (col == SUDOKU_GRID_SIZE - 1){
        return solveSudokuRec(board,row + 1, 0);
    }
    return solveSudokuRec(board,row, col + 1);
}

int numberAttempt(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int row, int col,int digitToTry){
    int result;
    if (digitToTry > 9){
        board[row][col] = 0;
        return 0;
    }
    board[row][col] = digitToTry;
    result = checkCollumn(board,col,digitToTry,0,row) && checkRow(board,row,digitToTry,0,col);
    if (checkBottomRightBox(SUDOKU_SUBGRID_SIZE,row,col)){
        result &= isBoxPerfectRec(board,row,col,1,1);
    }
    if (result && solveSudokuRec(board,row,col)){
        return 1;
    }
    return numberAttempt(board,row,col,digitToTry + 1);
}
int isBoxPerfectRec(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int row,int col,int rowCounter, int totalCounter){
    int result;
    int whichCounter;
    if (totalCounter == (SUDOKU_SUBGRID_SIZE * SUDOKU_SUBGRID_SIZE) + 1){
        return 1;
    }
    if (rowCounter == 3){
        if (checkBoxLoopRec(board,row - 1, col + 2,board[row][col],rowCounter - 2,totalCounter)){
            result = isBoxPerfectRec(board,row - 1, col + 2, rowCounter - 2, totalCounter + 1);
        }
    }
    else {
        if (checkBoxLoopRec(board,row, col -1, board[row][col],rowCounter + 1, totalCounter)){
            result = isBoxPerfectRec(board,row,col - 1, rowCounter + 1, totalCounter + 1);
        }
        else{
            result = 0;
        }
    }
    return result;
}
int checkBoxLoopRec(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int row,int col, int valueToCheck, int rowCounter, int totalCounter){
    int result;
    if (valueToCheck == board[row][col]){
        return 0;
    }
    if (totalCounter == SUDOKU_SUBGRID_SIZE * SUDOKU_SUBGRID_SIZE){
        return 1;
    }
    result = rowCounter == SUDOKU_SUBGRID_SIZE ? checkBoxLoopRec(board,row- 1,col + 2,valueToCheck,rowCounter - 2,totalCounter + 1)
                                      : checkBoxLoopRec(board,row,col - 1,valueToCheck, rowCounter + 1, totalCounter + 1);
    return result;
}

int checkBottomRightBox(int boxSize, int row, int col){
    if (((row + 1) % boxSize == 0) && ((col + 1) % boxSize == 0)){
        return 1;
    }
    return 0;
}

int checkCollumn(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int col, int valueToCheck, int currRow, int rowChecked){
    if (!isInBounds(SUDOKU_GRID_SIZE,SUDOKU_GRID_SIZE,currRow,col)){
        return 1;
    }
    if (board[currRow][col] == valueToCheck && currRow != rowChecked){
        return 0;
    }
    return checkCollumn(board,col,valueToCheck,currRow + 1, rowChecked);
}
int checkRow(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int row, int valueToCheck, int currCol, int colChecked){
    if (!isInBounds(SUDOKU_GRID_SIZE,SUDOKU_GRID_SIZE,row,currCol)){
        return 1;
    }
    if (board[row][currCol] == valueToCheck && currCol != colChecked){
        return 0;
    }
    return checkRow(board,row,valueToCheck,currCol + 1, colChecked);
}


void printSudoku(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE])
{
    printf("+-------+-------+-------+\n");
    for (int i = 0; i < SUDOKU_GRID_SIZE; i++)
    {
        printf("| ");
        for (int j = 0; j < SUDOKU_GRID_SIZE; j++)
        {
            if (board[i][j] == 0)
                printf(". ");
            printf("%d ", board[i][j]);

            if ((j + 1) % SUDOKU_SUBGRID_SIZE == 0)
                printf("| ");
        }
        printf("\n");
        if ((i + 1) % SUDOKU_SUBGRID_SIZE == 0)
            printf("+-------+-------+-------+\n");
    }
}



/***************************
*********** TODO ***********
****************************/


void task1ReversePhraseImplementation(){
    char c = getchar();
    if (c == '\n'){
        printf("The reversed phrase is:\n");
    }
    else if (c != '\n'){
        task1ReversePhraseImplementation();
        printf("%c", c);
    }
    
}


int task2CheckPalindromeImplementation(int length)
{
    if (length <= 1 ){
        if (length == 1){
            getchar();
        }
        return 1;
    }
    char charone = getchar();
    int result = task2CheckPalindromeImplementation(length -2);
    char chartwo = getchar();
    return (charone == chartwo) & result;

}


void task3GenerateSentencesImplementation(char subjects[][LONGEST_TERM+1], int subjectsCount, char verbs[][LONGEST_TERM+1], int verbsCount, char objects[][LONGEST_TERM+1], int objectsCount){
    if (subjectsCount > 1){
       task3GenerateSentencesImplementation(subjects, subjectsCount - 1, verbs, verbsCount, objects, objectsCount);
    }
    int currSubject = subjectsCount - 1;
    int startNum = 1 + (currSubject * verbsCount * objectsCount);
    
    printVerbs(subjects[currSubject],verbs,verbsCount,objects,objectsCount,verbsCount-1, startNum);

}


int task4SolveZipBoardImplementation(int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], int size, int startR, int startC, int highest)
{
    return task4SolveZipBoardRec(board,solution,size,startR,startC,highest,0,1);
    return 0;
}


int task5SolveSudokuImplementation(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE])
{
    return solveSudokuRec(board,0,0);
}

