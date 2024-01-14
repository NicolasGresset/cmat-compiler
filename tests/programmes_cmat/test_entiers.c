int main() {
    int a = 15;
    int b = 4;
    int c = a + b;
    int d = a - b;
    int e = a * b;
    int f = a / b;
    int g = a + c * d - e / f;
    int h = 15 + a;
    int i = a + 15;

    if (a == b) {
        a = 1;
    } else {
        a = 2;
    }

    if (c != d) {
        c = 3;
    } else {
        c = 4;
    }

    int x = 30;
    int y = 20;

    if (x > y) {
        while (y < x) {
            x = x - 1;
        }
    } else {
        x = 6;
    }

    for (int k = 0; k < 10; k = k + 1) {
        f = f * 2;
    }

    printf("a devrait valoir 2 : ");
    print(a);
    printf("b devrait valoir 4 : ");
    print(b);
    printf("c devrait valoir 3 : ");
    print(c);
    printf("d devrait valoir 11 : ");
    print(d);
    printf("e devrait valoir 60 : ");
    print(e);
    printf("f devrait valoir 120 : ");
    print(f);
    printf("g devrait valoir 19 : ");
    print(g);
    printf("h devrait valoir 30 : ");
    print(h);
    printf("i devrait valoir 30 : ");
    print(i);
    printf("x devrait valoir 20 : ");
    print(x);
    printf("y devrait valoir 20 : ");
    print(y);

    return 0;
}