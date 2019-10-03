#include <stdio.h>
#include <stdlib.h>

/*
1. Реализовать функцию перевода чисел из десятичной системы в двоичную, используя
   рекурсию.
2. Реализовать функцию возведения числа a в степень b:
    a. Без рекурсии.
    b. Рекурсивно.
    c. *Рекурсивно, используя свойство чётности степени.
3. **Исполнитель «Калькулятор» преобразует целое число, записанное на экране. У
   исполнителя две команды, каждой присвоен номер:
   1. Прибавь 1.
   2. Умножь на 2.
   Первая команда увеличивает число на экране на 1, вторая увеличивает его в 2 раза.
   Определить, сколько существует программ, которые преобразуют число 3 в число 20:
   *С использованием рекурсии.
*/

/*********************** Ex. 1 ****************************/
#define U unsigned
void decToBin(U dec, U size, U *bin)
{
    if (dec > 0) {
        bin[--size] = dec % 2;
        decToBin(dec/2, size, bin);
    } else return;
}//void decToBin(U dec, U size, U *bin)

U numOfBits(U numb)
{
    U i = 0;
    for (; numb > 0; numb >>= 1) i++;
    return i;
}//U numOfBits(U numb)

void printArray(U *arr, U size)
{
    U i = 0;
    for(; i < size; ++i)
        printf("%u", arr[i]);
}//void printArray(U *arr, U size)

/********************** Ex. 2 a ***************************/
long myPowa(int a, int b)
{
    long power = 1;
    for (; b; --b) power *= a;
    return power;
}//long myPowa(int a, int b)

/********************** Ex. 2 b ***************************/
long myPowb(int a, int b)
{
    return b?a*myPowb(a, --b):1;
}//long myPowb(int a, int b)

/********************** Ex. 2 c ***************************/
long myPowc(int a, int b)
{
    return b?((b%2)?a*myPowc(a, --b)
                  :myPowc(a*a, b/2)):1;
}//long myPowc(int a, int b)

/*********************** Ex. 3 ****************************/
U cC(U s, U e)//calcCounter
{//s - start, e - end
    if (s > e/2) return 1;
    else return cC(s+1, e)+cC(s << 1, e);
}//U cC(U s, U e)

int main()
{
printf("********************** Ex. 1 ***************************\n\n");
    U decimal = 123;
    U size = numOfBits(decimal);
    U *binary = (U*)calloc(size, sizeof(U));
    decToBin(decimal, size, binary);
    printf("Decimal:\t%u\nBinary: \t", decimal);
    printArray(binary, size);
printf("\n\n");

printf("********************* Ex. 2 a **************************\n\n");
    int a = 2, b = 25;
    printf("%d^(%d) = %ld", a, b, myPowa(a,b));
printf("\n\n");

printf("********************* Ex. 2 b **************************\n\n");
    printf("%d^(%d) = %ld", a, b, myPowb(a,b));
printf("\n\n");

printf("********************* Ex. 2 c **************************\n\n");
    printf("%d^(%d) = %ld", a, b, myPowc(a,b));
printf("\n\n");

printf("********************** Ex. 3 ***************************\n\n");
    U start = 3, end = 20;
    printf("Numbers of operations: %u", cC(start,end));
printf("\n\n");

    return 0;
}//int main()
