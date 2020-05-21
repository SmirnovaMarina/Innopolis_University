#include <stdio.h>
#include <float.h>
#include <limits.h>

int main()
{
    int int_var = INT_MAX;
    float float_var = FLT_MAX;
    double double_var = DBL_MAX;

    printf("INT_MAX = %d\n", int_var);
    printf("sizeof int_var = %d\n", sizeof(int_var));

    printf("FLT_MAX = %f\n", float_var);
    printf("sizeof float_var = %d\n", sizeof(float_var));

    printf("DBL_MAX = %f\n", double_var);
    printf("sizeof double_var = %d\n", sizeof(double_var));


    return 0;
}