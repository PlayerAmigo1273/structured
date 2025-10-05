
#if !(defined(STRUCTURED_TYPE) && defined(STRUCTURED_TYPE_NAME))
#	error You must provide a type (STRUCTURED_TYPE). \
You must also define the name for the type, meaning an identifier that does not have spaces \
or symbols (STRUCTURED_TYPE_NAME).
#else

#	include "../structured.h"

#	include <stdio.h>

#	define ARRAY STRUCTURED_POSTFIX(structured_array, STRUCTURED_TYPE_NAME)

void STRUCTURED_POSTFIX(structured_stack_printf, STRUCTURED_TYPE_NAME)(const struct STRUCTURED_ARRAY * array, const char * format) {
	for (int n = 0; n < array->capacity; n++) {
    printf(format, array->data[n]);
  }
}

# undef ARRAY

#endif