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
struct matrix * matrix_create(int rows, int columns)
{
    struct matrix * result = malloc(sizeof(struct matrix));
    double * contents = malloc((rows*columns)*sizeof(double));
    double ** con_ptr = malloc(sizeof(double *));
    *con_ptr = contents;
    int * dims = malloc(2*sizeof(int));
    dims[0] = columns;
    dims[1] = rows;

    result->columns = dims;
    dims++;
    result->rows = dims;
    result->value = con_ptr;
    return;
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
    *mat->rows = cols;
    *mat->columns = rows;
    double temp;
    double * val = *mat->value;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < i; j++)
        {
            temp = val[i*cols+j];
            val[i*cols+j] = val[j*cols+i];
            val[j*cols+i] = temp;
        }
    }
}

void matrix_dotproduct(struct matrix * mat1, struct matrix * mat2, struct matrix * result)
{
    *result->rows = *mat1->rows;
    *result->columns = *mat2->columns;

    if(*mat1->columns == *mat2->rows)
    {
        for(int i = 0; i < *mat1->rows; i++)
        {
            for(int j = 0; j < *mat2->columns; j++)
            {
                result->value[i][j] = 0;
                for(int k = 0; k < *mat2->rows; k++)
                {
                    result->value[i][j] += (mat1->value[i][k]) * (mat2->value[k][j]);
                }
            }
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