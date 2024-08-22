#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define TEST

struct DataForChecking {
            int testnum;

            double a;
            double b;
            double c;

            double x1_expected;
            double x2_expected;

            int nroots_expected;
    };

struct DataForSolvingEquetions {
            double a;
            double b;
            double c;

            double* x1;
            double* x2;
};

enum NumOfRoots {
    INF_ROOTS,
    ZERO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    ERROR};

enum Difference {
    LESS,
    GREATER,
    EQUAL
};

int getting_coefficients (double *const a, double *const b, double *const c);

int control_of_input_reload_if_error (double *const a);
bool checking_symbols (double *const a); 
int clean_buffer (void);

Difference comparing_doubles (const double a, const double b);

int solvation_of_equation (const double a, const double b, const double c, double *const x1, double *const x2);

int solvation_of_linear_equation (const double b, const double c, double *const x1);
NumOfRoots solvation_of_square_equation (const double a, const double b, const double c, double *const x1, double *const x2);

int getting_greater_root (double* x1, double* x2);

NumOfRoots getting_the_answer (const int a, double x1, double x2);

int filling_out_the_structure_tests(struct Tests);
int unittest (struct DataForChecking);
int launch_tests ();

const int INF_ROOTS = -1;
const double EPS = 1e-10;
const int AMOUNT_OF_TESTS = 5;

int main()
{

    printf("Enter coefficients for solving a equation\n");

    double a = 0, b = 0, c = 0;
    

    getting_coefficients(&a, &b, &c); 

    double x1 = 0, x2 = 0;
    int nroots = solvation_of_equation(a, b, c, &x1, &x2);

    getting_the_answer (nroots, x1, x2);

    struct DataForSolvingEquetions fulldataforsolving;

    filling_out_the_structure_tests(fulldataforsolving);


    launch_tests ();

    return 0;
}

int solvation_of_equation(const double a, const double b, const double c, double *const x1, double *const x2){

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x1 != nullptr);
    assert(x2 != nullptr);
    assert(x1 != x2);

    if (comparing_doubles(a, 0) == EQUAL)     
            solvation_of_linear_equation (b, c, x1);

    else
            solvation_of_square_equation (a, b, c, x1, x2);


}

int control_of_input_reload_if_error (double *const a){

    assert(a != nullptr);

    while (checking_symbols (a) != true)
    {
    printf("enter new\n");
    }
    return 0;
}

bool checking_symbols(double *const a){

    assert(a != nullptr);

    bool symbol_is_alpfa = true;

    scanf("%lg", a);
    int ch = 0;

    while (ch != '\n' || ch != EOF)
    {
        ch = getchar();
        if (isalpha(ch))
        {
            symbol_is_alpfa == false;
            return symbol_is_alpfa;
        }

    }
    return symbol_is_alpfa;
}

int clean_buffer(){
    int ch = 0;
    do { 
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return 0;
}

int getting_coefficients (double *const a, double *const b, double *const c){

    assert(a != nullptr);
    assert(b != nullptr);
    assert(c != nullptr);

    control_of_input_reload_if_error(a);
    control_of_input_reload_if_error(b);
    control_of_input_reload_if_error(c);

    return 0;
}

NumOfRoots getting_the_answer (const int nroots, double x1, double x2){

    assert(isfinite(nroots));
    assert(isfinite(x1));
    assert(isfinite(x2));


    switch (nroots){

        case ZERO_ROOTS: printf ("no roots\n");
                         break;

        case ONE_ROOT: printf ("x = %lg\n", x1);
                       break;
        case TWO_ROOTS:

            getting_greater_root (&x1, &x2);

            printf ("x1 = %lg, x2 = %lg\n", x1, x2);
            break;
        case INF_ROOTS: printf("any number\n");
                        break;
        default: printf("error\n");
                 return ERROR;
    }
}

int solvation_of_linear_equation (const double b, const double c, double *const x1){

    assert(isfinite(b));
    assert(isfinite(c));

    assert(x1 != nullptr);

    if (comparing_doubles(b, 0) == EQUAL)
            return (comparing_doubles(c, 0) == EQUAL)? INF_ROOTS: ZERO_ROOTS;

        else{
            *x1 = -c / b;
            return ONE_ROOT;
        }
}

NumOfRoots solvation_of_square_equation (const double a, const double b, const double c, double *const x1, double *const x2){

    assert(x1 != nullptr);
    assert(x2 != nullptr);
    assert(x1 != x2);

    double diskr = b*b - 4*a*c;

        if (comparing_doubles(diskr, 0) == EQUAL){
            *x1 = *x2 = -b / (2*a);

            return ONE_ROOT;
        }
        else if (comparing_doubles(diskr, 0) == LESS) {
            return ZERO_ROOTS;
        }
        else{
            *x1 = (-b + sqrt(diskr))/(2*a);
            *x2 = (-b - sqrt(diskr))/(2*a);
            return TWO_ROOTS;
        }
}

int unittest (DataForChecking* test) {


    double x1 = 0, x2 = 0;

    int nroots = solvation_of_equation(test->a, test->b, test->c, &x1, &x2);
    if (nroots != test->nroots_expected || x1 != test->x1_expected || x2 != test->x2_expected) {
        printf("error test %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nroots = %d\n"
        "expected x1 = %lg, x2 = %lg, nroots = %d\n",
        test->testnum, test->a, test->b, test->c, x1, x2, nroots,
        test->x1_expected, test->x2_expected, test->nroots_expected);
    }
}

int launch_tests () {

    #ifdef TEST
    DataForChecking test1 = {.testnum = 1, .a = 1,  .b =  -5, .c =   6, .x1_expected =    3, .x2_expected =  2, .nroots_expected =  2};
    DataForChecking test2 = {.testnum = 2, .a = 1,  .b =  -4, .c =   4, .x1_expected =    2, .x2_expected =  2, .nroots_expected =  1};
    DataForChecking test3 = {.testnum = 3, .a = 1,  .b =   2, .c =   4, .x1_expected =    0, .x2_expected =  0, .nroots_expected =  0};
    DataForChecking test4 = {.testnum = 4, .a = 1,  .b = 1.5, .c = 0.5, .x1_expected = -0.5, .x2_expected = -1, .nroots_expected =  2};
    DataForChecking test5 = {.testnum = 5, .a = 0,  .b =   0, .c =   0, .x1_expected =    0, .x2_expected =  0, .nroots_expected = -1};
    #endif
    
    unittest(test1);
    unittest(test2);
    unittest(test3);
    unittest(test4);
    unittest(test5);

    return 0;
}

Difference comparing_doubles (const double a, const double b) {

    assert(isfinite(a));
    assert(isfinite(b));
    
    double comp_res = b-a;
    if (fabs(comp_res) > EPS) {
            if (comp_res < 0) 
                return LESS;
            else
                return GREATER;
    }
    else 
        return EQUAL; 
}

int getting_greater_root (double* x1, double* x2) {

    assert(x1 != nullptr);
    assert(x2 != nullptr);
    assert(x1 != x2);

    if (comparing_doubles(*x1, *x2) == LESS) {
        double temp = 0;

        temp = *x1;
        *x1 = *x2;
        *x2 = temp;
    }

    return 0;
}

int filling_out_the_structure_tests(DataForSolvingEquetions nameofstructure) {
    
    nameofstructure.a = NAN;
    nameofstructure.b = NAN;
    nameofstructure.c = NAN;
    nameofstructure.x1 = ;////это указатели, их никак не заполнять?
    nameofstructure.x2 = ;

    return 0;

}