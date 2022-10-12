#include <stdio.h>
#include "convolutional_layer.h"
//#include "linearalgebra.h"
/* TODO:
    Linear algebra: 
        (about done) Unit test Convolution, multiplication, and Addition
    Convolutional layer: 
        Kernel, Batch Normalization, Relu, Loss function (gradient descent?)
        feed forward vs backward

    Read inputs:

    Send outputs:

*/
void matrix_convolution_test(int depth, int kernel, int ifmap, int stride)
{
    struct matrix * k = matrix_create(depth, kernel, kernel);
    struct matrix * imap = matrix_create(depth, ifmap, ifmap);
    int ofmap = (ifmap+kernel-1);
    // valid conv = int ofmap = (ifmap-kernel+stride)/stride;
    struct matrix * omap = matrix_create(depth, ofmap, ofmap);
    float kern[9] = {1,0,1,0,1,0,1,0,1};
    float map[16] = {1,2,4,3,2,1,3,5,3,2,1,6,2,3,4,9,};
    for(int d = 0; d < depth; d++)
    {
        for(int kr = 0; kr < kernel*kernel; kr++)
        {
            (*k->value)[kr] = kern[kr%9];
        }
        float * i_ptr =  *imap->value;
        for(int i = 0; i < ifmap*ifmap; i++)
        {
            (*imap->value)[i] = map[i%16];
        }
    }
    matrix_convolution_full(imap, k, omap, stride);
    printf("after convolution:\n");
    for(int d = 0; d < depth; d++)
    {
        for(int r = 0; r < *omap->rows; r++)
        {
            for(int c = 0; c < *omap->columns; c++)
            {
                printf("%f ", (*omap->value)[(r * *(omap->columns))+c]);
            }
            printf("\n");
        }
    }
    matrix_free(ifmap);
    matrix_free(omap);
    matrix_free(k);
}

void matrix_product_test(int depth, int rows, int columns)
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
    matrix_convolution_test(1,3,4,1);
}