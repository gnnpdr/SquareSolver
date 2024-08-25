#include <stdio.h>
#include "output.h"


/*!
 *\brief controls x1 is greater than x2
 *\param[in] x1 pointer to the first root of equation
 *\param[in] x2 pointer to the second root of equation
 */
static void getting_greater_root (double* x1, double* x2);

/*!
 *\brief changes the roots if necessary
 *\param[in,out] x1 pointer to the first root of equation
 *\param[in,out] x2 pointer to the second root of equation
 */
static void swap_roots (double* x1, double* x2); 

void output_the_answer (DataForSolvingEquations* fulldataforsolving)
{
    assert(fulldataforsolving != nullptr);  
 
    double x1 = 0, x2 = 0;

    x1 = fulldataforsolving->x1;
    x2 = fulldataforsolving->x2;

 
    switch (fulldataforsolving->nroots)
    { 
        case ZERO_ROOTS:    printf ("no roots\n"); 
                            break;

        case ONE_ROOT:      printf ("x = %lg\n", x1); 
                            break; 

        case TWO_ROOTS:     getting_greater_root (&fulldataforsolving->x1, &fulldataforsolving->x2); 
                            printf ("x1 = %lg, x2 = %lg\n", x1, x2); 
                            break;

        case INF_ROOTS:     printf("any number\n"); 
                            break;

        default:            printf("error\n");

    } 
} 

void getting_greater_root (double* x1, double* x2) 
{ 
 
    assert(x1 != nullptr); 
    assert(x2 != nullptr); 
    assert(x1 != x2); 
    
    if (comparing_doubles(*x1, *x2) == LESS) 
    { 
        swap_roots(x1, x2); 
    } 
}

void swap_roots (double* x1, double* x2) 
{ 

    assert (x1 != nullptr);
    assert (x2 != nullptr);

    double temp = 0; 
 
    temp = *x1; 
    *x1 = *x2;    
    *x2 = temp; 

}
