#include "firedns_internal.h"

struct in_addr *firedns_resolveip4(const char * const name) { 
	return firedns_resolveip4_i(name,firedns_getresult);
}

