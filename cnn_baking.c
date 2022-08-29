#include <stdio.h>
#include "linearalgebra.h"


int main()
{
    int rows = 3;
    int columns = 3;
    struct matrix * mat = matrix_create(rows, columns);
    double * current = *mat->value;
    int value_count = rows * columns;
    double inc_value = 1.1;
    int i = 0;
    while(i < 9)
    {
        *current = inc_value;
        inc_value += 1.1;
        current++;
        i++;
    }

    current = *mat->value;
    printf("Before Transpose:\n");
    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < columns; c++)
        {
            printf("%lf     ", *current);
            fflush(stdout);
            current++;
        }
        printf("\n");
    }
    *mat->value = current - (rows * columns);
    printf("After Transpose:\n");
    matrix_transpose(mat);
    current = *mat->value;
    for(int r = 0; r < rows; r++)
    {
        for(int c = 0; c < columns; c++)
        {
            printf("%lf     ", *current);
            fflush(stdout);
            current++;
        }
        printf("\n");
    }
    matrix_free(mat);
}