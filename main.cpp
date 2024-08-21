#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

int scan (double* a);
int clean_buffer(void);
int check(double* a);

int solve (double a, double b, double c, double* x1, double* x2);

const int INF_ROOTS = -1;

int main()
{

    printf("Enter coefficients for solving a equation\n");
    double a = 0, b = 0, c = 0;


    scan(&a);
    scan(&b);
    scan(&c);
    printf ("%lg %lg %lg", a, b, c);

    double x1 = 0, x2 = 0; // #отдельно ввод, вывод и другое
    int nroots = solve( a, b, c, &x1, &x2);

    enum num_of_roots {zero_roots, one_root, two_roots};

    switch (nroots){

        case zero_roots: printf ("no roots\n"); //добавить константу на указатель
                break;
        case one_root: printf ("x = %lg\n", x1);
                break;
        case two_roots: printf ("x1 = %lg, x2 = %lg\n", x1, x2);
                break;
        case INF_ROOTS: printf("any number\n");
                break;
        default: printf("error\n");
                return 1;

    return 0;
    }
}
int solve(double a, double b, double c, double* x1, double* x2){   //функция solve решает квадратное уравнение

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    enum num_of_roots {zero_roots, one_root, two_roots};

    if (a == 0){     //!! #функция для проверки точности
        if (b == 0){
            return (c == 0)? INF_ROOTS: zero_roots;
        }
        else{
            *x1 = -c/b;
        return 1;
        }
    }
    else{
        double diskr = b*b - 4*a*c;

        if (diskr == 0){
            *x1 = *x2 = -b/ (2*a);

            return one_root;
        }
        else if (diskr < 0) {
            return 0;
        }
        else{
            *x1 = (-b + sqrt(diskr))/(2*a);
            *x2 = (-b - sqrt(diskr))/(2*a);
            return two_roots;
        }
    }
}
int scan (double* a)
{
    while (check(a) != 0)
    {
    printf("enter new\n");
    }
    return 0;
}
int check(double* a){

    scanf("%lg", a);
    int ch = 0;

    while (ch != '\n')
    {
        ch = getchar();
        if (isalpha(ch))
        {
            clean_buffer();
            return 1;
        }

    }
    return 0;
}

int clean_buffer(){ //функция clean_buffer чистит поток ввода
    while (getchar() != '\n'){
    }
    return 0;
}
// #условие на выход из программы
