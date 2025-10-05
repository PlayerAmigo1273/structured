
#ifndef STRUCTURED_HASH_STATUS_H
#define STRUCTURED_HASH_STATUS_H

enum structured_hash_node_status
{
	STRUCTURED_HASH_NODE_UNTOUCHED,
	STRUCTURED_HASH_NODE_DELETED,
	STRUCTURED_HASH_NODE_OCCUPIED
};

/* Returns a stringyfied version of the status.
 * e.g. STRUCTURED_HASH_NODE_OCCUPIED -> "Occupied"
 */
const char * structured_hash_strstatus(int status);

#endif