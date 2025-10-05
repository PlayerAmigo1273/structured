
#include "../structured.h"

#include <string.h>

const char * structured_strerror(int error) {
	switch (error) {
		case STRUCTURED_ERROR_SUCCESS: return "Success";
		case STRUCTURED_ERROR_DUPLICATE: return "Duplicate";
		case STRUCTURED_ERROR_NOT_FOUND: return "Not Found";
		case STRUCTURED_ERROR_FULL: return "Full";
		default: return "";
	}
}

bool structured_streq(const char * a, const char * b) {
	if ((a == NULL) || (b == NULL)) {
		return (a == b);
	}
	
	return strcmp(a, b) == 0;
}