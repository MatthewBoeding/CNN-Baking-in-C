#include <stdio.h>
#include "linearalgebra.h"
/* TODO:
    Linear algebra: 
    Unit test Convolution, multiplication, and Addition
    Convolutional layer: 
        Kernel, Batch Normalization, Relu, Loss function (gradient descent?)
        feed forward vs backward
    Read inputs:

    Send outputs:

*/

void matrix_test(depth, rows, columns)
{
    struct matrix * mat = matrix_create(depth, rows, columns);
    struct matrix * mat2 = matrix_create(depth, rows, columns);
    struct matrix * result = matrix_create(depth, rows, columns);

    float * current = *mat->value;
    float * current2 = *mat2->value;
    int value_count = rows * columns;
    float inc_value = 1.1;
    int i = 0;
    while(i < (depth*rows*columns))
    {
        (*current) = inc_value;
        (*current2) = inc_value;
        inc_value += 1.1;
        current += 1;
        current2 += 1;
        i++;
    }

    current = *mat->value;
    printf("Before Transpose:\n");
    for(int d = 0; d < depth; d++)
    {
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
        printf("\n");
    }
    *mat->value = current - (rows * columns);
    printf("After Transpose:\n");
    matrix_transpose(mat);
    current = *mat->value;
    for(int d = 0; d < depth; d++)
    {
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
        printf("\n");
    }
    matrix_dotproduct(mat2, mat, result);
    printf("Product Result:\n");
    current = *result->value;
    for(int d = 0; d < depth; d++)
    {
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
        printf("\n");
    }
    matrix_free(mat);
    matrix_free(mat2);
    matrix_free(result);
}

int main()
{
    int rows = 3;
    int columns = 3;
    int depth = 1;
    matrix_test(depth, rows, columns);
    matrix_test(1,2,2);
    matrix_test(1,4,4);
}