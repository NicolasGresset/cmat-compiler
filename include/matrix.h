#ifndef MATRIX_H
#define MATRIX_H

/**
 * Definition of the matrix structure
 *
 * Define a matrix or a vector of type float.
 */
typedef struct matrix
{
    union {float ** mat; float * vect;};
    int n; /// Number of columns
    int p; /// Number of rows
} matrix;


/**
 * Allocate a matrix of size n x p and the structure ??.
 *
 */
matrix * init_mat_matrix(int n, int p);

/**
 * Useless for now a vector is a matrix of size 1xn
 *
 * Allocate a vector of size n with the structure that allows it.
 */
matrix * init_vect_matrix(int n);


/**
 * Performs matrix addition
 *
 * return: The matrix C that corresponds to the addition of the matrix A by B.
 */
matrix * add_matrix(const matrix * A, const matrix * B);

/**
 * Performs matrix substraction
 *
 * return: The matrix C that corresponds to the substraction of the matrix A by B.
 */
matrix * sub_matrix(const matrix * A, const matrix * B);

/**
 * Performs matrix operation with a constant
 *
 * args: A the struct matrix\n
 *       cst the constant to perform the operation with
 *       op  a character that correspond to the operator
 *
 * return: C a struct matrix that is egal to A op cst
 */
matrix * cst_op_matrix(const matrix * A, const float cst, const char op);

/**
 * Performs matrix multiplication
 *
 * return: The matrix C that corresponds to the multiplication of the matrix A by B.
 */
matrix * mult_matrix(const matrix * A, const matrix * B);

/**
 * Performs matrix divsion
 *
 * return: The matrix C that corresponds to the division of the matrix A by B.
 */
matrix * div_matrix(const matrix * A, const matrix * B);

/**
 * Performs matrix transposition
 *
 * return: The matrix C that corresponds to the transpose matrix of A.
 */
matrix * transpose_matrix(matrix * A);

/**
 * Performs matrix transposition
 *
 * return: The matrix C that corresponds to the transpose matrix of A.
 */
matrix * transpose_matrix(matrix * A);

/**
 * Displays the matrix A on the standard output
 */
void printmat(matrix * A);

/**
 * Free the allocated memory for a structure matrix
 */
void free_matrix(matrix * M);

#endif
