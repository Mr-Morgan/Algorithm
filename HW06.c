#include <stdio.h>
#include <stdlib.h>

/*
1. Реализовать простейшую хэш-функцию. На вход функции подается строка, на выходе сумма кодов символов.

2. Реализовать двоичное дерево поиска

а) Добавить обход дерева различными способами;
б) Реализовать поиск в двоичном дереве поиска;

3. ***Разработать базу данных студентов из двух полей “Имя”, “Возраст”, “Табельный номер” в которой использовать все знания, полученные на уроках.
    Считайте данные в двоичное дерево поиска. Реализуйте поиск по какому-нибудь полю базы данных (возраст, вес)
*/

#define T int
#define SIZE 10

typedef int boolean;
#define true 1
#define false 0

/*********************** Ex. 1 ****************************/
int easyHash(char *arr, const int size)
{
    int hash = 0;
    for (int i = 0; i < size; ++i) hash += arr[i];
    return hash;
}//int easyHash(char *arr)

/*********************** Ex. 2 ****************************/
T arr[SIZE] = {5, 8, 7, 3, 0, 9, 1, 2, 4, 6};
int i = 0;

typedef struct BinNode {
    T data;
    struct BinNode *left;
    struct BinNode *right;
    struct BinNode *parent;
} BNode;

BNode* backToRoot(BNode *p)
{
    return (p->parent)?backToRoot(p->parent):p;
}//BNode* backToRoot(BNode *p)

int main()
{
printf("********************** Ex. 1 ***************************\n\n");
    char str[SIZE];
    for (int i = 0; i < SIZE; ++i) str[i] = i + 'a';
    printf("HASH: %d\n", easyHash(str, SIZE));
printf("\n\n");

printf("********************** Ex. 2 ***************************\n\n");

printf("\n\n");

    return 0;
}//int main()
