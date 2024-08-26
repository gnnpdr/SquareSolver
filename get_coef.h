/*!
 *\file
 *\brief contains functions declaration, that need for test mode
 */

#ifndef COEFS_H
#define COEFS_H

#include <assert.h> 
#include <ctype.h>
#include "DataForSolving.h"

/*!
 *\brief enum describes the result of checking what is sbmitted for input
 */
enum Result
{
    OK,     ///< user has entered something that can be used to solve
    WRONG   ///< there is a problem in users enter
};


/*!
 *\brief fulls out the struct by coefficients
 *\param[in,out] fulldataforsolving structure includes all information for solving
 */
void getting_coefficients (DataForSolvingEquations* fulldataforsolving); 

#endif //COEFS_H
