#include "../../include/matrix.h"
#include <stdio.h>

int main(void) {
    /* ----------Test--------- */

    /*__________init_mat_matrix__________*/
    matrix *A = init_mat_matrix(2, 3);
    matrix *B = init_mat_matrix(2, 3);

    // Put a value in the matrix A and B
    for (int i = 0; i < A->n; ++i) {
        for (int j = 0; j < A->p; ++j) {
            A->mat[i][j] = i + j;
            B->mat[i][j] = i + j + 1;
        }
    }

    /*__________printmat__________*/
    printf("A\n");
    printmat(A);
    printf("B\n");
    printmat(B);

    /*__________cst_op_matrix__________*/
    printf("A + -1\n");
    matrix *Z = cst_op_matrix(A, -1, '+');
    printmat(Z);
    printf("A - -1\n");
    Z = cst_op_matrix(A, -1, '-');
    printmat(Z);
    printf("A * (-1)\n");
    Z = cst_op_matrix(A, -1, '*');
    printmat(Z);
    printf("A / 2\n");
    Z = cst_op_matrix(A, 2, '/');
    printmat(Z);

    /*__________add_matrix__________*/
    printf("C = A + B\n");
    matrix *C = add_matrix(A, B);
    printmat(C);

    printf("C");
    C->mat[1][1] = 2;
    C->mat[0][1] = 1;
    printmat(C);

    /*__________transpose_matrix__________*/
    printf("D = ~C\n");
    matrix *D = transpose_matrix(C);
    printmat(D);

    /*__________mult_matrix__________*/
    printf("E = A * D\n");
    matrix *E = mult_matrix(A, D);
    printmat(E);

    // Same tests on vectors
    /*__________init_mat_matrix__________*/
    matrix *a = init_mat_matrix(1, 2);
    matrix *b = init_mat_matrix(1, 2);

    // Put a value in the matrix A and B
    for (int i = 0; i < a->n; i++) {
        for (int j = 0; j < a->p; ++j) {
            a->mat[i][j] = 3;
            b->mat[i][j] = 2;
        }
    }

    /*__________printmat__________*/
    printf("a\n");
    printmat(a);
    printf("b\n");
    printmat(b);

    /*__________cst_op_matrix__________*/
    printf("a + -1\n");
    matrix *z = cst_op_matrix(a, -1, '+');
    printmat(z);
    printf("a - -1\n");
    a = cst_op_matrix(a, -1, '-');
    printmat(a);
    printf("a * (-1)\n");
    z = cst_op_matrix(a, -1, '*');
    printmat(z);
    printf("a / 2\n");
    z = cst_op_matrix(a, 2, '/');
    printmat(z);

    /*__________add_matrix__________*/
    printf("c = a + b\n");
    matrix *c = add_matrix(a, b);
    printmat(c);

    c->mat[0][1] = 2;
    c->mat[0][0] = 1;
    printmat(c);

    /*__________transpose_matrix__________*/
    printf("d = ~c\n");
    matrix *d = transpose_matrix(c);
    printmat(d);

    /*__________mult_matrix__________*/
    printf("e = d * a\n");
    matrix *e = mult_matrix(d, a);
    printmat(e);

    // Free all the allocated matrix and vectors
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    free_matrix(D);
    free_matrix(E);

    free_matrix(a);
    free_matrix(b);
    free_matrix(c);
    free_matrix(d);
    free_matrix(e);

    // Warning about those allocated memories but no bytes reachable.
    /* free_matrix(Z); */
    free_matrix(z);

#ifdef C_EXEMPLE_1
    E = add_matrix(A, transpose_matrix(D));
#endif

#ifdef C_EXEMPLE_2
    E = mult_matrix(A, transpose_matrix(D));
#endif

#ifdef C_EXEMPLE_3
    E = div_matrix(A, D);
#endif

    return 0;
}
