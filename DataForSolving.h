
#ifndef INIT_H
#define INIT_H

#include <math.h> 

/*!
 *\brief includes all data needed to solve the equation
 */
struct DataForSolvingEquations 
{
    double a;     ///< a   a-coefficient
    double b;     ///< b   b-coefficient
    double c;     ///< c   c-coefficient

    double x1;    ///< x1   first root
    double x2;    ///< x2   second root

    int nroots;   ///< nroots   pointer to the amount of roots
};

/*!
 * \brief fulls out the struct by NANs
 */ 
void initialising_structure(DataForSolvingEquations* fulldataforsolving);

#endif //INIT_H
