
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
#	 include "hash_map.h"

#	 include "../structured.h"

#	 include <stdio.h>
#	 include <string.h>

#  define PREFIX(x) STRUCTURED_ID(STRUCTURED_POSTFIX(STRUCTURED_KEY_TYPE_NAME, STRUCTURED_VALUE_TYPE_NAME), x)
#	 define HASH_NODE PREFIX(hash_node)
#	 define HASH_MAP PREFIX(hash_map)

void PREFIX(hash_map_create)(struct HASH_MAP * map, uint64_t capacity, struct HASH_NODE * nodes) {
	map->capacity = capacity;
	map->nodes = nodes;
	// Also sets keys and values but that doesn't matter
	memset(map->nodes, STRUCTURED_HASH_NODE_UNTOUCHED, capacity*sizeof(struct HASH_NODE));
}

uint64_t PREFIX(hash_map_hash)(const struct HASH_MAP * map, STRUCTURED_KEY_TYPE key) {
	return STRUCTURED_HASH_FUNCTION(key)%(map->capacity);
}

bool PREFIX(hash_map_iterate_key)(struct HASH_MAP * map, STRUCTURED_KEY_TYPE key, PREFIX(hash_map_iterator) iterator, void * args, void ** result) {
	uint64_t idx = PREFIX(hash_map_hash)(map, key);
	uint64_t n = idx;
	do {
		int control = iterator(map, key, n, args, result);
		if (control == STRUCTURED_CONTROL_RETURN) {
			return true;
		}
		else if (control == STRUCTURED_CONTROL_BREAK) {
			break;
		}
		else if (control == STRUCTURED_CONTROL_CONTINUE) {
			continue;
		}
			
		n = (n + 1)%(map->capacity);
	} while (n != idx);
	
	return false;
}

static int node_iterator(struct HASH_MAP * map, STRUCTURED_KEY_TYPE key, uint64_t n, void * args, void ** result) {
	// If an untouched node is found, there is no node with 'key'.
	// It would have overwritten the untouched node.
	if (map->nodes[n].status == STRUCTURED_HASH_NODE_UNTOUCHED) {
		return STRUCTURED_CONTROL_BREAK;
	}
			
	// If a deleted node is found, continue searching.
	if (map->nodes[n].status == STRUCTURED_HASH_NODE_DELETED) {
		return STRUCTURED_CONTROL_NONE;
	}

	// If an occupied node has a matching key, it's the one.
	if ((map->nodes[n].key == key) || structured_streq(map->nodes[n].key, key)) {
		// Return &(map->nodes[n]).
		*result = (void *) &(map->nodes[n]);
		return STRUCTURED_CONTROL_RETURN;
	}

	return STRUCTURED_CONTROL_NONE;
}

int PREFIX(hash_map_node)(const struct HASH_MAP * map, STRUCTURED_KEY_TYPE key, struct HASH_NODE ** node_ptr) {
	void * result;
	bool ret = PREFIX(hash_map_iterate_key)((struct HASH_MAP *) map, key, node_iterator, NULL, &result);

	*node_ptr = (struct HASH_NODE *) result;
  return ret ? STRUCTURED_ERROR_SUCCESS : STRUCTURED_ERROR_NOT_FOUND;
}

struct ins_iterator_args
{
	STRUCTURED_VALUE_TYPE value;
	bool overwrite;
};

static int ins_iterator(struct HASH_MAP * map, STRUCTURED_KEY_TYPE key, uint64_t n, void * args, void ** result) {
	struct ins_iterator_args * iterator_args = (struct ins_iterator_args *) args;

	if (map->nodes[n].status == STRUCTURED_HASH_NODE_OCCUPIED) {
		if (structured_streq(map->nodes[n].key, key)) {
			if (iterator_args->overwrite) {
				map->nodes[n].key = key;
				map->nodes[n].value = iterator_args->value;
				map->nodes[n].status = STRUCTURED_HASH_NODE_OCCUPIED;
				
				// Return success.
				*result = (void *) STRUCTURED_ERROR_SUCCESS;
				return STRUCTURED_CONTROL_RETURN;
			}
			else {
				// Return error: duplicate.
				*result = (void *) STRUCTURED_ERROR_DUPLICATE;
				return STRUCTURED_CONTROL_RETURN;
			}
		}
	}
	else {
		map->nodes[n].key = key;
		map->nodes[n].value = iterator_args->value;
		map->nodes[n].status = STRUCTURED_HASH_NODE_OCCUPIED;
		
		// Return success.
		*result = (void *) STRUCTURED_ERROR_SUCCESS;
		return STRUCTURED_CONTROL_RETURN;
	}

	return STRUCTURED_CONTROL_NONE;
}

int PREFIX(hash_map_ins)(struct HASH_MAP * map, STRUCTURED_KEY_TYPE key, STRUCTURED_VALUE_TYPE value, bool overwrite) {
	struct ins_iterator_args iterator_args = {value, overwrite};
	void * result;
	bool ret = PREFIX(hash_map_iterate_key)((struct HASH_MAP *) map, key, ins_iterator, &iterator_args, &result);
	
	// Return code.
	return ret ? ((intptr_t) result) : STRUCTURED_ERROR_FULL;
}

int PREFIX(hash_map_del)(struct HASH_MAP * map, STRUCTURED_KEY_TYPE key) {
	struct structured_ccharp_int_hash_node * node_ptr;
	int error = PREFIX(hash_map_node)(map, key, &node_ptr);
	if (!error) {
		node_ptr->status = STRUCTURED_HASH_NODE_DELETED;
	}

	// Return code.
	return error;
}

void PREFIX(hash_map_printf)(const struct HASH_MAP * map, const char * key_format, const char * value_format) {
	struct HASH_NODE node;
	
	printf("{");
	for (int n = 0; n < (map->capacity - 1); n++) {
		node = map->nodes[n];
		printf("{");
		printf(key_format, node.key);
		printf(", ");
		printf(value_format, node.value);
		printf(", %s}, ", structured_hash_strstatus(node.status));
	}
	node = map->nodes[map->capacity - 1];
	printf("{");
	printf(key_format, node.key);
	printf(", ");
	printf(value_format, node.value);
	printf(", %s}}", structured_hash_strstatus(node.status));
}

#	 undef PREFIX
#	 undef HASH_NODE
#	 undef HASH_MAP

#	endif

#endif