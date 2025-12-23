#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main() {
    int a = -2;
    char s[32];
    itoa(a, s, 2); // 将整数a转换为二进制字符串s
    printf("%8s\n", s);
    return 0;
}
