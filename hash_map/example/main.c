
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
#define STRUCTURED_COMPARISON_FUNCTION structured_streq
#include "../hash_map_src.c"

int main(void) {
	int error;

	struct structured_ccharp_int_hash_map map;
	structured_ccharp_int_hash_map_create(&map, 5, (struct structured_ccharp_int_hash_node [5]) {});

	// Insert element with key "A" and value 21. If an element with the same key is found, do not overwrite, instead:
	// return error STRUCTURED_ERROR_DUPLICATE. If the map is full, return error STRUCTURED_ERROR_FULL.
	error = structured_ccharp_int_hash_map_ins(&map, "A", 21, false);
	if (error) {
		fprintf(stderr, "Error inserting element: %s\n", structured_strerror(error));
		return -1;
	}

	// Print nodes formatted
	structured_ccharp_int_hash_map_printf(&map, "%s", "%i");

	// Delete element with key "A". If the element is not found (has already been deleted or never existed),
	// return error STRUCTURED_ERROR_NOT_FOUND.
	error = structured_ccharp_int_hash_map_del(&map, "A");
	if (error) {
		fprintf(stderr, "Error deleting element: %s\n", structured_strerror(error));
		return -1;
	}

	return 0;
}