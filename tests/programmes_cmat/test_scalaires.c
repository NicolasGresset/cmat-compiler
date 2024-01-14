int main() {
    int a = 1;
    float b = 2.7;
    int c = a + b;
    float d = a + b;

    printf("c devrait valoir 3 : ");
    print(c);
    printf("d devrait valoir 3.7 : ");
    print(d);

    int e = 6.8 + 2;
    float f = 3 * 1.5;
    printf("e devrait valoir 8 : ");
    print(e);
    printf("f devrait valoir 4.5 : ");
    print(f);

    if (a < 0) {
        int g = 1;
    } else {
        a = 2;
    }

    if (b > 0.) {
        float h = 1.0;
    } else {
        b = 2.0;
    }

    return 0;
}