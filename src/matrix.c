/**
 * In this file are implemented the useful functions for the CMat
 * language.
 *
 * Be aware : in this librairy the matrix' index starts to 0 instead
 * of 1 in the CMat language.
 */

#include "../include/matrix.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

#define CHK(op)            \
    do {                   \
        if ((op) == -1)    \
            raler(1, #op); \
    } while (0)
#define CHKN(op)           \
    do {                   \
        if ((op) == NULL)  \
            raler(1, #op); \
    } while (0)

noreturn void raler(int syserr, const char *msg, ...) {
    va_list ap;

    va_start(ap, msg);
    vfprintf(stderr, msg, ap);
    fprintf(stderr, "\n");
    va_end(ap);

    if (syserr == 1)
        perror("");

    exit(1);
}

/**
 * Allocate a matrix of size n x p and the structure ??.
 *
 */
matrix *init_mat_matrix(int n, int p) {
    matrix *M = malloc(sizeof(matrix));
    CHKN(M);

    M->n = n;
    M->p = p;

    CHKN(M->mat = calloc(sizeof(float *), n));

    for (int i = 0; i < n; ++i) {
        CHKN(M->mat[i] = calloc(sizeof(float), p));
    }

    return M;
}

/**
 * Allocate a vector of size n with the structure that allows it.
 */
matrix *init_vect_matrix(int n) {
    matrix *M = malloc(sizeof(matrix));
    CHKN(M);

    M->n = n;
    M->p = 1;

    CHKN(M->mat = calloc(sizeof(float *), n));

    for (int i = 0; i < n; ++i) {
        CHKN(M->mat[i] = calloc(sizeof(float), M->p));
    }

    return M;
}

/**
 * Performs matrix addition
 *
 * return: The matrix C that corresponds to the addition of the matrix A by B.
 */
matrix *add_matrix(const matrix *A, const matrix *B) {
    if ((A->n != B->n) || A->p != B->p)
        raler(1, "Invalid matrix dimensions\n");

    matrix *C = init_mat_matrix(A->n, A->p);

    for (int i = 0; i < A->n; ++i) {
        for (int j = 0; j < A->p; ++j)
            C->mat[i][j] = A->mat[i][j] + B->mat[i][j];
    }

    return C;
}

/**
 * Performs matrix substraction
 *
 * return: The matrix C that corresponds to the substraction of the matrix A by
 * B.
 */
matrix *sub_matrix(const matrix *A, const matrix *B) {
    if ((A->n != B->n) || A->p != B->p)
        raler(1, "Invalid matrix dimensions\n");

    matrix *C = init_mat_matrix(A->n, A->p);

    for (int i = 0; i < A->n; ++i) {
        for (int j = 0; j < A->p; ++j)
            C->mat[i][j] = A->mat[i][j] - B->mat[i][j];
    }

    return C;
}

/**
 * Performs matrix operation with a constant
 *
 * args: A the struct matrix\n
 *       cst the constant to perform the operation with
 *       op  a character that correspond to the operator
 *
 * return: C a struct matrix that is egal to A op cst
 */
matrix *cst_op_matrix(const matrix *A, const float cst, const char op) {
    matrix *C = init_mat_matrix(A->n, A->p);
    for (int i = 0; i < A->n; ++i) {
        for (int j = 0; j < A->p; ++j)
            switch (op) {
            case '+':
                C->mat[i][j] = A->mat[i][j] + cst;
                break;
            case '-':
                C->mat[i][j] = A->mat[i][j] - cst;
                break;
            case '*':
                C->mat[i][j] = A->mat[i][j] * cst;
                break;
            case '/':
                C->mat[i][j] = A->mat[i][j] / cst;
                break;
            default:
                raler(1, "Operation %c not recognized", op);
            }
    }

    return C;
}

/**
 * Performs matrix multiplication
 *
 * return: The matrix C that corresponds to the multiplication of the matrix A
 * by B.
 */
matrix *mult_matrix(const matrix *A, const matrix *B) {
    if (A->p != B->n)
        raler(1, "Invalid matrix dimensions\n");

    matrix *C = init_mat_matrix(A->n, B->p);

    for (int i = 0; i < A->n; ++i) {
        for (int j = 0; j < B->p; ++j) {
            C->mat[i][j] = 0;

            for (int k = 0; k < A->p; ++k)
                C->mat[i][j] += A->mat[i][k] * B->mat[k][j];
        }
    }
    return C;
}

/**
 * Performs matrix divsion
 *
 * return: The matrix C that corresponds to the division of the matrix A by B.
 */
matrix *div_matrix(const matrix *A, const matrix *B) {
    if (A->p != B->n)
        raler(1, "Invalid matrix dimensions\n");

    matrix *C = init_mat_matrix(A->n, B->p);

    for (int i = 0; i < A->n; ++i) {
        for (int j = 0; j < A->p; ++j) {
            C->mat[i][j] = 0;

            for (int k = 0; k < A->p; ++k)
                C->mat[i][j] += A->mat[i][k] / B->mat[k][j];
        }
    }
    return C;
}

/**
 * Performs matrix transposition
 *
 * return: The matrix C that corresponds to the transpose matrix of A.
 */
matrix *transpose_matrix(matrix *A) {
    matrix *C = init_mat_matrix(A->p, A->n);

    for (int i = 0; i < A->n; ++i) {
        for (int j = 0; j < A->p; ++j)
            C->mat[j][i] = A->mat[i][j];
    }

    return C;
}

/**
 * Displays the matrix A on the standard output
 */
void printmat(matrix *A) {
    for (int i = 0; i < A->n; ++i) {
        for (int j = 0; j < A->p; ++j) {
            if (j == A->p - 1) {
                printf("%.2f", A->mat[i][j]);
                break;
            }
            printf("%.2f\t", A->mat[i][j]);
        }
        printf("\n");
    }
}

/**
 * Free the allocated memory for a structure matrix
 */
void free_matrix(matrix *M) {
    for (int i = 0; i < M->n; ++i) {
        free(M->mat[i]);
    }

    free(M->mat);
    free(M);
}
