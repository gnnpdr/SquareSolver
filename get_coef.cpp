#include <stdio.h> 

#include "get_coef.h"



/*!
 *\brief moves the position of input of the '\n' or EOF symbol and anylizes buffer 
 */
static void clean_buffer (void);

/*!
 *\brief analyzes every single coefficient and ask for new enter in case of error
 *\param[in,out] a pointer to the coefficient
 */
static void control_of_input_reload_if_error (double *const a); 

/*!
 *\brief analyzes the coefficient
 *\param[in,out] a pointer to the coefficient
 *\param[in,out] good_enter means is there other symbols after a number
 *\return result of checking the enter
 */
static Result check (double *const a, bool *const good_enter);

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

    while (there_is_symbol != true && cnt < 3) 
    {
        printf("enter again\n");
        check(&a, &good_enter);
    }
}

void check(double *const a, bool *const good_enter)
{
    assert(a != nullptr);
    assert(good_enter != nullptr);

    scanf("%lg", a);
    if (clean_buffer() == OK)
        good_enter = true;

}


static Result clean_buffer()
{
    int ch = getchar();
    int symb_cnt = 0;

    while (ch != '\n' && ch != EOF)
    {
        printf("%c\n", ch);

        if (isspace(ch) == false)
        {
            symb_cnt++;
        }
        ch = getchar();
    }

    if (symb_cnt == 0)
        return OK;
    else
        return WRONG;
}
