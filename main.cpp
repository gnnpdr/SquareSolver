#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#define TEST

struct DataForSolvingEquetions {
    int testnum;

    double a;
    double b;
    double c;

    double x1;
    double x2;

    int nroots;
    };

struct DataForChecking {
    int testnum;

    double a;
    double b;
    double c;

    double x1_exp;
    double x2_exp;

    int nroots;

};

enum NumOfRoots {
    ZERO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INF_ROOTS = -1,
    ERROR};

enum Difference {
    LESS,
    GREATER,
    EQUAL
};

int getting_coefficients (DataForSolvingEquetions* fulldataforsolving);

int control_of_input_reload_if_error (double *const a);
bool checking_symbols (double *const a); 
int clean_buffer (void);

Difference comparing_doubles (const double a, const double b);

int solvation_of_equation (DataForSolvingEquetions* fulldataforsolving);

int solvation_of_linear_equation (DataForSolvingEquetions* fulldataforsolving);
int solvation_of_square_equation (DataForSolvingEquetions* fulldataforsolving);

int getting_greater_root (double* x1, double* x2);

int getting_the_answer (DataForSolvingEquetions* fulldataforsolving);

int initialising_structure(DataForSolvingEquetions* fulldataforsolving);
int unittest (DataForSolvingEquetions* fulldataforsolving);
int launch_tests ();
int swap_roots (double* x1, double* x2);

const double EPS             = 1e-10;
const int    AMOUNT_OF_TESTS =     5;

int main()
{
    DataForSolvingEquetions fulldataforsolving = {};

    initialising_structure(&fulldataforsolving);

    getting_coefficients(&fulldataforsolving); 

    solvation_of_equation(&fulldataforsolving);

    getting_the_answer (&fulldataforsolving);

    #ifdef TEST
    launch_tests ();
    #endif

    return 0;
}

int solvation_of_equation(DataForSolvingEquetions* fulldataforsolving){

    assert(fulldataforsolving != nullptr);


    if (comparing_doubles(fulldataforsolving->a, 0) == EQUAL)     
            solvation_of_linear_equation (fulldataforsolving);

    else
            solvation_of_square_equation (fulldataforsolving);


}

int control_of_input_reload_if_error (double *const a){

    assert(a != nullptr);

    while (checking_symbols (a) == true)
    {
        printf("enter new\n");
    }
    return 0;
}

bool checking_symbols(double *const a){

    assert(a != nullptr);

    bool symbol_is_alpfa = false;

    printf("scanf output: %d\n", scanf("%lg", a));

    printf("-> %lg\n", *a);

    int ch = 0;

    while (ch != '\n' && ch != EOF)
    {
        // printf("%c", ch);
        // printf("%c", ch);
        // if (isalpha(ch))
        // {
        //     symbol_is_alpfa == false;
        //     return symbol_is_alpfa;
        // }
        ch = getchar();

    }
    printf("true\n");
    return symbol_is_alpfa;
}

int clean_buffer(){
    int ch = 0;
    do { 
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return 0;
}

int getting_coefficients (DataForSolvingEquetions* fulldataforsolving){

    assert(fulldataforsolving != nullptr);

    double a = 0, b = 0, c = 0;

    printf("Enter coefficients for solving a equation\n");

    control_of_input_reload_if_error(&a);
    control_of_input_reload_if_error(&b);
    control_of_input_reload_if_error(&c);

    printf("%lg %lg %lg", a, b, c);

    fulldataforsolving->a = a;
    fulldataforsolving->b = b;
    fulldataforsolving->c = c;
    
    
    return 0;
}

int getting_the_answer (DataForSolvingEquetions* fulldataforsolving){

    assert(fulldataforsolving != nullptr);

    switch (fulldataforsolving->nroots){

        case ZERO_ROOTS: printf ("no roots\n");
                         break;

        case ONE_ROOT:   printf ("x = %lg\n", fulldataforsolving->x1);
                         break;

        case TWO_ROOTS:  getting_greater_root (&fulldataforsolving->x1, &fulldataforsolving->x2);
                         printf ("x1 = %lg, x2 = %lg\n", fulldataforsolving->x1, fulldataforsolving->x2);
                         break;
        case INF_ROOTS:  printf("any number\n");
                         break;
        default:         printf("error\n");
    }
    return 0;
}

int solvation_of_linear_equation (DataForSolvingEquetions* fulldataforsolving){

    assert(fulldataforsolving != nullptr);

    int nroots = 0;

    if (comparing_doubles(fulldataforsolving->b, 0) == EQUAL)
            nroots = (comparing_doubles(fulldataforsolving->c, 0) == EQUAL)? INF_ROOTS: ZERO_ROOTS;

        else{
            double x1 = -fulldataforsolving->c / fulldataforsolving->b;
            fulldataforsolving->x1 = x1;

            nroots = ONE_ROOT;
        }
    fulldataforsolving->nroots = nroots;    
    return 0;
}

int solvation_of_square_equation (DataForSolvingEquetions* fulldataforsolving){

    assert(fulldataforsolving != nullptr);

    int nroots = 0;

    double diskr = fulldataforsolving->b*fulldataforsolving->b - 4*fulldataforsolving->a*fulldataforsolving->c;
    
    double x1 = 0, x2 = 0;

        if (comparing_doubles(diskr, 0) == EQUAL){
            
            x1 = x2 = -fulldataforsolving->b / (2*fulldataforsolving->a);

            fulldataforsolving->x1 = x1;
            fulldataforsolving->x2 = x2;

            nroots = ONE_ROOT;
        }
        else if (comparing_doubles(diskr, 0) == LESS) {
            nroots = ZERO_ROOTS;
        }
        else{
            x1 = (-fulldataforsolving->b + sqrt(diskr))/(2*fulldataforsolving->a);
            x2 = (-fulldataforsolving->b - sqrt(diskr))/(2*fulldataforsolving->a);

            fulldataforsolving->x1 = x1;
            fulldataforsolving->x2 = x2;

            nroots = TWO_ROOTS;
        }

    return 0;
}

int unittest (DataForSolvingEquetions* fulldataforsolving, DataForChecking* test) {

    assert(fulldataforsolving != nullptr);
    assert(test != nullptr);

    DataForChecking test = {};

    if (test->nroots != fulldataforsolving->nroots || test->x1_exp != fulldataforsolving->x1 || test->x2_exp != fulldataforsolving->x2) {
        printf("error test %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nroots = %d\n"
        "expected x1 = %lg, x2 = %lg, nroots = %d\n",
        fulldataforsolving->testnum, fulldataforsolving->a, fulldataforsolving->b, fulldataforsolving->c, fulldataforsolving->x1, fulldataforsolving->x2, fulldataforsolving->nroots,
        test->x1_exp, test->x2_exp, test->nroots);
    }
}

int launch_tests () {

    DataForChecking ch_test1 = {.testnum = 1, .a = 1,  .b =  -5, .c =   6, .x1_exp =    3, .x2_exp =  2, .nroots =  2};
    DataForChecking ch_test2 = {.testnum = 2, .a = 1,  .b =  -4, .c =   4, .x1_exp =    2, .x2_exp =  2, .nroots =  1};
    DataForChecking ch_test3 = {.testnum = 3, .a = 1,  .b =   2, .c =   4, .x1_exp =    0, .x2_exp =  0, .nroots =  0};
    DataForChecking ch_test4 = {.testnum = 4, .a = 1,  .b = 1.5, .c = 0.5, .x1_exp = -0.5, .x2_exp = -1, .nroots =  2};
    DataForChecking ch_test5 = {.testnum = 5, .a = 0,  .b =   0, .c =   0, .x1_exp =    0, .x2_exp =  0, .nroots = -1};
  
    DataForSolvingEquetions test1 = {.testnum = 1, .a = 1,  .b =  -5, .c =   6, .nroots =  2};
    DataForSolvingEquetions test2 = {.testnum = 2, .a = 1,  .b =  -4, .c =   4, .nroots =  1};
    DataForSolvingEquetions test3 = {.testnum = 3, .a = 1,  .b =   2, .c =   4, .nroots =  0};
    DataForSolvingEquetions test4 = {.testnum = 4, .a = 1,  .b = 1.5, .c = 0.5, .nroots =  2};
    DataForSolvingEquetions test5 = {.testnum = 5, .a = 0,  .b =   0, .c =   0, .nroots = -1};
    
    unittest(&test1, &ch_test1);
    unittest(&test2, &ch_test2);
    unittest(&test3, &ch_test3);
    unittest(&test4, &ch_test4);
    unittest(&test5, &ch_test5);

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
        swap_roots(x1, x2);
    }

    return 0;
}

int initialising_structure (DataForSolvingEquetions* fulldataforsolving) {
    
    fulldataforsolving->a  = 1;
    fulldataforsolving->b  = NAN;
    fulldataforsolving->c  = NAN;
    fulldataforsolving->x1 = NAN;
    fulldataforsolving->x2 = NAN;
    
    printf("%lg", fulldataforsolving->a);
    return 0;

}

int swap_roots (double* x1, double* x2) {
    double temp = 0;

    temp = *x1;
    *x1 = *x2;   
    *x2 = temp;

    return 0;
}