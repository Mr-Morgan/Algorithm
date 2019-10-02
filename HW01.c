#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Домашнее задание "Простые алгоритмы" (Урок 1)
 * Выполнил: А.Зюльковский.

1. Ввести вес и рост человека. Рассчитать и вывести индекс массы тела по формуле I=m/(h*h);
   где m-масса тела в килограммах, h - рост в метрах.

3. Написать программу обмена значениями двух целочисленных переменных:
    b. *без использования третьей переменной.

4. Написать программу нахождения корней заданного квадратного уравнения.

6. Ввести возраст человека (от 1 до 150 лет) и вывести его вместе с последующим словом «год»,
   «года» или «лет».

7. Имеются числовые координаты двух полей шахматной доски (x1,y1,x2,y2). Требуется определить,
   относятся ли к поля к одному цвету или нет.

9. Даны целые положительные числа N и K. Используя только операции сложения и вычитания, найти
   частное от деления нацело N на K, а также остаток от этого деления.

10. Дано целое число N (> 0). С помощью операций деления нацело и взятия остатка от деления
    определить, имеются ли в записи числа N нечетные цифры. Если имеются, то вывести True,
    если нет — вывести False.

14. * Автоморфные числа. Натуральное число называется автоморфным, если оно равно последним
    цифрам своего квадрата. Например, 25 \ :sup: 2 = 625. Напишите программу, которая выводит
    на экран все автоморфные числа, в пределах 1_000_000

15. Дублирую задание по улучшению алгоритма с урока))
*/

/*********************** Ex. 1 ****************************/
double BMICalc(double m, double h)
{//m-масса тела в килограммах, h - рост в метрах
    if ((m != 0.0) && (h != 0.0))
        return m / (h * h);
    else return 0.0;
}//double BMICalc(double m, double h)

/*********************** Ex. 3 ****************************/
void mySwap(int *a, int *b)
{
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}//void mySwap(int *a, int *b)

/*********************** Ex. 4 ****************************/
int calcSquarEq(double a, double b, double c, double *x1, double *x2)
{//возвращает количество корней
    if (a == 0.0) {
        if (b == 0.0) return 0;
        else {
            *x1 = -c / b;
            *x2 = *x1;
            return 1;
        }//if (b == 0.0)
    } else {
        double D = b*b - 4*a*c;
        if (D > 0.0) {
            *x1 = (-b + sqrt(D))/(a+a);
            *x2 = (-b - sqrt(D))/(a+a);
            return 2;
        } else if (D == 0.0) {
            *x1 = -b /(a+a);
            *x2 = *x1;
            return 1;
        } else return 0;
    }//if (a == 0.0)
}//int calcSquarEq(double a, double b, double c, double *x1, double *x2)

/*********************** Ex. 6 ****************************/
#define MIN_AGE 1
#define MAX_AGE 150

void printAge(int age)
{
    if((age >= MIN_AGE) && (age <= MAX_AGE)) {
        if(((age/10)%10 != 1) && (age%10 == 1))
            printf("%d god.", age);
        else if (((age/10)%10 != 1) && ((age%10 >= 2) && (age%10 <= 4)))
            printf("%d goda.", age);
        else
            printf("%d let.", age);
    }//if((age >= MIN_AGE) && (age <= MAX_AGE))
}//void printAge(int age)

/*********************** Ex. 7 ****************************/
int isOneColor(int X1, int Y1, int X2, int Y2)
{//возвращает 0 если цвет разный, 1 если одинаковый
    X1 += Y1;
    X2 += Y2;
    if (X1%2 == X2%2) return 1;
    else return 0;
}//int isOneColor(int X1, int Y1, int X2, int Y2)

/*********************** Ex. 9 ****************************/
void division(int *N, int *K, int *quotient, int *remaimder)
{//возвращает остаток от деления (remaimder) и частное (quotient) от деления нацело N на K
    if (*N < *K) mySwap(N, K);
    int d = *K, count = 0;
    for (count = 0; d <= *N; ++count)
        d += *K;
    d -= *K;
    *remaimder = *N - d;
    *quotient = count;
}//void division(int *N, int *K, int *quotient, int *remaimder)

/*********************** Ex. 10 ***************************/
int isOddNumder(int numb)
{
    for (int d = numb%10; numb > 0; numb /= 10, d = numb%10)
        if (d % 2 == 1)
            return 1;
    return 0;
}//int isOddNumder(int numb)

/*********************** Ex. 14 ***************************/
#define MAX_AUTO 1000000
unsigned long pow10(unsigned pow)
{
    return pow?10*pow10(--pow):1;
}//unsigned long pow10(unsigned pow)

void printAutomorph()
{
    for (unsigned long i = 0; i <= MAX_AUTO; ++i) {
        unsigned count = 0;
        for (unsigned long numb = i; numb > 0; numb/=10)
            count++;
        if ((i*i)%pow10(count) == i)
            printf("%lu\t", i);
    }//for (unsigned long i = 0; i <= MAX_AUTO; ++i)
}//void printAutomorph()

/*********************** Ex. 15 ***************************/
float mean() {
    int sum = 0, counter = 0;
    for (int in = 0; (scanf("%d", &in) && (in != -1)); counter++)
        sum += in;
    if (counter != 0)
        return (float)sum / counter;
    else
        return -1;
}//float mean()


int main()
{
printf("********************** Ex. 1 ***************************\n\n");
    double I = 69.6, h = 179.0;
    printf("Enter your weight(kg), and growth(m): ");
    scanf("%lf%lf", &I, &h);
    I = BMICalc(I, h);
    if (I != 0.0)
        printf("Your BMI = %lf.", I);
    else
        perror("Incorrect input!\nEnter numbers separated by a space.");
printf("\n\n");

printf("********************** Ex. 3 ***************************\n\n");
    int x = 1, y = -1;
    printf("x = %d\ty = %d\n", x, y);
    mySwap(&x, &y);
    printf("x = %d\ty = %d", x, y);
printf("\n\n");

printf("********************** Ex. 4 ***************************\n\n");
    double a = -1.0, b = 2.0, c = 1.0, x1 = 0.0, x2 = 0.0;
    printf("The equation %.1lf*x^2 + %.1lf*x + %.1lf = 0 ", a, b, c);
    switch (calcSquarEq(a,b,c,&x1,&x2)) {
    case 0:
        printf("has no roots.");
        break;
    case 1:
        printf("has one root.\nx = %.3lf", x1);
        break;
    case 2:
        printf("has two roots.\nx[1] = %.3lf\nx[2] = %.3lf", x1, x2);
        break;
    default:
        perror("Unknown error in function calcSquarEq(..).\n");
        break;
    }//switch (calcSquarEq(a,b,c,&x1,&x2))
printf("\n\n");

printf("********************** Ex. 6 ***************************\n\n");
    int age = 11;
        printAge(age);
printf("\n\n");

printf("********************** Ex. 7 ***************************\n\n");
    int X1 = 4, Y1 = 5, X2 = 8, Y2 = 7;
    if(isOneColor(X1, Y1, X2, Y2))
        printf("Chess fields of the same color.");
    else
        printf("Chess fields of different color.");
printf("\n\n");

printf("********************** Ex. 9 ***************************\n\n");
    x = 12;
    y = 3;
    int q = 0, r = 0;
    division(&x, &y, &q, &r);
    printf("%d/%d = %d\nRest: %d\n", x, y, q, r);
printf("\n\n");

printf("********************** Ex. 10 **************************\n\n");
    x = 12264;
    if (isOddNumder(x)) printf("True\n");
    else printf("False\n");
printf("\n\n");

printf("********************** Ex. 14 **************************\n\n");
    printAutomorph();
printf("\n\n");

printf("********************** Ex. 15 **************************\n\n");
    printf("Mean: %.2f", mean());
printf("\n\n");

    return 0;
}//int main()

