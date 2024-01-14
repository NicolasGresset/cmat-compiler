// tester les matrices (sans erreurs)

int main() {
    matrix A[2][2] = {{1., 2.}, {3., 4.}};
    matrix B[2][2] = {{5., 6.}, {7., 8.}};
    matrix C[2][2];
    C = A + B;

    matrix D[2][2];
    D = A - B;

    matrix E[2][2];
    E = A * B;

    matrix F[2][2];
    F = A / B;

    matrix G[2][2];
    G = A;

    printf("Tests matrices carrées")
        printf("A devrait valoir [[1.0, 2.0], [3.0, 4.0]] : ");
    printmat(A);
    printf("B devrait valoir [[5.0, 6.0], [7.0, 8.0]] : ");
    printmat(B);
    printf("C devrait valoir [[6.0, 8.0], [10.0, 12.0]] : ");
    printmat(C);
    printf("D devrait valoir [[-4.0, -4.0], [-4.0, -4.0]] : ");
    printmat(D);
    printf("E devrait valoir [[19.0, 22.0], [43.0, 50.0]] : ");
    printmat(E);
    printf("F devrait valoir [[0.06666666666666667, 0.13333333333333333], "
           "[0.42857142857142855, 0.5714285714285714]] : ");
    printmat(F);
    printf("G devrait valoir [[1.0, 2.0], [3.0, 4.0]] : ");
    printmat(G);

    return 0;
}