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
    float * contents = malloc((rows*columns)*sizeof(float));
    float ** con_ptr = malloc(sizeof(float *));
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
    float temp;
    float * val = *mat->value;
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
/**
 * @brief returs dot product of any 2 matrices (assuming mat1 cols == mat2 rows)
 *  3D matrices are also supported
 * @param mat1 - first matrix in multiplication (depth x rows x height) 
 * @param mat2 - second matrix of form depth x rows x height
 * @param result - resulting matrix of size depth, mat1->rows, mat2->columns
 */
void matrix_dotproduct(struct matrix * mat1, struct matrix * mat2, struct matrix * result)
{
    *result->rows = *mat1->rows;
    *result->columns = *mat2->columns;
    int rows = *result->rows;
    int cols = *result->columns;
    float * val_ptr =  *result->value;
    float * mat1_ptr = *(*mat1).value;
    float * mat2_ptr = *mat2->value;
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

/**
 * @brief frees all memory malloc'd in matrix_create
 * Be sure to call this when you're done with a matrix!
 * @param mat - matrix to have memory de-allocated
 */
void matrix_free(struct matrix * mat)
{
    float * ptr_val = *mat->value;
    free(ptr_val);
    free(mat->value);
    free(mat->columns);
    free(mat->rows);
    free(mat->depth);
    return;

}
/**
 * @brief performs convolution (or cross-correlation) on 2 matrices
 *  assume that all matrices have been malloc'd and stride = 1
 * @param input - must be larget than kernel with same depth
 * @param kernel - must be smaller than input with same depth
 * @param output - convolution output
 * @param stride - stride length of convolution
 */
void matrix_convolution_valid(struct matrix * input, struct matrix * kernel, struct matrix * output, int stride)
{
    if(*kernel->rows > *input->rows || *kernel->columns > *input->columns || *input->depth != *kernel->depth)
    {
     printf("Kernel is too large for input matrix");   
    }
    else
    {
        float value = 0;
        int iterations = (*output->rows * *output->columns);
        int iterations_per_row = (*input->columns - *kernel->columns) / stride + 1;
        int row_offset, col_offset;
        for(int i = 0; i < iterations; i++)
        {
            row_offset = (i / iterations_per_row) * stride;
            col_offset = (i % iterations_per_row) * stride;
            value = 0;
            for(int r = 0; r < *kernel->rows; r++)
            {
                for(int c = 0; c < *kernel->columns; c++)
                {
                    value += (*kernel->value)[r*(*kernel->columns)+c] * (*input->value)[(r+row_offset)*(*input->columns)+c+col_offset];
                    float h1 = (*input->value)[(r+row_offset)*(*input->columns)+c+col_offset];
                    float h2 =  (*kernel->value)[r*(*kernel->columns)+c];
                }
            }
            (*output->value)[i]=value;
        }
    }
}

void matrix_convolution_full(struct matrix * input, struct matrix * kernel, struct matrix * output, int stride)
{
    if(*kernel->rows > *input->rows || *kernel->columns > *input->columns || *input->depth != *kernel->depth)
    {
     printf("Kernel is too large for input matrix");   
    }
    else if(*output->rows != (*input->rows + *kernel->rows - 1) || (*output->columns != (*input->columns + *kernel->columns - 1)))
    {
        printf("Output dimension does not match kernel and input filter for full convolution");
    }
    else
    {
        float value = 0;
        int iterations = (*output->rows * *output->columns);
        printf("iterations: %i", iterations);
        int iterations_per_row = (*input->columns + *kernel->columns-1);
        int row_offset, col_offset, curr_ops_row, curr_ops_col, start_loc_k;
        for(int i = 0; i < iterations; i++)
        {
            row_offset = 0;
            col_offset = 0;
            int active_row = (i / iterations_per_row);
            int k = i % iterations_per_row;
            start_loc_k = (*kernel->columns)*(*kernel->rows)-1;
            if(k < *kernel->columns)
            {   
                col_offset = 0;
                curr_ops_col = k;
            }
            else if(k >= *kernel->columns && k < (*input->columns - *kernel->columns + 1))
            {
                col_offset = k - *kernel->columns + 1;
                curr_ops_col = *kernel->columns;

            }
            else if(k > (*input->columns - *kernel->columns + 1))
            {
                col_offset = k - *kernel->columns + 1;
                curr_ops_col = *kernel->columns -(k - (*input->columns - *kernel->columns + 1));
                start_loc_k -= (k-*kernel->columns);
            }
            if(active_row < *kernel->rows)
            {
                row_offset = 0;
                curr_ops_row = active_row;
            }
            else if(active_row >= *kernel->rows && active_row <= (*input->rows - *kernel->rows + 1))
            {
                row_offset = active_row - *kernel->rows +1;
                curr_ops_row = *kernel->rows;
            }
            else if(active_row+*kernel->rows > *input->rows)
            {
                row_offset = active_row - *kernel->rows+1;
                curr_ops_row = *kernel->rows - (active_row - (*input->columns - *kernel->columns + 1));
                start_loc_k -= (*kernel->columns)*(active_row+*kernel->rows - *input->rows - 2);
            }
            value = 0;
            //printf("\n[%i,%i]\n", curr_ops_row, curr_ops_col);

            for(int r = 0; r <= curr_ops_row; r++)
            {
                for(int c = 0; c <= curr_ops_col; c++)
                {
                    value += (*kernel->value)[start_loc_k - c -(*kernel->columns)*r] * (*input->value)[(row_offset+curr_ops_row-r)*(*input->rows)+(col_offset + curr_ops_col - c)];
                    int loc = start_loc_k - c -(*kernel->columns)*r;
                    int loc2 = (row_offset+curr_ops_row-r)*(*input->rows)+(col_offset + curr_ops_col - c);
                    //printf("%i * %i ->", loc, loc2);
                }
            }
            (*output->value)[i]=value;
        }
    }
}

/**
 * @brief performs elementwise addition on 2 matrices for scalar see
 *  matrix_additionscalar or scalar to matrix. 
 * @param mat1 - first input matrix must be same size as mat2
 * @param mat2 - second input matrix
 * @param result - addition output
 */
void matrix_addition(struct matrix * mat1, struct matrix * mat2, struct matrix * result)
{
    if(*mat1->rows == *mat2->rows && *mat1->columns == *mat2->columns && *mat1->depth == *mat2->depth)
    {
        for(int d = 0; d < *mat1->depth; d++)
        {
            for(int r = 0; r < *mat1->rows; r++)
            {
                for(int c = 0; c < *mat1->columns; c++)
                {
                    int index = d*(*mat1->rows * *mat1->columns) + r* (*mat1->columns) + c;
                    *result->value[index] = *mat1->value[index] + *mat2->value[index];
                }
            }
        }
    }
}

void matrix_subtraction(struct matrix * mat1, struct matrix * mat2, struct matrix * result)
{
    if(*mat1->rows == *mat2->rows && *mat1->columns == *mat2->columns && *mat1->depth == *mat2->depth)
    {
        for(int d = 0; d < *mat1->depth; d++)
        {
            for(int r = 0; r < *mat1->rows; r++)
            {
                for(int c = 0; c < *mat1->columns; c++)
                {
                    int index = d*(*mat1->rows * *mat1->columns) + r* (*mat1->columns) + c;
                    *result->value[index] = *mat1->value[index] - *mat2->value[index];
                }
            }
        }
    }
}

void matrix_multiplicationscalar(struct matrix * mat1, int scalar)
{
    int depth, rows, cols;
    depth = *mat1->depth;
    rows = *mat1->rows;
    cols = *mat1->columns;
    for(int d = 0; d < depth; d++)
    {
        for (int r = 0; r<rows; r++)
        {
            for(int c = 0; c < cols; c++)
            {
                *mat1->value[d*(rows*cols)+(r*cols)+c] = *mat1->value[d*(rows*cols)+(r*cols)+c] * scalar;
            }
        }
    }
}

void matrix_additionscalar(struct matrix * mat1, int scalar)
{
    int depth, rows, cols;
    depth = *mat1->depth;
    rows = *mat1->rows;
    cols = *mat1->columns;
    for(int d = 0; d < depth; d++)
    {
        for (int r = 0; r<rows; r++)
        {
            for(int c = 0; c < cols; c++)
            {
                *mat1->value[d*(rows*cols)+(r*cols)+c] = *mat1->value[d*(rows*cols)+(r*cols)+c] + scalar;
            }
        }
    }
}

