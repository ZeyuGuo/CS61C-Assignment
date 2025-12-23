#include <stdio.h>

int main(int argc, char *argv[]) {
    int A[3] = {10, 20, 30};
    int *p = A;
    printf("%d\n", *p); // 10
    p = p+1;
    printf("%d\n", *p); // 20

    return 0;
}