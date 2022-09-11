#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int fun(int a, int b);

int main()
{
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d\n", fun(a, b));

	return 0;
}
