
#include "hash.h"

struct xtable {
	u_short xid;
	char *name;
	struct xtable *next;
};

struct xtable *gtable[256], *utable[256];

