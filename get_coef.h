/*!
 *\file
 *\brief contains functions declaration, that need for test mode
 */

#ifndef COEFS_H
#define COEFS_H

#include <assert.h> 
#include "DataForSolving.h"


/*!
 *\brief fulls out the struct by coefficients
 *\param[in,out] fulldataforsolving structure includes all information for solving
 */
void getting_coefficients (DataForSolvingEquations* fulldataforsolving); 

#endif //COEFS_H
