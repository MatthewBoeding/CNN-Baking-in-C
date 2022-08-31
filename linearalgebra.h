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