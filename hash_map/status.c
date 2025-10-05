
#include "status.h"

const char * structured_hash_strstatus(int status) {
	switch (status) {
		case STRUCTURED_HASH_NODE_UNTOUCHED: return "Untouched";
		case STRUCTURED_HASH_NODE_DELETED: return "Deleted";
		case STRUCTURED_HASH_NODE_OCCUPIED: return "Occupied";
		default: return "";
	}
}