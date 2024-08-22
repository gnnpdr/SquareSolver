#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

enum num_of_roots {
    ZERO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS};

enum difference {
    LESS,
    GREATER,
    EQUAL
};

int launch_functions (void);

const int enter (double* a, double* b, double* c);

const int control_of_input_reload_if_error (double* a);
const int checking_symbols (double* a);
int clean_buffer (void);

const int finding_difference_between_doubles ( double a, double b);

int solve (double a, double b, double c, double* x1, double* x2);

int solvation_of_linear_equation (double b, double c, double* x1);
int solvation_of_square_equation (double a, double b, double c, double* x1, double* x2);

const int output (int a, double x1, double x2);

const int unitest (int test_num, double a, double b, double c, double x1_expected, double x2_expected, int nroots_expected);
int launch_tests (void);

const int INF_ROOTS = -1;
const double EPS = 1e-10;

int main()
{

    printf("Enter coefficients for solving a equation\n");

    double a = 0, b = 0, c = 0;
    const double *pa = &a, *pb = &b, *pc = &c;

    enter(&a, &b, &c);

    double x1 = 0, x2 = 0;
    int nroots = solve(a, b, c, &x1, &x2);

    output (nroots, x1, x2);

    launch_tests ();

    return 0;
}

int solve(double a, double b, double c, double* x1, double* x2){

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x1 != nullptr);
    assert(x2 != nullptr);
    assert(x1 != x2);

    const double *pa = &a, *pb = &b, *pc = &c;


    if (finding_difference_between_doubles(a, 0) == EQUAL)     
            solvation_of_linear_equation (b, c, x1);

    else
            solvation_of_square_equation (a, b, c, x1, x2);


}

const int control_of_input_reload_if_error (double* a){

    assert(a != nullptr);

    while (checking_symbols (a) != 0)
    {
    printf("enter new\n");
    }
    return 0;
}

const int checking_symbols(double* a){

    assert(a != nullptr);

    scanf("%lg", a);
    int ch = 0;

    while (ch != '\n' || ch != EOF)
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

const int enter (double* a, double* b, double* c){

    assert(a != nullptr);
    assert(b != nullptr);
    assert(c != nullptr);

    control_of_input_reload_if_error(a);
    control_of_input_reload_if_error(b);
    control_of_input_reload_if_error(c);

    return 0;
}

const int output (int nroots, double x1, double x2){

    assert(isfinite(nroots));
    assert(isfinite(x1));
    assert(isfinite(x2));


    switch (nroots){

        case ZERO_ROOTS: printf ("no roots\n");
                break;
        case ONE_ROOT: printf ("x = %lg\n", x1);
                break;
        case TWO_ROOTS: printf ("x1 = %lg, x2 = %lg\n", x1, x2);
                break;
        case INF_ROOTS: printf("any number\n");
                break;
        default: printf("error\n");
                return 1;
    }
    return 0;
}

int solvation_of_linear_equation (double b, double c, double* x1){

    assert(isfinite(b));
    assert(isfinite(c));

    assert(x1 != nullptr);

    const double *pb = &b, *pc = &c;

    if (finding_difference_between_doubles(b, 0) == EQUAL)
            return (finding_difference_between_doubles(c, 0) == EQUAL)? INF_ROOTS: ZERO_ROOTS;

        else{
            *x1 = -c/b;
            return ONE_ROOT;
        }
}

int solvation_of_square_equation (double a, double b, double c, double* x1, double* x2){

    assert(x1 != nullptr);
    assert(x2 != nullptr);
    assert(x1 != x2);

    const double *pa = &a, *pb = &b, *pc = &c;

    double diskr = b*b - 4*a*c;

        if (finding_difference_between_doubles(diskr, 0) == EQUAL){
            *x1 = *x2 = -b/ (2*a);

            return ONE_ROOT;
        }
        else if (finding_difference_between_doubles(diskr, 0) == LESS) {
            return ZERO_ROOTS;
        }
        else{
            *x1 = (-b + sqrt(diskr))/(2*a);
            *x2 = (-b - sqrt(diskr))/(2*a);
            return TWO_ROOTS;
        }
}

const int unitest (int test_num, double a, double b, double c, double x1_expected, double x2_expected, int nroots_expected) {

    assert(isfinite(test_num));
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(isfinite(x1_expected));
    assert(isfinite(x2_expected));
    assert(isfinite(nroots_expected));

    double x1 = 0, x2 = 0;

    int nroots = solve(a, b, c, &x1, &x2);
    if (nroots != nroots_expected || x1 != x1_expected || x2 != x2_expected) {
        printf("error test %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nroots = %d\n"
        "expected x1 = %lg, x2 = %lg, nroots = %d\n",
        test_num, a, b, c, x1, x2, nroots,
        x1_expected, x2_expected, nroots_expected);
    }
}

int launch_functions () {


}

int launch_tests () {

    int start = 0, rows = 0, cols = 0;
    double tests[rows][cols] = {{1, 1, -5, 6, 3, 2, 2},
                                {2, 1, -4, 4, 2, 2, 1},
                                {3, 1, 2, 4, 0, 0, 0},
                                {4, 1, 1.5, 0.5, -0.5, -1, 2},
                                {5, 0, 0, 0 ,0, 0, -1}};
    while ( start++ < rows) {
          unitest(tests[start]);
    }

    return 0;
}

const int finding_difference_between_doubles ( double a, double b) {

    assert(isfinite(a));
    assert(isfinite(b));
    
    double dif = b-a;

    if (dif < 0 & abs(dif) > EPS)
        return LESS;

    else if (dif > 0 & abs(dif) > EPS)
        return GREATER;

    else
        return EQUAL;
}