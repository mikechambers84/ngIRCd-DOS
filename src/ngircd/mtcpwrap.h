#ifndef MTCPWRAP_H_
#define MTCPWRAP_H_

#include "global.cfg"
#include "../ipaddr/ng_ipaddr.h"

void shutdown(int rc);
int mtcp_parseEnv(void);
int mtcp_initStack(int socks, int ringsize, void __interrupt __far (*ctrlbreak)(), void __interrupt __far (*ctrlc)());
void mtcp_getAddr(int sock, void* dst);
UINT16 mtcp_getPort(int sock);
int mtcp_getSocket(void);
void gethostname(char* host, int len);
int connect(int sockfd, char *host, uint16_t port);
int send(int sockfd, uint8_t *buf, size_t len, int flags);
int recv(int sockfd, uint8_t *buf, size_t len, int flags);
int bind(int sockfd, uint16_t port);
int accept(int sockfd, ng_ipaddr_t *addr, int *addrlen);
int closesocket(int sock);
int closesocket2(int sock);

#endif

