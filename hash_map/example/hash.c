
uint64_t fnv1a_hash(const char * str) {
	uint64_t hash = 14695981039346656037ULL;  // FNV offset basis
	while (*str != '\0') {
		hash ^= (unsigned char) *str;
		hash *= 1099511628211ULL;             // FNV prime
		str++;
	}
	return hash;
}