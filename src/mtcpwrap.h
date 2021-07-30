#ifndef MTCPWRAP_H_
#define MTCPWRAP_H_

int mtcp_parseEnv(void);
int mtcp_initStack(int, int, void __interrupt __far *, void __interrupt __far *);

#endif

