#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int64_t decode(int64_t x,int64_t y);

int main()
{
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d\n", decode(a, b));

	return 0;
}
