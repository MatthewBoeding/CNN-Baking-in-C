/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* Linear Algebra Library
* Written by: Matthew Boeding
* It has most certainly been done better, but this my attempt into the fray! My personal opinion is that
* a strong foundation is required for greater understanding. Hopefully this will be useful for future
* projects, and I come out the other side with a better understanding of machine learning.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "linearalgebra.h"

/**
 * @brief Create a matrix struct with uninitialized values
 * 
 * @param rows -number of rows in the matrix
 * @param columns - number of columns in the matrix
 * @return struct matrix* 
 */
struct matrix * matrix_create(int depth, int rows, int columns)
{
    struct matrix * result = malloc(sizeof(struct matrix));
    double * contents = malloc((rows*columns)*sizeof(double));
    double ** con_ptr = malloc(sizeof(double *));
    *con_ptr = contents;
    int * dims = malloc(3*sizeof(int));
    dims[0] = columns;
    dims[1] = rows;
    dims[2] = depth;

    result->columns = dims;
    dims++;
    result->rows = dims;
    dims++;
    result->depth = dims;
    result->value = con_ptr;
    return result;
}

/**
 * @brief A simple matrix transpose
 *      updates the row and column value as wel
 * @param mat 
 */
void matrix_transpose(struct matrix * mat)
{
    int rows = *mat->rows;
    int cols = *mat->columns;
    int depth = *mat->depth;
    *mat->rows = cols;
    *mat->columns = rows;
    double temp;
    double * val = *mat->value;
    for(int d = 0; d < depth; d++)
    {
        for(int i = 0; i < rows; i++)
        {   
            for(int j = 0; j < i; j++)
            {
                temp = val[i*cols+j];
                val[i*cols+j] = val[j*cols+i];
                val[j*cols+i] = temp;
            }
        }
        val += (rows*cols);
    }   
}

void matrix_dotproduct(struct matrix * mat1, struct matrix * mat2, struct matrix * result)
{
    *result->rows = *mat1->rows;
    *result->columns = *mat2->columns;
    int rows = *result->rows;
    int cols = *result->columns;
    double * val_ptr =  *result->value;
    double * mat1_ptr = *(*mat1).value;
    double * mat2_ptr = *mat2->value;
    if(*mat1->columns == *mat2->rows && *mat1->depth == *mat2->depth)
    {
        for(int d = 0; d < *mat1->depth; d++)
        {
            for(int i = 0; i < *mat1->rows; i++)
            {
                for(int j = 0; j < *mat2->columns; j++)
                {
                    val_ptr[i*rows+j] = 0;
                    for(int k = 0; k < *mat2->rows; k++)
                    {
                        val_ptr[i*rows+j] += mat1_ptr[i*rows+k] * mat2_ptr[k*cols+j];
                    }
                }
            }
            val_ptr += (*result->rows)*(*result->columns);
        }
    }
    else
    {
        printf("Dimension Error! Matrix 1 colums: %d, while Matrix 2 rows: %d", *mat1->columns, *mat2->rows);
    }
}

void matrix_free(struct matrix * mat)
{
    double * ptr_val = *mat->value;
    free(ptr_val);
    free(mat->value);
    free(mat->columns);
    free(mat->rows);
    free(mat->depth);
    return;

}
void matrix_convolution(struct matrix * mat1, struct matrix * mat2, struct matrix * result)
{


}

void matrix_addition(struct matrix * mat1, struct matrix * mat2, struct matrix * result)
{

}

/* Perhaps for later
void matrix_crossproduct(struct matrix * mat1, struct matrix * mat2, struct matrix * result)
{


}
*/