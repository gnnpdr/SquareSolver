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


enum NumOfRoots {
    ZERO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INF_ROOTS = -1,
    ERROR};

enum AnswerTest {
    OK,
    NOTOK,
};

enum ComparisonResult {
    LESS,
    GREATER,
    EQUAL
};

void getting_coefficients (DataForSolvingEquetions* fulldataforsolving);

void control_of_input_reload_if_error (double *const a);
bool checking_symbols (double *const a); 
void clean_buffer (void);

ComparisonResult comparing_doubles (const double a, const double b);

void solution_of_equation (DataForSolvingEquetions* fulldataforsolving);

NumOfRoots solution_of_linear_equation (DataForSolvingEquetions* fulldataforsolving);
NumOfRoots solution_of_square_equation (DataForSolvingEquetions* fulldataforsolving);

void getting_greater_root (double* x1, double* x2);

void getting_the_answer (DataForSolvingEquetions* fulldataforsolving);

void initialising_structure(DataForSolvingEquetions* fulldataforsolving);
void unittest (DataForSolvingEquetions* fulldataforsolving);
void launch_tests ();
void swap_roots (double* x1, double* x2);
AnswerTest checking_test_answer(DataForSolvingEquetions* fulldataforsolving);


const double EPS             = 1e-10;
const int    AMOUNT_OF_TESTS =     5;

int main()
{
    DataForSolvingEquetions fulldataforsolving = {};
    
    initialising_structure(&fulldataforsolving);

    getting_coefficients(&fulldataforsolving); 

    solution_of_equation(&fulldataforsolving);

    getting_the_answer (&fulldataforsolving);

    #ifdef TEST
    launch_tests ();
    #endif

    return 0;
}

void solution_of_equation(DataForSolvingEquetions* fulldataforsolving){

    assert(fulldataforsolving != nullptr);

    assert(fulldataforsolving->a != NAN);
    assert(fulldataforsolving->b != NAN);
    assert(fulldataforsolving->c != NAN);

    if (comparing_doubles(fulldataforsolving->a, 0) == EQUAL)     
            solution_of_linear_equation (fulldataforsolving);

    else
            solution_of_square_equation (fulldataforsolving);

}

void control_of_input_reload_if_error (double *const a){

    int cnt = 0;

    assert(a != nullptr);

    while (scanf("%lg", a) != 1 && cnt != 3)
    {
        cnt++;
        clean_buffer();
        printf("enter new\n");
    }
}

/*bool checking_symbols(double *const a){

    assert(a != nullptr);

    bool symbol_is_alpfa = true;

    

    //printf("-> %lg\n", *a);

    scanf("%lg", a);
    //printf("scanf output: %d\n", scanf("%lg", a));
    int ch = 0;

    while (ch != '\n' && ch != EOF)
    {
        //if (isalpha(ch))
        // {
        //     symbol_is_alpfa == false;
        //     return symbol_is_alpfa;
        //}
        ch = getchar();

    }
    return symbol_is_alpfa;
}*/

void clean_buffer(){
    int ch = 0;
    do { 
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

}

void getting_coefficients (DataForSolvingEquetions* fulldataforsolving){

    assert(fulldataforsolving != nullptr);

    double a = 0, b = 0, c = 0;

    printf("Enter coefficients for solving a equation\n");

    control_of_input_reload_if_error(&a);
    control_of_input_reload_if_error(&b);
    control_of_input_reload_if_error(&c);

    //printf("%lg %lg %lg", a, b, c);

    fulldataforsolving->a = a;
    fulldataforsolving->b = b;
    fulldataforsolving->c = c;
    
}

void getting_the_answer (DataForSolvingEquetions* fulldataforsolving){

    assert(fulldataforsolving != nullptr);
    assert(fulldataforsolving->x1 != NAN);
    assert(fulldataforsolving->x2 != NAN);

    double x1 = 0, x2 = 0;
    fulldataforsolving->x1 = x1;
    fulldataforsolving->x2 = x2;

    switch (fulldataforsolving->nroots){

        case ZERO_ROOTS: printf ("no roots\n");
                         break;

        case ONE_ROOT:   printf ("x = %lg\n", x1);
                         break;

        case TWO_ROOTS:  getting_greater_root (&fulldataforsolving->x1, &fulldataforsolving->x2);
                         printf ("x1 = %lg, x2 = %lg\n", x1, x2);
                         break;

        case INF_ROOTS:  printf("any number\n");
                         break;

        default:         printf("error\n");
    }
}

 NumOfRoots solution_of_linear_equation (DataForSolvingEquetions* fulldataforsolving){

    assert(fulldataforsolving != nullptr);
    assert(fulldataforsolving->x1 != NAN);
    assert(fulldataforsolving->x2 != NAN);

    int nroots = 0;
    double b = 0, c = 0;
    fulldataforsolving->b = b;
    fulldataforsolving->c = c;

    if (comparing_doubles(b, 0) == EQUAL)
            nroots = (comparing_doubles(c, 0) == EQUAL)? INF_ROOTS: ZERO_ROOTS;

        else{
            double x1 = -c / b;
            fulldataforsolving->x1 = x1;

            nroots = ONE_ROOT;
        }
    fulldataforsolving->nroots = nroots;    
}

NumOfRoots solution_of_square_equation (DataForSolvingEquetions* fulldataforsolving){

    assert(fulldataforsolving != nullptr);
    assert(fulldataforsolving->x1 != NAN);
    assert(fulldataforsolving->x2 != NAN);

    int nroots = 0;
    double a = 0, b = 0, c = 0;
    a = fulldataforsolving->a;
    b = fulldataforsolving->b;
    c = fulldataforsolving->c;

    double diskr = b*b - 4*a*c;
    double discr_sq = sqrt(diskr);
    
    double x1 = 0, x2 = 0;

        if (comparing_doubles(diskr, 0) == EQUAL){
            
            x1 = x2 = -b / (2*a);

            fulldataforsolving->x1 = x1;
            fulldataforsolving->x2 = x2;

            nroots = ONE_ROOT;
        }
        else if (comparing_doubles(diskr, 0) == LESS) {
            nroots = ZERO_ROOTS;
        }
        else{
            x1 = (-b + discr_sq)/(2*a);
            x2 = (-b - discr_sq)/(2*a);

            fulldataforsolving->x1 = x1;
            fulldataforsolving->x2 = x2;

            nroots = TWO_ROOTS;
        }

}

void unittest (DataForSolvingEquetions* fulldataforsolving) {

    assert(fulldataforsolving != nullptr);

    double x1_initial = 0, x2_initial = 0, nroots_initial = 0;

    x1_initial = fulldataforsolving->x1;
    x2_initial = fulldataforsolving->x2;
    nroots_initial = fulldataforsolving->nroots;

    solution_of_equation(fulldataforsolving);

    double x1_end = 0, x2_end = 0, nroots_end = 0;

    x1_end = fulldataforsolving->x1;
    x2_end = fulldataforsolving->x2;
    nroots_end = fulldataforsolving->nroots;

    if (x1_initial != x1_end || x2_initial != x2_end || nroots_initial != nroots_end) 
        printf("error test %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nroots = %d\n" 
        "expected x1 = %lg, x2 = %lg, nroots = %d\n", 
        fulldataforsolving->testnum, fulldataforsolving->a, fulldataforsolving->b, fulldataforsolving->c, x1_end, x2_end, nroots_end, 
        x1_initial, x2_initial, nroots_initial); 
    

}

void launch_tests () {

    DataForSolvingEquetions test [AMOUNT_OF_TESTS] = {
    {.testnum = 1, .a = 1,  .b =  -5, .c =   6, .x1 =    3, .x2 =  2, .nroots =  2},
    {.testnum = 2, .a = 1,  .b =  -4, .c =   4, .x1 =    2, .x2 =  2, .nroots =  1},
    {.testnum = 3, .a = 1,  .b =   2, .c =   4, .x1 =    0, .x2 =  0, .nroots =  0},
    {.testnum = 4, .a = 1,  .b = 1.5, .c = 0.5, .x1 = -0.5, .x2 = -1, .nroots =  2},
    {.testnum = 5, .a = 0,  .b =   0, .c =   0, .x1 =    0, .x2 =  0, .nroots = -1},
    };


    for (int i = 0; i < AMOUNT_OF_TESTS; i++){
        unittest(&test[i]);
    }
    
}

ComparisonResult comparing_doubles (const double a, const double b) {

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

void getting_greater_root (double* x1, double* x2) {

    assert(x1 != nullptr);
    assert(x2 != nullptr);
    assert(x1 != x2);

    if (comparing_doubles(*x1, *x2) == LESS) {
        swap_roots(x1, x2);
    }

}

void initialising_structure (DataForSolvingEquetions* fulldataforsolving) { 

    fulldataforsolving->testnum = NAN;

    fulldataforsolving->a  = NAN;
    fulldataforsolving->b  = NAN;
    fulldataforsolving->c  = NAN;

    fulldataforsolving->x1 = NAN;
    fulldataforsolving->x2 = NAN;
    
    fulldataforsolving->nroots = NAN;
}

void swap_roots (double* x1, double* x2) {
    double temp = 0;

    temp = *x1;
    *x1 = *x2;   
    *x2 = temp;

}

