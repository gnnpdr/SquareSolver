/*!
 *\file
 *\brief This program solves a square equation aX^2 + bX + c = 0
 */

#include <stdio.h> 

#include "DataForSolving.h"
#include "get_coef.h"
#include "solve.h"
#include "output.h"
#include "tests.h"

#define TEST


int main() 
{ 
    DataForSolvingEquations fulldataforsolving = {};

    initialising_structure (&fulldataforsolving);

    getting_coefficients(&fulldataforsolving); 
 
    solve_the_equation(&fulldataforsolving); 
 
    output_the_answer (&fulldataforsolving); 
 
    #ifdef TEST
    launch_tests (); 
    #endif
 
    return 0; 
} 
