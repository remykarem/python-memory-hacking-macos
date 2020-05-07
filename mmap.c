#include <stdio.h>
#include <stdlib.h>

int main() {
    int a = 9;
    int *b = (int *) malloc(sizeof(int));
    if (b == NULL)
        return 1;

    printf("%p\n", &a);
    printf("%p\n", b);
    printf("%p\n", main);

    while (1) {}

    return 0;
}