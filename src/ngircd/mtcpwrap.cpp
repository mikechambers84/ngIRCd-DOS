#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <conio.h>
#include "tcp.h"
#include "tcpsockm.h"
#include "utils.h"
#include "arp.h"
#include "dns.h"
#include "packet.h"

#define RECV_BUFFER_SIZE    1024

TcpSocket *tcpsock[TCP_MAX_SOCKETS];
TcpSocket *tcpconfsendl, *tcpmotdsendl, *tcpconfrecvl, *tcpmotdrecvl;
uint16_t lport[TCP_MAX_SOCKETS];

void conf_send_reset(char* fname, FILE* sendfile);
void conf_recv_reset(char* fname, FILE* recvfile);
void conf_send_work(int sock, FILE* sendfile);
void conf_recv_work(int sock, FILE* recvfile);

FILE *confsend = NULL;
FILE *confrecv = NULL;
FILE *motdsend = NULL;
FILE *motdrecv = NULL;

void __interrupt __far ctrlBreakHandler(void) {
}

void __interrupt __far ctrlCHandler(void) {
}

int getUnusedSocket() {
    for (int i=0; i<TCP_MAX_SOCKETS; i++) {
        if (tcpsock[i] == NULL) return i;
    }
    return -1;
}

#define NGIRCd_ConfFile "NGIRCD.CNF"
#define Conf_MotdFile "MOTD.TXT"

extern "C" {
        #include "io.h"
        #include "../ipaddr/ng_ipaddr.h"
		#include "log.h"
        #include "mtcpwrap.h"
		
		//GLOBAL char NGIRCd_ConfFile[256];
		//GLOBAL char Conf_MotdFile[256];
        
        void mtcp_cb_clientserver(int sock, short what);
    int mtcp_New_Connection(int Sock, bool IsSSL);

        void shutdown(int rc) {
                Utils::endStack();
                exit(rc);
        }

    //TODO: make this actually work
    int getsockname(int sockfd, char* addr, size_t addrlen) {
                mtcp_getAddr(sockfd, addr);
        return 0;
    }

    /*struct hostent *gethostbyname(const char *name) {
        return NULL;
    }*/

    void tcp_tick(void) {
        PACKET_PROCESS_SINGLE;
        Arp::driveArp();
        Tcp::drivePackets();
                
                for (int i=0; i<TCP_MAX_SOCKETS; i++) {
            if (tcpsock[i] != NULL) {
                if (tcpsock[i]->state == TCP_STATE_LISTEN) {
                    //printf("listening ");
                    int newsock;
                    newsock = getUnusedSocket();
                    if (newsock >= 0) {
                        tcpsock[newsock] = TcpSocketMgr::accept();
                        if (tcpsock[newsock] != NULL) {
							switch (tcpsock[newsock]->srcPort) {
								case 500: //send conf port
									Log(LOG_INFO, "NOTE: New connection on send conf port. (%s)", NGIRCd_ConfFile);
									conf_send_reset(NGIRCd_ConfFile, confsend);
									break;
								case 501: //receive conf port
									Log(LOG_INFO, "NOTE: New connection on recv conf port. (%s)", NGIRCd_ConfFile);
									conf_recv_reset(NGIRCd_ConfFile, confrecv);
									break;
								case 502: //send motd port
									Log(LOG_INFO, "NOTE: New connection on send MOTD port. (%s)", Conf_MotdFile);
									conf_send_reset(Conf_MotdFile, motdsend);
									break;
								case 503: //receive motd port
									Log(LOG_INFO, "NOTE: New connection on recv MOTD port. (%s)", Conf_MotdFile);
									conf_recv_reset(Conf_MotdFile, motdrecv);
									break;
								default: //ngIRCd ports
									mtcp_New_Connection(newsock, false);
									break;
							}
                        }
                    }
                } else if (tcpsock[i]->state == TCP_STATE_ESTABLISHED) {
							switch (tcpsock[i]->srcPort) {
								case 500: //send conf port
									conf_send_work(i, confsend);
									break;
								case 501: //receive conf port
									conf_recv_work(i, confrecv);
									break;
								case 502: //send motd port
									conf_send_work(i, motdsend);
									break;
								case 503: //receive motd port
									conf_recv_work(i, motdrecv);
									break;
								default: //ngIRCd ports
                                    mtcp_cb_clientserver(i,
                                            ((tcpsock[i]->recvDataWaiting() == true) ? IO_WANTREAD : 0) |
                                            (tcpsock[i]->hasRoom() ? IO_WANTWRITE : 0) );
									break;
							}
                        }
				else {
							switch (tcpsock[i]->srcPort) {
								case 500: //send conf port
									closesocket(i); //frees socket
									Log(LOG_INFO, "NOTE: Closed send conf socket.");
									break;
								case 501: //receive conf port
									fclose(confrecv);
									closesocket(i);
									Log(LOG_INFO, "NOTE: Saved new %s and closed recv conf socket.", NGIRCd_ConfFile);
									break;
								case 502: //send motd port
									closesocket(i); //frees socket
									Log(LOG_INFO, "NOTE: Closed send motd socket.");
									break;
								case 503: //receive motd port
									fclose(motdrecv);
									closesocket(i);
									Log(LOG_INFO, "NOTE: Saved new %s and closed recv motd socket.", Conf_MotdFile);
									break;
							}
				}
            }
        }
		
    }

    int bind(int sockfd, uint16_t port) {
        //printf("bind sockfd = %d, port = %u\n", sockfd, port);
        if (tcpsock[sockfd] == NULL) return -1;
        lport[sockfd] = port;
        return 0;
    }

    int accept(int sockfd, ng_ipaddr_t *addr,
                  int *addrlen) {
        int newsock;
        if (tcpsock[sockfd] == NULL) return -1;
                //return -1;
                
        newsock = getUnusedSocket();
        if (newsock < 0) return -1;

        //TODO: This could be an issue. I can't specify which listening socket to accept from?? Uh-oh...
        tcpsock[newsock] = TcpSocketMgr::accept();
                
        mtcp_getAddr(newsock, (void*)addr->sin4.sin_addr);
        addr->sin4.port = tcpsock[newsock]->dstPort;
        return newsock;
    }

    int closesocket(int sock) {
        if (tcpsock[sock] == NULL) return -1;
        tcpsock[sock]->close();
        TcpSocketMgr::freeSocket(tcpsock[sock]);
        tcpsock[sock] = NULL; //TODO: error checking the above call first??
        return 0;
    }

    int closesocket2(int sock) { //TODO: This was a different call than closesocket. Do I need to handle differently?
        return closesocket(sock);
    }

	void gethostname(char* host, int len) {
		strlcpy(host, MyHostname, len);
	}

/*    bool io_close(int sock) {
        if (tcpsock[sock] == NULL) return false;
        tcpsock[sock]->close();
        TcpSocketMgr::freeSocket(tcpsock[sock]);
        return true;
    }*/

    int send(int sockfd, uint8_t *buf, size_t len, int flags) {
        int sent;
		//uint8_t* tmp;
        if (tcpsock[sockfd] == NULL) return -1;
        /*for (sent=0; sent<len; sent++) {
            printf("%c", buf[sent]);
        }*/
        /*while(1) {
            sent = tcpsock[sockfd]->send(buf, len);
			if (sent != 0) break;
            PACKET_PROCESS_SINGLE;
            Arp::driveArp();
            Tcp::drivePackets();                        
        }
        return sent;*/
        sent = 0;
        while (sent < len) {
            int ret;
            ret = tcpsock[sockfd]->send(&buf[sent], ((len - sent) > 1024) ? 1024 : (len - sent));

            PACKET_PROCESS_SINGLE;
            Arp::driveArp();
            Tcp::drivePackets();

            if (ret <= 0) break;
            sent += ret;
		}
        return sent;
    }

    int recv(int sockfd, uint8_t *buf, size_t len, int flags) {
        if (tcpsock[sockfd] == NULL) return -1;
                /*if (kbhit()) {
                        buf[0] = getch();
                        return 1;
                } else {
                        return 0;
                }*/
        return tcpsock[sockfd]->recv(buf, len);
    }

    int listen(int sockfd, int backlog) {
        if (tcpsock[sockfd] == NULL) return -1;
        return tcpsock[sockfd]->listen(lport[sockfd], RECV_BUFFER_SIZE);
    }

    //int connect(int sockfd, ng_ipaddr_t *addr,  addrlen) {
	int connect(int sockfd, char *host, uint16_t port) {
		int rc;
		IpAddr_t serverAddr;
		
		Log(LOG_INFO, "mTCP: Resolving \"%s\"...", host);
		
		rc = Dns::resolve(host, serverAddr, 1);
		Log(LOG_INFO, "mTCP: First Dns::resolve() rc = %d", rc);
		if (rc < 0) {
			closesocket(sockfd);
			return rc;
		}
		
		//TODO: I don't like this, it makes connect blocking if we don't know a hostname yet. It will timeout after 5 seconds.
		//Use IP addresses instead of hostnames in the conf file until this is fixed.
		int8_t done = 0;
		while ( !done ) {
			//if ( CtrlBreakDetected ) break;
			if ( !Dns::isQueryPending( ) ) break;
			PACKET_PROCESS_MULT(5);
			Arp::driveArp( );
			Tcp::drivePackets( );
			Dns::drivePendingQuery( );
		}

		rc = Dns::resolve(host, serverAddr, 0);
		Log(LOG_INFO, "mTCP: Second Dns::resolve() rc = %d", rc);
		if (rc != 0) {
			closesocket(sockfd);
			return rc;
		}

        Log(LOG_DEBUG, "mTCP: Resolved. Connect to %u.%u.%u.%u:%u", serverAddr[0], serverAddr[1], serverAddr[2], serverAddr[3], port);
		tcpsock[sockfd]->setRecvBuffer(RECV_BUFFER_SIZE);
		rc = tcpsock[sockfd]->connect(0, serverAddr, port, 5000); //TODO: This can block for up to 5 seconds. Make this non-blocking.
		if (rc < 0) {
			closesocket(sockfd);
			return rc;
		}
		
		return 0;
    }

    int mtcp_getSocket() {
        int newsock;
        newsock = getUnusedSocket();
        if (newsock < 0) return newsock;

        tcpsock[newsock] = TcpSocketMgr::getSocket();
        
        if (tcpsock[newsock] != NULL) {
            return newsock;
        } else {
            return -1;
        }
    }
        
    void mtcp_getAddr(int sock, void * dst) {
		((UINT8*)dst)[0] = tcpsock[sock]->dstHost[0];
		((UINT8*)dst)[1] = tcpsock[sock]->dstHost[1];
		((UINT8*)dst)[2] = tcpsock[sock]->dstHost[2];
		((UINT8*)dst)[3] = tcpsock[sock]->dstHost[3];
    }
		
	UINT16 mtcp_getPort(int sock) {
		return tcpsock[sock]->dstPort;
	}

    void sock_init(void) {
        Log(LOG_INFO, "Parsing mTCP environment variables");
        if ( Utils::parseEnv( ) != 0 ) {
            printf("FAILURE\n");
            shutdown(-1);
        }

        Log(LOG_INFO, "Initializing TCP/IP");
        if ( Utils::initStack( TCP_MAX_SOCKETS, TCP_MAX_XMIT_BUFS, ctrlBreakHandler, ctrlCHandler ) ) {
            printf("FAILURE\n");
            shutdown(-1);
        }

        for (int i=0; i<TCP_MAX_SOCKETS; i++) {
            tcpsock[i] = NULL;
        }
                
        /*tcpconfsendl = TcpSocketMgr::getSocket();
		if (tcpconfsendl != NULL) {
			tcpconfsendl->listen(500, 1024); //don't really need a receive buffer here...
		} else {
			Log(LOG_EMERG, "WTF: Can't get a socket for conf send port!\n");
		}

        tcpconfrecvl = TcpSocketMgr::getSocket();
		if (tcpconfrecvl != NULL) {
			tcpconfrecvl->listen(501, 1024);
		} else {
			Log(LOG_EMERG, "WTF: Can't get a socket for conf recv port!\n");
		}

        tcpmotdsendl = TcpSocketMgr::getSocket();
		if (tcpmotdsendl != NULL) {
			tcpmotdsendl->listen(502, 1024); //don't really need a receive buffer here...
		} else {
			Log(LOG_EMERG, "WTF: Can't get a socket for motd send port!\n");
		}

        tcpmotdrecvl = TcpSocketMgr::getSocket();
		if (tcpmotdrecvl != NULL) {
			tcpmotdrecvl->listen(503, 1024);
		} else {
			Log(LOG_EMERG, "WTF: Can't get a socket for motd recv port!\n");
		}*/

    }
};

void conf_send_reset(char* fname, FILE* sendfile) {
	if (sendfile != NULL) {
		fclose(sendfile);
	}
	sendfile = fopen(fname, "rb");
}

uint8_t conftmp[128];
void conf_send_work(int sock, FILE* sendfile) {
	if (sendfile == NULL) {
		closesocket(sock);
		return;
	}
	
	int len;
	len = fread(conftmp, 1, 128, sendfile);
	if (len > 0) {
		while (len) {
			int ret;
			ret = send(sock, conftmp, len, 0);
			if (ret >= 0) {
				len -= ret;
			} else {
				fclose(sendfile);
				closesocket(sock);
			}
			PACKET_PROCESS_SINGLE;
			Arp::driveArp();
			Tcp::drivePackets();
		}
	} else {
		if (sendfile != NULL) {
			fclose(sendfile);
		}
		//closesocket(sock);
	}
}

void conf_recv_reset(char* fname, FILE* recvfile) {
	if (recvfile != NULL) {
		fclose(recvfile);
	}
	recvfile = fopen(fname, "wb");
}

void conf_recv_work(int sock, FILE* recvfile) {
	if (recvfile == NULL) {
		closesocket(sock);
		return;
	}
	
	int len;
	if (tcpsock[sock]->recvDataWaiting() == true) {
		len = recv(sock, conftmp, 128, 0);
		if (len > 0) {
			fwrite(conftmp, 1, len, recvfile);
		}
	}	
}
