#include "firedns_internal.h"

char *firedns_resolvename4_r(const struct in_addr * const ip) {
	return firedns_resolvename4_i(ip,firedns_getresult_r);
}

