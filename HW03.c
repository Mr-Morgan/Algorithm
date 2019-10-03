#include <stdio.h>
#include <stdlib.h>

/*
1. Попробовать оптимизировать пузырьковую сортировку. Сравнить количество операций
   сравнения оптимизированной и неоптимизированной программы. Написать функции
   сортировки, которые возвращают количество операций.

2. *Реализовать шейкерную сортировку.

3. Реализовать бинарный алгоритм поиска в виде функции, которой передаётся отсортированный
   массив. Функция возвращает индекс найденного элемента или –1, если элемент не найден.

4. *optional. Погуглить как осуществляется Pigeon Hole Sort и попробовать реализовать на языке С..
*/

#define MAX_SIZE 10
#define true 1
#define false 0

void mySwap(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}//void mySwap(int *a, int *b)

void arrayFiller(int *arr, const int size)
{
    for(int i = 0; i < size; ++i)
        *(arr + i) = rand()%100 + 1;
}//void arrayFiller(int *arr, const int size)

void printArray(int *arr, const int size)
{
    for(int i = 0; i < size; ++i)
        printf("%d\t", arr[i]);
    printf("\n");
}//void printArray(int *arr, const int size)

/*********************** Ex. 1 ****************************/
int bubbleSort(int *arr, const int size)
{
    int operations = 0;
    for (int i = 0; i < size; ++i)
        for(int j = 0; j < size - 1; ++j)
            if (arr[j] > arr[j+1]) {
                mySwap(&arr[j], &arr[j+1]);
                operations++;
            }//if (arr[j] > arr[j+1])
    return operations;
}//int bubbleSort(int *arr, const int size)

int bubbleSortMod(int *arr, const int size)
{
    int operations = 0;
    for(int L = 0, R = size - 1; L < R; L++, R--) {
        for(int j = L; j <= R; ++j) {
            if (arr[j] > arr[R]) {
                mySwap(&arr[R], &arr[j]);
                operations++;
            }//if (arr[j] > arr[R])
            if (arr[j] < arr[L]) {
                mySwap(&arr[L], &arr[j]);
                operations++;
            }//if (arr[j] < arr[L])
        }//for(int j = L; j <= R; ++j)
    }//for(int L = 0, R = size - 1; L < R; L++, R--)
    return operations;
}//int bubbleSort(int *arr, const int size)

/*********************** Ex. 2 ****************************/
int changeFlag(int flag)
{
    if(flag) return false;
    else return true;
}//int changeFlag(int flag)

int shakerSort(int *arr, const int size)
{
    int operations = 0;
    int flag = true; // true -> (++), false <- (--)
    int i_min = 0, i_max = size - 1;
    for(int i = i_min+1; i_max > i_min; (flag?i++:i--)) {
        if(flag){
            if(arr[i-1] > arr[i]) {
                mySwap(&arr[i-1], &arr[i]);
                operations++;
            }//if(arr[i] > arr[i+1])
        }else {
            if(arr[i+1] < arr[i]) {
                mySwap(&arr[i+1], &arr[i]);
                operations++;
            }//if(arr[i+1] < arr[i])
        }//if(flag)
        if(i == (flag?i_max:i_min)){
            if(flag) i_max--;
            else i_min++;
            flag = changeFlag(flag);
        }//if(i == flag?i_max:i_min)
    }//for(int i = i_min+1; i_max > i_min; (flag?i++:i--))
    return operations;
}//int sheikerSort(int *arr, const int size)

/*********************** Ex. 3 ****************************/
int binSearch(int *arr, const int size, int value)
{
    int L = 0, R = size - 1;
    int m = L + ((R - L) >> 1);
    for(; ((L <= R) && (arr[m] != value)); m = L + ((R - L) >> 1))
        if(arr[m] < value) L = m + 1;
        else R = m - 1;
    if (arr[m] == value) return m;
    else return  -1;
}//int binSearch(int *arr, const int size, int value)

/*********************** Ex. 4 ****************************/
int pigeonHoleSort(int *arr, const int size, int min, int max)
{
    int operations = 0;
    int range = max - min + 1;
    int *hole = (int*)calloc((unsigned)(range), sizeof(int));
    for(int i = 0; i < size; ++i, operations++)
        hole[arr[i] - min]++;
    for (int i = 0, j = 0; i <= range; i++)
        for (; hole[i] > 0; hole[i]--, j++, operations++)
            arr[j] = i + min;
    free(hole);
    return operations;
}//int pigeonHoleSort(int *arr, const int size, int min, int max)

int main()
{
printf("********************** Ex. 1 ***************************\n\n");
    int arr[MAX_SIZE], array[MAX_SIZE], array_1[MAX_SIZE], array_2[MAX_SIZE];
    arrayFiller(arr, MAX_SIZE);
    for(int i = 0; i < MAX_SIZE; ++i) {
        array[i] = arr[i];
        array_1[i] = arr[i];
        array_2[i] = arr[i];
    }
    printArray(arr, MAX_SIZE);

    printf("Operations: %d\n",bubbleSort(arr, MAX_SIZE));
    printArray(arr, MAX_SIZE);
    printf("Operations: %d\n",bubbleSortMod(array, MAX_SIZE));
    printArray(array, MAX_SIZE);
printf("\n\n");

printf("********************** Ex. 2 ***************************\n\n");
    printArray(array_1, MAX_SIZE);
    printf("Operations: %d\n",shakerSort(array_1, MAX_SIZE));
    printArray(array_1, MAX_SIZE);
printf("\n\n");

printf("********************** Ex. 3 ***************************\n\n");
    int value = 22;
    printf("Index: %d\n",binSearch(array, MAX_SIZE, value));
printf("\n\n");

printf("********************** Ex. 4 ***************************\n\n");
    printf("Operations: %d\n",pigeonHoleSort(array_2, MAX_SIZE, 0, 99));
    printArray(array_2, MAX_SIZE);
printf("\n\n");

    return 0;
}//int main()
