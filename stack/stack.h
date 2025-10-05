
#if !(defined(STRUCTURED_TYPE) && defined(STRUCTURED_TYPE_NAME))
#	error You must provide a type (STRUCTURED_TYPE). \
You must also define the name for the type, meaning an identifier that does not have spaces \
or symbols (STRUCTURED_TYPE_NAME).
#else

#	include "affix.h"
#	define STACK STRUCTURED_POSTFIX(structured_stack, STRUCTURED_TYPE_NAME)

#	include <stddef.h>

struct STACK
{
	STRUCTURED_TYPE * data;
	size_t capacity;
	size_t top;
};

int STRUCTURED_POSTFIX(structured_stack_push, STRUCTURED_TYPE_NAME)(struct STACK * stack, STRUCTURED_TYPE element);

STRUCTURED_TYPE STRUCTURED_POSTFIX(structured_stack_pop, STRUCTURED_TYPE_NAME)(struct STACK * stack);

void STRUCTURED_POSTFIX(structured_stack_printf, STRUCTURED_TYPE_NAME)(const struct STACK * stack, const char * format);

#	undef STACK

#endif