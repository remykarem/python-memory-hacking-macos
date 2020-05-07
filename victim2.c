#include <stdio.h>
#include <unistd.h>

typedef struct {
    int a;
    int b;
    int c;
} Somestruct;

int main() {
	Somestruct struct1 = {.a=1, .b=2, .c=9};

	while (1) {
		printf("%i  %i  %p", getpid(), struct1.a, &struct1.a);
		getchar();
	}

	return 0;
}
