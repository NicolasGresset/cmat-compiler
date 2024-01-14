int main() {
    float a = 1.7;
    float b = 2.3;
    float c = a + b;
    float d = a - b;
    float e = a * b;
    float f = a / b + 4.0;

    if (a == b) {
        a = 1.097;
    } else {
        a = 2.889;
    }

    if (c != d) {
        c = 3.0;
    } else {
        c = 4.0;
    }

    float x = 30.56;
    float y = 20.0;

    if (x > y) {
        while (y < x) {
            x = x - 1.0;
        }
    } else {
        x = 6.0;
    }

    float h = 15.0;

    for (int k = 0; k < 10; k = k + 1) {
        h = h * 2.0;
    }

    printf("a devrait valoir 2.889 : ");
    print(a);
    printf("b devrait valoir 2.3 : ");
    print(b);
    printf("c devrait valoir 3.0 : ");
    print(c);
    printf("d devrait valoir -0.6 : ");
    print(d);
    printf("e devrait valoir 3.91 : ");
    print(e);
    printf("f devrait valoir 11.7 : ");
    print(f);
    printf("h devrait valoir 3840.0 : ");
    print(h);
    printf("x devrait valoir 30.56 : ");
    print(x);
    printf("y devrait valoir 20.0 : ");
    print(y);
    return 0;
}