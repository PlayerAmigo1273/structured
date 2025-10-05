
#ifndef STRUCTURED_ARRAY_H
#define STRUCTURED_ARRAY_H

#if !(defined(STRUCTURED_TYPE) && defined(STRUCTURED_TYPE_NAME))
#	error You must provide a type (STRUCTURED_TYPE). \
You must also define the name for the type, meaning an identifier that does not have spaces \
or symbols (STRUCTURED_TYPE_NAME).
#else

#	include "../affix.h"
#	define ARRAY STRUCTURED_POSTFIX(structured_array, STRUCTURED_TYPE_NAME)

#	include <stddef.h>

struct STRUCTURED_ARRAY
{
  STRUCTURED_TYPE * data;
  size_t capacity;
};

STRUCTURED_TYPE * structured_array_find(const struct ARRAY * array, STRUCTURED_TYPE element);

#	undef ARRAY

#endif
#endif