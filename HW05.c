#include <stdio.h>
#include <stdlib.h>

/*
1. Написать программу, которая определяет, является ли введенная скобочная последовательность правильной. Примеры правильных скобочных выражений: (), ([])(), {}(), ([{}]), неправильных — )(, ())({), (, ])}), ([(]) для скобок [,(,{.
Например: (2+(2*2)) или [2/{5*(4+7)}]

2. *Создать функцию, копирующую односвязный список (то есть создает в памяти копию односвязного списка, без удаления первого списка).

3. *Реализовать очередь на основе двусвязного списка.
*/

#define T char

typedef int boolean;
#define true 1
#define false 0

typedef struct Node {
    T data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} Stack;

boolean push(Stack *st, T value)
{
    Node *temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL) return false;

    temp->data = value;
    temp->next = st->head;

    st->head = temp;
    st->size++;
    return true;
}//boolean push(Stack *st, T value)

T pop(Stack *st)
{
    if (st->size == 0) return -1;

    Node *temp = st->head;
    T result = st->head->data;

    st->head = st->head->next;
    st->size--;
    free(temp);
    return result;
}//T pop(Stack *st)

/*********************** Ex. 1 ****************************/
boolean clearBrackets(Stack *st, T value)
{
    if (st->size == 0) return false;
    if(st->head->data == value) {
        pop(st);
        return true;
    } else {
        Node *prev = st->head;
        Node *temp = st->head->next;
        for (int i = 0; i < st->size-1; ++i, prev = temp, temp = temp->next)
            if(temp->data == value) {
                prev->next = temp->next;
                st->size--;
                free(temp);
                return true;
            }//if(temp->data == value)
        return false;
    }//if(st->head->data == value)
}//boolean clearBrackets(Stack *st, T value)

boolean checkBrackets(Stack *st)
{
    for (char ch = '?'; ch != '\n'; ch = (char)getchar())
        switch (ch) {
        case '(': case '[': case '{':
            push(st, ch);
            break;
        case ')':
            if(!clearBrackets(st, ch - 1)) return false;
            break;
        case ']': case '}':
            if(!clearBrackets(st, ch - 2)) return false;
            break;
        default:
            break;
        }//switch (ch)
    if (st->size) return false;
    else return true;
}//boolean checkBrackets(Stack *st)

/*********************** Ex. 2 ****************************/
Node* cpNode(Node *N, int size)
{
    if (size) {
        Node *cp_N = (Node*)malloc(sizeof(Node));
        cp_N->data = N->data;
        cp_N->next = cpNode(N->next, size - 1);
        return cp_N;
    } else return NULL;
}//Node* cpNode(Node *N, int size)

Stack* cpLinkList(Stack *st)
{
    Stack *cp_st = (Stack*)malloc(sizeof(Stack));
    cp_st->head = cpNode(st->head, st->size);
    cp_st->size = st->size;
    return cp_st;
}//Stack* cpLinkList(Stack *st)

/*********************** Ex. 3 ****************************/
typedef struct QNode {
    T data;
    struct QNode *next;
    struct QNode *prev;
} QNode;

typedef struct {
    QNode *head;
    QNode *tail;
    int size;
} Queue;

boolean pushBack(Queue *qu, T value)
{
    QNode *temp = (QNode*)malloc(sizeof(QNode));
    if (temp == NULL) return false;

    temp->data = value;
    temp->next = qu->tail;
    temp->prev = NULL;
    if (qu->size) qu->tail->prev = temp;
    else qu->head = temp; //Если добавляется первый элемент.

    qu->tail = temp;
    qu->size++;
    return true;
}//boolean pushBack(Queue *qu, T value)

T popFront(Queue *qu)
{
    if (qu->size == 0) return -1;

    QNode *temp = qu->head;
    T result = qu->head->data;

    qu->head = qu->head->prev;
    qu->size--;
    if (qu->size) qu->head->next = NULL;
    else qu->tail = NULL; //Если извлекается последний элемент.
    free(temp);
    return result;
}//T popFront(Queue *qu)

int main()
{
printf("********************** Ex. 1 ***************************\n\n");
    Stack s;
    s.size = 0;
    s.head = NULL;
    printf("Enter the sequence: ");
    printf("%s", checkBrackets(&s)?"The sequence is correct!":"The sequence is incorrect!");
printf("\n\n");

printf("********************** Ex. 2 ***************************\n\n");
    s.size = 0;
    s.head = NULL;
    for (char ch = 'a'; ch <= 'h'; ++ch)
        push(&s, ch);
    Stack *s1;
    s1 = cpLinkList(&s);
    for (;s.size > 0;)
        printf("%c ", pop(&s));
    printf("\n");
    for (;s1->size > 0;)
      printf("%c ", pop(s1));
printf("\n\n");

printf("********************** Ex. 3 ***************************\n\n");
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;
    for (char ch = 'a'; ch <= 'h'; ++ch)
        pushBack(&q, ch);
    for (;q.size > 0;)
      printf("%c ", popFront(&q));
printf("\n\n");

    return 0;
}//int main()
