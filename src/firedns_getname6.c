#include "firedns_internal.h"
#include <stdio.h>
#ifdef USE_LIBULZ
#include <ulz/stdio-repl.h>
#endif

int firedns_getname6(firedns_state* self, const struct in6_addr* ip) {
	char query[512];
	struct s_header h;
	struct s_connection* s;
	int l;
	snprintf(query, sizeof(query), "%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.%x.ip6.arpa",
			ip->s6_addr[15] & 0x0f,
			(ip->s6_addr[15] & 0xf0) >> 4,
			ip->s6_addr[14] & 0x0f,
			(ip->s6_addr[14] & 0xf0) >> 4,
			ip->s6_addr[13] & 0x0f,
			(ip->s6_addr[13] & 0xf0) >> 4,
			ip->s6_addr[12] & 0x0f,
			(ip->s6_addr[12] & 0xf0) >> 4,
			ip->s6_addr[11] & 0x0f,
			(ip->s6_addr[11] & 0xf0) >> 4,
			ip->s6_addr[10] & 0x0f,
			(ip->s6_addr[10] & 0xf0) >> 4,
			ip->s6_addr[9] & 0x0f,
			(ip->s6_addr[9] & 0xf0) >> 4,
			ip->s6_addr[8] & 0x0f,
			(ip->s6_addr[8] & 0xf0) >> 4,
			ip->s6_addr[7] & 0x0f,
			(ip->s6_addr[7] & 0xf0) >> 4,
			ip->s6_addr[6] & 0x0f,
			(ip->s6_addr[6] & 0xf0) >> 4,
			ip->s6_addr[5] & 0x0f,
			(ip->s6_addr[5] & 0xf0) >> 4,
			ip->s6_addr[4] & 0x0f,
			(ip->s6_addr[4] & 0xf0) >> 4,
			ip->s6_addr[3] & 0x0f,
			(ip->s6_addr[3] & 0xf0) >> 4,
			ip->s6_addr[2] & 0x0f,
			(ip->s6_addr[2] & 0xf0) >> 4,
			ip->s6_addr[1] & 0x0f,
			(ip->s6_addr[1] & 0xf0) >> 4,
			ip->s6_addr[0] & 0x0f,
			(ip->s6_addr[0] & 0xf0) >> 4
			);
	l = firedns_build_query_payload(query,FDNS_QRY_PTR,1,(unsigned char *)&h.payload);
	if (l == -1)
		return -1;
	s = firedns_add_query(self, &h);
	if (!s)
		return -1;
	s->dclass = 1;
	s->type = FDNS_QRY_PTR;
	if (firedns_send_requests(self, &h, s, l) == -1)
		return -1;
	return s->fd;
}

