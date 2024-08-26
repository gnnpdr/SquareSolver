#include <stdio.h> 

#include "get_coef.h"



/*!
 *\brief moves the position of input of the '\n' or EOF symbol and anylizes buffer
 *\return result of checking the enter 
 */
static Result clean_buffer (void);

/*!
 *\brief analyzes every single coefficient and ask for new enter in case of error
 *\param[in,out] a pointer to the coefficient
 */
static void control_of_input_reload_if_error (double *const a); 

/*!
 *\brief analyzes the coefficient
 *\param[in,out] a pointer to the coefficient
 *\param[in,out] good_enter means is there other symbols after a number
 */
static void check (double *const a, bool *const good_enter);

void getting_coefficients (DataForSolvingEquations* fulldataforsolving)
{
    assert(fulldataforsolving != nullptr); 

    double a = 0, b = 0, c = 0;

    printf("Enter coefficients for solving a equation\n");

    control_of_input_reload_if_error(&a);
    control_of_input_reload_if_error(&b);
    control_of_input_reload_if_error(&c);

    fulldataforsolving->a = a;
    fulldataforsolving->b = b;
    fulldataforsolving->c = c;
}
 
static void control_of_input_reload_if_error (double *const a)
{
    assert(a != nullptr); 

    int cnt = 0;
    bool good_enter = false;

    while (cnt < 3) 
    {
        check(a, &good_enter);
        if (good_enter != true)
            printf("enter again\n");
        else
            break;
    }
}

void check(double *const a, bool *const good_enter)
{
    assert(a != nullptr);
    assert(good_enter != nullptr);

    scanf("%lg", a);
    if (clean_buffer() == OK)
        *good_enter = true;

}


static Result clean_buffer()
{
    int ch = getchar();
    bool symb = true;

    while (ch != '\n' && ch != EOF)
    {
        if (isspace(ch) == false)
        {
            symb = false;
        }
        ch = getchar();
    }

    if (symb == true)
        return OK;
    else
        return WRONG;
}
