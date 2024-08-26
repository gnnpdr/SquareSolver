
#include <stdio.h> 
#include "data_for_solving.h"

void initialising_structure (DataForSolvingEquations* fulldataforsolving) 
{ 
    fulldataforsolving->a      = NAN;
    fulldataforsolving->b      = NAN;
    fulldataforsolving->c      = NAN;

    fulldataforsolving->x1     = NAN;
    fulldataforsolving->x2     = NAN;
    
    fulldataforsolving->nroots = NAN;
}
