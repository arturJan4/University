#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
    
/* dodaje n argumentów */
long puzzle7(long n, ...) {
	va_list args;
	va_start(args, n);
	long result = 0;
	for ( ; n > 0; n--) {
		result += va_arg(args, long);
	}
	va_end(args);
	return result;
}