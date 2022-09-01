struct matrix
{
    float ** value;
    int * rows;
    int * columns;
    int * depth;
};

struct matrix * matrix_create(int depth, int rows, int columns);
void matrix_transpose(struct matrix * mat);
void matrix_dotproduct(struct matrix * mat1, struct matrix * mat2, struct matrix * result);
void matrix_free(struct matrix * mat);
void matrix_convolution(struct matrix * input, struct matrix * kernel, struct matrix * output);
void matrix_addition(struct matrix * mat1, struct matrix * mat2, struct matrix * result);
void matrix_subtraction(struct matrix * mat1, struct matrix * mat2, struct matrix * result);
void matrix_multiplicationscalar(struct matrix * mat1, int scalar);
void matrix_additionscalar(struct matrix * mat1, int scalar);
