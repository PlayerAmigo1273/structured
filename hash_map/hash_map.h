
#ifndef STRUCTURED_HASH_MAP_H
#define STRUCTURED_HASH_MAP_H

#if !(defined(STRUCTURED_KEY_TYPE) && defined(STRUCTURED_VALUE_TYPE) 					\
	&& defined(STRUCTURED_KEY_TYPE_NAME) && defined(STRUCTURED_VALUE_TYPE_NAME) \
)
# error You must define a key type (STRUCTURED_KEY_TYPE) and a value type (STRUCTURED_VALUE_TYPE). \
You must also define the names for the respective defined types (STRUCTURED_KEY_TYPE_NAME, STRUCTURED_VALUE_TYPE_NAME), \
meaning an identifier that does not have spaces or symbols.
#else

# if !defined(STRUCTURED_HASH_FUNCTION)
	 #error You must define a hashing function for your key type.
# else

#	 include "../affix.h"
#  define PREFIX(x) STRUCTURED_ID(STRUCTURED_POSTFIX(STRUCTURED_KEY_TYPE_NAME, STRUCTURED_VALUE_TYPE_NAME), x)
#	 define HASH_NODE PREFIX(hash_node)
#	 define HASH_MAP PREFIX(hash_map)

#	 include "status.h"

#	 include <stdint.h>
#	 include <stdbool.h>

struct HASH_NODE
{
	STRUCTURED_KEY_TYPE key;
	STRUCTURED_VALUE_TYPE value;
	enum structured_hash_node_status status;
};

struct HASH_MAP
{
	struct HASH_NODE * nodes;
	uint64_t capacity;
};

typedef int (* PREFIX(hash_map_iterator))(struct HASH_MAP * map, STRUCTURED_KEY_TYPE key, uint64_t n, void * args, void ** result);
bool PREFIX(hash_map_iterate_key)(struct HASH_MAP * map, STRUCTURED_KEY_TYPE key, PREFIX(hash_map_iterator) iterator, void * args, void ** result);

uint64_t PREFIX(hash_map_hash)(const struct HASH_MAP * map, STRUCTURED_KEY_TYPE key);

void PREFIX(hash_map_create)(struct HASH_MAP * map, uint64_t capacity, struct HASH_NODE * nodes);

int PREFIX(hash_map_node)(const struct HASH_MAP * map, STRUCTURED_KEY_TYPE key, struct HASH_NODE ** node_ptr);

int PREFIX(hash_map_ins)(struct HASH_MAP * map, STRUCTURED_KEY_TYPE key, STRUCTURED_VALUE_TYPE value, bool overwrite);

int PREFIX(hash_map_del)(struct HASH_MAP * map, STRUCTURED_KEY_TYPE key);

void PREFIX(hash_map_printf)(const struct HASH_MAP * map, const char * key_format, const char * value_format);

#	 undef HASH_MAP
#	 undef HASH_NODE
#  undef PREFIX

# endif
#endif
#endif