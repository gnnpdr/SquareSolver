/*!
 *\file
 *\brief contains functions declaration, that need for test mode
 */

#ifndef SOLVE_H
#define SOLVE_H

#include "get_coef.h"

/*!
 *\brief enum describes amount of roots of the equation
 */
enum NumOfRoots 
{ 
    ZERO_ROOTS,    ///< equation does not have roots
    ONE_ROOT,      ///< equation has one root 
    TWO_ROOTS,     ///< equation has two root
    INF_ROOTS = -1 ///< equation has infinite number of roots
}; 
 
 /*!
  *\brief enum describes difference between two doubles
  */
enum ComparisonResult 
{ 
    LESS,    ///< first double is less than the second
    GREATER, ///< first double is greater than second
    EQUAL    ///< first and second double are equal
}; 

/*!
 *\brief fulls out the struct by roots and number of roots
 *\param[in,out] fulldataforsolving structure includes all information for solving
 */
void solve_the_equation (DataForSolvingEquations* fulldataforsolving); 

/*!
 *\brief compares doubles 
 *\param[in] a first double for comparing
 *\param[in] b second double for comparing
 *\return comparison result
 */
ComparisonResult comparing_doubles (const double a, const double b); 

#endif //SOLVE_H
