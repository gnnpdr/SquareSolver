#include <stdio.h>
#include <math.h>

int check_digit (double* a);
int clean_buffer(void);

int solve (double a, double b, double c, double* x1, double* x2);

const int INF_ROOTS = -1;

int main()
{

    printf("Enter coefficients for solving a equation\n");
    double a = 0, b = 0, c = 0;

    check_digit (&a);
    check_digit (&b);
    check_digit (&c);

    double x1 = 0, x2 = 0; // отдельно ввод, вывод и другое
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
int solve(double a, double b, double c, double* x1, double* x2){
    if (a == 0){     // функция для проверки точности
        if (b == 0){
            return (c == 0)? INF_ROOTS: 0; // isfinite, нулевые указатели, не равны ли они
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
            return 1; // заменить на enum
        }
        else if (diskr < 0) {
            return 0;
        }
        else{
            *x1 = (-b + sqrt(diskr))/(2*a);
            *x2 = (-b - sqrt(diskr))/(2*a);
            return 2;
        }
    }
}
int check_digit(double* a){ // комментарии к функции
    while (scanf("%lg", a) != 1) {
        clean_buffer();
        printf("enter coefficient as number\n");
    }
    return 0;
}

int clean_buffer(){
    while (getchar() != '\0'){ // упример 12апол
    }
    return 0;
}
// условие на выход из программы
