#include <stdio.h> 
#include "solve.h"


/*!
 *\brief solves equation in case it is linear 
 *\param[in,out] fulldataforsolving structure includes all information for solving
 */
static void solve_of_linear_equation (DataForSolvingEquations* fulldataforsolving); 

/*!
 *\brief solves equation in case it is square 
 *\param[in,out] fulldataforsolving structure includes all information for solving
 */
static void solve_of_square_equation (DataForSolvingEquations* fulldataforsolving);

static const double EPS = 1e-10; ///< acceptable difference of doubles

void solve_the_equation (DataForSolvingEquations* fulldataforsolving)
{
    assert(fulldataforsolving != nullptr); 

    double a = 0;

    a = fulldataforsolving->a;
    
    if (comparing_doubles(a, 0) == EQUAL)      
            solve_of_linear_equation (fulldataforsolving); 
 
    else 
            solve_of_square_equation (fulldataforsolving); 
 
 
} 
 
static void solve_of_linear_equation (DataForSolvingEquations* fulldataforsolving)
{
    assert(fulldataforsolving != nullptr);  
 
    double b = 0, c = 0;

    b = fulldataforsolving->a;
    c = fulldataforsolving->b;

    int nroots = 0;

    if (comparing_doubles(b, 0) == EQUAL)

            nroots = (comparing_doubles(c, 0) == EQUAL) ? INF_ROOTS : ZERO_ROOTS; 
 
    else
    { 
        double x1 = 0;
        x1 = -c / b;

        fulldataforsolving->x1 = x1;

        nroots = ONE_ROOT; 
    } 

    fulldataforsolving->nroots = nroots;
} 

static void solve_of_square_equation (DataForSolvingEquations* fulldataforsolving)
{

    assert(fulldataforsolving != nullptr);

    int nroots = 0;

    double a = 0, b = 0, c = 0;

    a = fulldataforsolving->a;
    b = fulldataforsolving->b;
    c = fulldataforsolving->c;

    double diskr = b*b - 4*a*c;
    
    double x1 = 0, x2 = 0;

    if (comparing_doubles(diskr, 0) == EQUAL)
    {
        x1 = x2 = -b / (2*a);

        fulldataforsolving->x1 = x1;
        fulldataforsolving->x2 = x2;

        nroots = ONE_ROOT;
    }
    else if (comparing_doubles(diskr, 0) == LESS) 
    {
        nroots = ZERO_ROOTS;
    }
    else
    {
        double discr_sq = sqrt(diskr);
        x1 = (-b + discr_sq)/(2*a);
        x2 = (-b - discr_sq)/(2*a);

        fulldataforsolving->x1 = x1;
        fulldataforsolving->x2 = x2;

        nroots = TWO_ROOTS;
    }
    fulldataforsolving->nroots = nroots;

} 

ComparisonResult comparing_doubles (const double a, const double b) { 
 
    assert(isfinite(a)); 
    assert(isfinite(b)); 
     
    double dif = a - b; 
    if (fabs(dif) > EPS) 
    { 
        if (dif < 0)  
            return LESS; 
        else 
            return GREATER; 
    } 
    else  
        return EQUAL;  
} 
