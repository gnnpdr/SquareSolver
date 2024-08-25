#include <stdio.h> 

#include "get_coef.h"

/*!
 *\brief moves the position of input of the '\n' or EOF symbol
 */
static void clean_buffer (void);

/*!
 *\brief analyzes every single coefficient and ask for new enter in case of error
 *\param [in] a pointer to the coefficient
 */
static void control_of_input_reload_if_error (double *const a); 

/*!
 *\brief analyzes if the enter before space is a number 
 *\param [in] a pointer to the coefficient
 */
static Result first_check (double *const a);

/*!
 *\brief analyzes if the enter is a number or a wrong enter or multiple number (it means user did not understand the task) 
 *\param [in] a pointer to the coefficient
 */
static Result sec_check(double* a);


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
 
void control_of_input_reload_if_error (double *const a)
{
    assert(a != nullptr); 

    int cnt = 0;

    while (first_check(&a) != OK && cnt < 3) 
    {
        cnt++;
    }
}

Result first_check(double* a)
{
    assert(a != nullptr); 

    if (scanf("%lg", &a) != 1)
    {
        printf("enter number\n");
        clean_buffer();
        return WRONG;
    }
    else
    {
        return(sec_check(a));
    }
}

Result sec_check(double* a)
{
    assert(a != nullptr); 

    int space_cnt = 0;
    bool alpha = false;
    bool digit = false;
    int ch = getchar();


    while (ch != '\n' && ch != EOF)
    {
        if (isalpha(ch))
        {
            alpha = true;
        }
        else if (isspace(ch))
        {
            space_cnt++;
        }
        else if (isdigit(ch))
        {
            digit = true;
        }
        ch = getchar();
    }

    if (alpha == false)
    {
        if (space_cnt == 2 && digit == true)
        {
            printf("enter coefficients separately\n");
            return WRONG;
        }
        else
        {
            printf("all right\n");
            return OK;
        }
    }
    else
    {
        printf("enter again sec check error\n");
        return WRONG;
    }
}

void clean_buffer()
{
    int ch = 0;
    while (ch != '\n' && ch != EOF)
    {
        ch = getchar();
    }
}
