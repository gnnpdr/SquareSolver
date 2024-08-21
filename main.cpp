#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

enum num_of_roots {zero_roots, one_root, two_roots};


int enter (double* a, double* b, double* c);

int scan (double* a);
int check(double* a);
int clean_buffer(void);

int solve (double a, double b, double c, double* x1, double* x2);

int solvation_of_linear_equation (double b, double c, double* x1);
int solvation_of_square_equation (double a, double b, double c, double* x1, double* x2);

int output (int a, double x1, double x2);

int unitest (int test_num, double a, double b, double c, double x1_expected, double x2_expected, int nroots_expected);

const int INF_ROOTS = -1;

int main()
{

    printf("Enter coefficients for solving a equation\n");

    double a = 0, b = 0, c = 0;
    const double *pa = &a, *pb = &b, *pc = &c;

    enter(&a, &b, &c);

    double x1 = 0, x2 = 0;
    int nroots = solve(a, b, c, &x1, &x2);

    output (nroots, x1, x2);

    unitest(1, 1, -5, 6, 3, 2, 2);         //two_roots_case
    unitest(2, 1, -4, 4, 2, 2, 1);         //one_root_case
    unitest(3, 1, 2, 4, 0, 0, 0);          //zero_roots_case
    unitest(4, 1, 1.5, 0.5, -0.5, -1, 2);  //float_coefficients_case
    unitest(5, 0, 0, 0 ,0, 0, -1);         //inf_answer_case

    return 0;
}

int solve(double a, double b, double c, double* x1, double* x2){

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (a == 0)     //!! #функция для проверки точности
            solvation_of_linear_equation (b, c, x1);

    else
            solvation_of_square_equation (a, b, c, x1, x2);


}
int scan (double* a){
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

int clean_buffer(){
    while (getchar() != '\n'){
    }
    return 0;
}

int enter (double* a, double* b, double* c){
    scan(a);
    scan(b);
    scan(c);

    return 0;
}

int output (int nroots, double x1, double x2){

    switch (nroots){

        case zero_roots: printf ("no roots\n");
                break;
        case one_root: printf ("x = %lg\n", x1);
                break;
        case two_roots: printf ("x1 = %lg, x2 = %lg\n", x1, x2);
                break;
        case INF_ROOTS: printf("any number\n");
                break;
        default: printf("error\n");
                return 1;
    }
    return 0;
}

int solvation_of_linear_equation (double b, double c, double* x1){

    if (b == 0)
            return (c == 0)? INF_ROOTS: zero_roots;

        else{
            *x1 = -c/b;
            return one_root;
        }
}

int solvation_of_square_equation (double a, double b, double c, double* x1, double* x2){

    double diskr = b*b - 4*a*c;

        if (diskr == 0){
            *x1 = *x2 = -b/ (2*a);

            return one_root;
        }
        else if (diskr < 0) {
            return zero_roots;
        }
        else{
            *x1 = (-b + sqrt(diskr))/(2*a);
            *x2 = (-b - sqrt(diskr))/(2*a);
            return two_roots;
        }
}

int unitest (int test_num, double a, double b, double c, double x1_expected, double x2_expected, int nroots_expected) {
    double x1 = 0, x2 = 0;

    int nroots = solve(a, b, c, &x1, &x2);
    if (nroots != nroots_expected || x1 != x1_expected || x2 != x2_expected) {
        printf("error test %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nroots = %d\n"
        "expected x1 = %lg, x2 = %lg, nroots = %d\n",
        test_num, a, b, c, x1, x2, nroots,
        x1_expected, x2_expected, nroots_expected);
    }
}
