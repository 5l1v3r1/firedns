#include "firedns_internal.h"

struct s_connection *firedns_add_query(struct s_header * restrict const h) { 
	struct s_connection * restrict s;
	s = firestring_malloc(sizeof(struct s_connection));
	
	h->id[0] = s->id[0] = rand() % 255; 
	h->id[1] = s->id[1] = rand() % 255;
	h->flags1 = 0 | FLAGS1_MASK_RD;
	h->flags2 = 0;
	h->qdcount = 1;
	h->ancount = 0;
	h->nscount = 0;
	h->arcount = 0;
	
	s->want_list = 0;
	
#ifdef HAVE_IPV6
	s->v6 = 0;
	if (i6 > 0) {
		s->fd = socket(PF_INET6, SOCK_DGRAM, 0);
		if (s->fd != -1) {
			if (fcntl(s->fd, F_SETFL, O_NONBLOCK) != 0) {
				close(s->fd);
				s->fd = -1;
			}
		}
		if (s->fd != -1) {
			struct sockaddr_in6 addr6;
			memset(&addr6,0,sizeof(addr6));
			addr6.sin6_family = AF_INET6;
			if (bind(s->fd,(struct sockaddr *)&addr6,sizeof(addr6)) == 0)
				s->v6 = 1;
			else
				close(s->fd);
		}
	}
	if (s->v6 == 0) {
#endif
		s->fd = socket(PF_INET, SOCK_DGRAM, 0);
		if (s->fd != -1) {
			if (fcntl(s->fd, F_SETFL, O_NONBLOCK) != 0) {
				close(s->fd);
				s->fd = -1;
			}
		}
		if (s->fd != -1) {
			struct sockaddr_in addr;
			memset(&addr,0,sizeof(addr));
			addr.sin_family = AF_INET;
			addr.sin_port = 0;
			addr.sin_addr.s_addr = INADDR_ANY;
			if (bind(s->fd,(struct sockaddr *)&addr,sizeof(addr)) != 0) {
				close(s->fd);
				s->fd = -1;
			}
		}
		if (s->fd == -1) {
			free(s);
			return NULL;
		}
#ifdef HAVE_IPV6
	}
#endif
	
	pthread_mutex_lock(&connlist_lock);
	s->next = connection_head;
	connection_head = s;
	if (wantclose == 1) {
		close(lastcreate);
		wantclose = 0;
	}
	lastcreate = s->fd;
	pthread_mutex_unlock(&connlist_lock);
	return s;
}

