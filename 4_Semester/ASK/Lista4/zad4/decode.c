#include <stdint.h>
int64_t decode(int64_t x,int64_t y)
{
	return ((((x+y)^x) & ((x+y)^y)) >> 63);
}
