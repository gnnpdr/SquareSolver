/*!
 *\file
 *\brief This program solves a square equation aX^2 + bX + c = 0
 */

#include <stdio.h> 
#include <string.h>

#include "data_for_solving.h"
#include "get_coef.h"
#include "solve.h"
#include "output.h"
#include "tests.h"

int main(int argc, const char * argv[]) 
{ 
    DataForSolvingEquations fulldataforsolving = {};

    initialising_structure (&fulldataforsolving);

    if (argc == 2) 
    {
        if (strcmp(argv[1], "--test") == 0 || strcmp(argv[1], "-t") == 0) 
        {
            launch_tests (); 
        }
        else if (strcmp(argv[1], "--base") == 0 || strcmp(argv[1], "-b") == 0)
        {

            getting_coefficients(&fulldataforsolving); 
 
            solve_the_equation(&fulldataforsolving); 
 
            output_the_answer (&fulldataforsolving); 
        }
        else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
        {
            printf("usage: *name_of_your_file*.exe [--base] [--test]\n"
                   "use [--test] or [-t] if you want to check the correctness of the program\n"
                   "use [--base] or [-b] if you want to solve a square equation\n");
        }
    }
 
    return 0; 
} 
