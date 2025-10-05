
#include <stdint.h>

uint64_t fnv1a_hash(const char * str) {
	uint64_t hash = 14695981039346656037ULL;  // FNV offset basis
	while (*str != '\0') {
		hash ^= (unsigned char) *str;
		hash *= 1099511628211ULL;             // FNV prime
		str++;
	}
	return hash;
}

#define STRUCTURED_KEY_TYPE const char *
#define STRUCTURED_KEY_TYPE_NAME ccharp
#define STRUCTURED_VALUE_TYPE int
#define STRUCTURED_VALUE_TYPE_NAME int
#define STRUCTURED_HASH_FUNCTION fnv1a_hash
#include "../hash_map_src.c"

int main(void) {
	int * wild;
	*wild = 2;

	return 0;
}