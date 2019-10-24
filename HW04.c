#include <stdio.h>
#include <stdlib.h>

/*
1. *Количество маршрутов с препятствиями. Реализовать чтение массива с препятствием и
    нахождение количество маршрутов.

3. ***Требуется обойти конём шахматную доску размером NxM, пройдя через все поля доски
    по одному разу.
*/

#define M 8
#define N 8

void printDoubleArr(int *arr, int size_N, int size_M)
{
    for (int i = 0; i < size_N; ++i) {
        for (int j = 0; j < size_M; ++j)
            printf("%4d", *(arr + j + i*size_M));
        printf("\n");
    }//for (int i = 0; i < size_N; ++i)
}//void printDoubleArr(int *arr, int size_N, int size_M)

/*********************** Ex. 1 ****************************/
int field[N][M];

void initField()
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            field[i][j] = 1;
}//void initField()

void setObst(int num_obst)
{
    for (int i = 0; i < num_obst; ++i)
        field[rand()%8][rand()%8] = 0;
}//void setObst(int num_obst)

void numRoutObst()
{
    for (int y = 0; y < M; ++y)
        for (int x = 0; x < N; ++x)
            if ((x != 0 || y != 0) && field[x][y] != 0)
                field[x][y] = ((x-1 < 0)?0:field[x-1][y]) + ((y-1 < 0)?0:field[x][y-1]);
}//void numRoutObst()

/*********************** Ex. 2 ****************************/
int board[N][M];

void initBoard()
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            board[i][j] = 0;
}//void initBoard()

#define KNIGHT 8 //максимально возможное кольчество ходов конем
//последовательность обхода конём возможных полей
// [ ](7)[ ](0)[ ]
// (6)[ ][ ][ ](1)
// [ ][ ]{K}[ ][ ]
// (5)[ ][ ][ ](2)
// [ ](4)[ ](3)[ ]

enum knight_move
{
    km1, km2, km3, km4, km5, km6, km7, km8
};//enum knight_move

void nextMove(unsigned shift, int *x, int *y)
{//пересчитывает координаты следующего хода в зависимости от его номера в соответствии с последовательностью
    switch (shift) {
    case km1: (*x)++;   *y -= 2;
        break;
    case km2: *x += 2;  (*y)--;
        break;
    case km3: *x += 2;  (*y)++;
        break;
    case km4: (*x)++;   *y += 2;
        break;
    case km5: (*x)--;   *y += 2;
        break;
    case km6: *x -= 2;  (*y)++;
        break;
    case km7: *x -= 2;  (*y)--;
        break;
    case km8: (*x)--;    *y -= 2;
        break;
    default:
        break;
    }//switch (shift)
}//void nextMove(unsigned shift, int *x, int *y)

unsigned checkBoard(int x, int y)
{// функция возвращает число, биты которого означают возможно ли поставить коня в поля от 0 до 7 в соответствии с последовательностью
    unsigned check = 0;
    int new_x = x, new_y = y;
    for (unsigned i = 0; i < KNIGHT; ++i) {
        nextMove(i, &new_x, &new_y);
        if(!board[new_x][new_y] && (new_x >= 0 && new_x < N) && (new_y >= 0 && new_y < M))
            check ^= (1 << i);
        new_x = x;
        new_y = y;
    }//for (int i = 0; i < KNIGHT; ++i)
    return check;
}//unsigned checkBoard(int x, int y)

int knightMove(int move, int x, int y)
{
    if(move == N*M + 1) return 1;
    unsigned check = checkBoard(x,y);
    int new_x = x, new_y = y;
    if(check)
        for (unsigned i = 0; i < KNIGHT; ++i) {
            if((check >> i) & 1) {
                nextMove(i, &new_x, &new_y);
                board[new_x][new_y] = move;
                if(knightMove(move+1, new_x, new_y)) return 1;
                else {
                    board[new_x][new_y] = 0;
                    new_x = x;
                    new_y = y;
                }//if(knightMove(move+1, new_x, new_y))
            }//if((check >> i) & 1)
        }//for (int i = 0; i < KNIGHT; ++i)
    return 0;
}//int knightMove(int move, int x, int y)

void mainMove()
{
    int move = 1; //первый ход
    for (int x = 0; x < N; ++x)
        for (int y = 0; y < M; ++y) {
            board[x][y] = move;
            if(knightMove(move+1, x, y)) return;
            else board[x][y] = 0;
        }//for (int y = 0; y < M; ++y)
}//void mainMove()

int main()
{
printf("********************** Ex. 1 ***************************\n\n");
    initField();
    setObst(15);
    printDoubleArr(*field, N, M);
    printf("\n");
    numRoutObst();
    printDoubleArr(*field, N, M);
printf("\n\n");

printf("********************** Ex. 2 ***************************\n\n");
    initBoard();
    mainMove();
    printDoubleArr(*board, N, M);
printf("\n\n");

    return 0;
}//int main()
