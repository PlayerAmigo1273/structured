
#ifndef STRUCTURED_H
#define STRUCTURED_H

#include <stdbool.h>

enum structured_error
{
	STRUCTURED_ERROR_SUCCESS,			// No error.
	STRUCTURED_ERROR_DUPLICATE,		// The same element was found.
	STRUCTURED_ERROR_NOT_FOUND,		// The element was not found.
	STRUCTURED_ERROR_FULL					// The structure is full.
};

/* Returns a stringyfied version of the error.
 * e.g. STRUCTURED_ERROR_SUCCESS -> "Success"
 */
const char * structured_strerror(int error);

/**
 * These should be returned by
 * 
 */
enum structured_control
{
	STRUCTURED_CONTROL_NONE,
	STRUCTURED_CONTROL_RETURN,
	STRUCTURED_CONTROL_BREAK,
	STRUCTURED_CONTROL_CONTINUE
};

/* Null-safe string comparison.
 * If one of them is NULL, compares the pointers (a == b).
 * Otherwise, compares the strings (strcmp).
 */
bool structured_streq(const char * a, const char * b);

#endif