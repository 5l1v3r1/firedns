#define _XOPEN_SOURCE 700 /* dprintf */
#include <stdio.h>
#include "../include/firedns.h"
#ifdef USE_LIBULZ
#include <ulz/stdio-repl.h>
#endif

int main(int argc, char **argv) {
	struct in_addr *result;
	firedns_state dns, *d = &dns;
	char ntoabuf[256];

	if (argc != 2) {
		dprintf(2,"usage: %s <hostname>\n",argv[0]);
		return 2;
	}

	firedns_init(d);
	firedns_add_server(d, "8.8.8.8");

	result = firedns_resolveip4(d, argv[1]);
	if (result) {
		printf("%s\n",firedns_ntoa4(result, ntoabuf));
		return 0;
	}

	return 1;
}
