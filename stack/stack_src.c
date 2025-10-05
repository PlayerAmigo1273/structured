
#if !(defined(STRUCTURED_TYPE) && defined(STRUCTURED_TYPE_NAME))
#	error You must provide a type (STRUCTURED_TYPE). \
You must also define the name for the type, meaning an identifier that does not have spaces \
or symbols (STRUCTURED_TYPE_NAME).
#else

#	include "structured.h"

#	include <stdio.h>

#	define STACK STRUCTURED_POSTFIX(structured_stack, STRUCTURED_TYPE_NAME)

int STRUCTURED_POSTFIX(structured_stack_push, STRUCTURED_TYPE_NAME)(struct STACK * stack, STRUCTURED_TYPE element) {
	if (stack->top == stack->capacity) {
    return STRUCTURED_ERROR_FULL;
  }
  
	stack->data[stack->top] = element;
  stack->top++;
	return STRUCTURED_ERROR_SUCCESS;
}

STRUCTURED_TYPE STRUCTURED_POSTFIX(structured_stack_pop, STRUCTURED_TYPE_NAME)(struct STACK * stack) {
	if (stack->top != 0) {
    stack->top--;
  }
    
  return stack->data[stack->top];
}

void STRUCTURED_POSTFIX(structured_stack_printf, STRUCTURED_TYPE_NAME)(const struct STACK * stack, const char * format) {
	for (int n = 0; n < stack->top; n++) {
    printf(format, stack->data[n]);
  }
}

# undef STACK

#endif