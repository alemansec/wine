/* WINSOCK.H--definitions to be used with the WINSOCK.DLL
 *
 * This header file corresponds to version 1.1 of the Windows Sockets
 * specification.
 */

#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_

#ifndef RC_INVOKED
#include <sys/types.h>

/* Solaris uses these macro names */
#undef FSHIFT
#undef TRANSPARENT
#include <netinet/in.h>
/* Restore the Windows values */
#ifdef _WINUSER_
#undef FSHIFT
#define FSHIFT            0x04
#endif
#ifdef _WINGDI_
#undef TRANSPARENT
#define TRANSPARENT       1
#endif

#include <arpa/inet.h>
#include <sys/time.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#endif /* RC_INVOKED */

#include "windef.h"

#ifdef __cplusplus
extern "C" {
#endif /* defined(__cplusplus) */

/* no "forced" alignment of ws_XXXXent here ! */
	
typedef struct ws_hostent
{
        char    *h_name;        /* official name of host */
        char    **h_aliases;    /* alias list */
        short   h_addrtype;     /* host address type */
        short   h_length;       /* length of address */
        char    **h_addr_list;  /* list of addresses from name server */
} _ws_hostent;

typedef struct ws_protoent
{
        char    *p_name;        /* official protocol name */
        char    **p_aliases;    /* alias list */
        short   p_proto;        /* protocol # */
} _ws_protoent;

typedef struct ws_servent 
{
        char    *s_name;        /* official service name */
        char    **s_aliases;    /* alias list */
        short   s_port;         /* port # */
        char    *s_proto;       /* protocol to use */
} _ws_servent;

typedef struct ws_netent
{
        char    *n_name;        /* official name of net */
        char    **n_aliases;    /* alias list */
        short   n_addrtype;     /* net address type */
        u_long  n_net;          /* network # */
} _ws_netent;

#include "pshpack1.h"

typedef UINT		SOCKET;

typedef struct sockaddr		ws_sockaddr;

typedef struct ws_fd_set32_struct
{
        UINT    fd_count;               /* how many are SET? */
        SOCKET  fd_array[FD_SETSIZE];   /* an array of SOCKETs */
} ws_fd_set32;


/* ws_fd_set operations */

INT WINAPI __WSAFDIsSet( SOCKET, ws_fd_set32 * );

#define __WS_FD_CLR(fd, set, cast) do { \
    UINT __i; \
    for (__i = 0; __i < ((cast*)(set))->fd_count ; __i++) \
    { \
        if (((cast*)(set))->fd_array[__i] == fd) \
	{ \
            while (__i < ((cast*)(set))->fd_count-1) \
	    { \
                ((cast*)(set))->fd_array[__i] = \
                    ((cast*)(set))->fd_array[__i+1]; \
                __i++; \
            } \
            ((cast*)(set))->fd_count--; \
            break; \
        } \
    } \
} while(0)
#define WS_FD_CLR(fd, set)	__WS_FD_CLR((fd),(set), ws_fd_set32)

#define __WS_FD_SET(fd, set, cast) do { \
    if (((cast*)(set))->fd_count < FD_SETSIZE) \
        ((cast*)(set))->fd_array[((cast*)(set))->fd_count++]=(fd);\
} while(0)
#define WS_FD_SET(fd, set)    __WS_FD_SET((fd),(set), ws_fd_set32)
#define WS_FD_ZERO(set) (((ws_fd_set32*)(set))->fd_count=0)
#define WS_FD_ISSET(fd, set) __WSAFDIsSet((SOCKET)(fd), (ws_fd_set32*)(set))

/* 
 * Internet address (old style... should be updated) 
 */

struct ws_in_addr
{
        union {
                struct { BYTE   s_b1,s_b2,s_b3,s_b4; } S_un_b;
                struct { WORD   s_w1,s_w2; } S_un_w;
                UINT S_addr;
        } S_un;
#define ws_addr  S_un.S_addr		/* can be used for most tcp & ip code */
#define ws_host  S_un.S_un_b.s_b2	/* host on imp */
#define ws_net   S_un.S_un_b.s_b1	/* network */
#define ws_imp   S_un.S_un_w.s_w2	/* imp */
#define ws_impno S_un.S_un_b.s_b4	/* imp # */
#define ws_lh    S_un.S_un_b.s_b3	/* logical host */
};

struct ws_sockaddr_in
{
        SHORT		sin_family;
        WORD 		sin_port;
        struct ws_in_addr sin_addr;
        BYTE    	sin_zero[8];
};

#define WSADESCRIPTION_LEN      256
#define WSASYS_STATUS_LEN       128

typedef struct WSAData {
        WORD                    wVersion;
        WORD                    wHighVersion;
        char                    szDescription[WSADESCRIPTION_LEN+1];
        char                    szSystemStatus[WSASYS_STATUS_LEN+1];
        WORD                    iMaxSockets;
        WORD                    iMaxUdpDg;
        SEGPTR			lpVendorInfo;
} WSADATA, *LPWSADATA;

#include "poppack.h"

/*
 * This is used instead of -1, since the
 * SOCKET type is unsigned.
 */
#define INVALID_SOCKET 	   (~0)
#define SOCKET_ERROR               (-1)


/*
 * Types
 */
#define WS_SOCK_STREAM     1               /* stream socket */
#define WS_SOCK_DGRAM      2               /* datagram socket */
#define WS_SOCK_RAW        3               /* raw-protocol interface */
#define WS_SOCK_RDM        4               /* reliably-delivered message */
#define WS_SOCK_SEQPACKET  5               /* sequenced packet stream */

#define WS_SOL_SOCKET		0xffff
#define WS_IPPROTO_TCP		6

/*
 * Option flags per-socket.
 */
#define WS_SO_DEBUG        0x0001          /* turn on debugging info recording */
#define WS_SO_ACCEPTCONN   0x0002          /* socket has had listen() */
#define WS_SO_REUSEADDR    0x0004          /* allow local address reuse */
#define WS_SO_KEEPALIVE    0x0008          /* keep connections alive */
#define WS_SO_DONTROUTE    0x0010          /* just use interface addresses */
#define WS_SO_BROADCAST    0x0020          /* permit sending of broadcast msgs */
#define WS_SO_USELOOPBACK  0x0040          /* bypass hardware when possible */
#define WS_SO_LINGER       0x0080          /* linger on close if data present */
#define WS_SO_OOBINLINE    0x0100          /* leave received OOB data in line */

#define WS_SO_DONTLINGER   (UINT)(~WS_SO_LINGER)

/*
 * Additional options.
 */
#define WS_SO_SNDBUF       0x1001          /* send buffer size */
#define WS_SO_RCVBUF       0x1002          /* receive buffer size */
#define WS_SO_SNDLOWAT     0x1003          /* send low-water mark */
#define WS_SO_RCVLOWAT     0x1004          /* receive low-water mark */
#define WS_SO_SNDTIMEO     0x1005          /* send timeout */
#define WS_SO_RCVTIMEO     0x1006          /* receive timeout */
#define WS_SO_ERROR        0x1007          /* get error status and clear */
#define WS_SO_TYPE         0x1008          /* get socket type */

#define WS_IOCPARM_MASK    0x7f            /* parameters must be < 128 bytes */
#define WS_IOC_VOID        0x20000000      /* no parameters */
#define WS_IOC_OUT         0x40000000      /* copy out parameters */
#define WS_IOC_IN          0x80000000      /* copy in parameters */
#define WS_IOC_INOUT       (WS_IOC_IN|WS_IOC_OUT)
#define WS_IOR(x,y,t)      (WS_IOC_OUT|(((UINT)sizeof(t)&WS_IOCPARM_MASK)<<16)|((x)<<8)|(y))
#define WS_IOW(x,y,t)      (WS_IOC_IN|(((UINT)sizeof(t)&WS_IOCPARM_MASK)<<16)|((x)<<8)|(y))

/* IPPROTO_TCP options */
#define WS_TCP_NODELAY	1		/* do not apply nagle algorithm */

/*
 * Socket I/O flags (supported by spec 1.1)
 */

#define WS_FIONREAD    WS_IOR('f', 127, u_long)
#define WS_FIONBIO     WS_IOW('f', 126, u_long)

#define WS_SIOCATMARK  WS_IOR('s',  7, u_long)

/*
 * Maximum queue length specifiable by listen.
 */
#ifdef SOMAXCONN
#undef SOMAXCONN
#endif
#define SOMAXCONN       5

#ifndef MSG_DONTROUTE
#define MSG_DONTROUTE   0x4             /* send without using routing tables */
#endif
#define MSG_MAXIOVLEN   16

#ifndef MSG_PARTIAL
#define MSG_PARTIAL     0x8000 /* partial send or recv (WSARecvEx) */
#endif

/*
 * Define constant based on rfc883, used by gethostbyxxxx() calls.
 */
#define MAXGETHOSTSTRUCT        1024

/*
 * Define flags to be used with the WSAAsyncSelect() call.
 */
#define FD_READ            WS_FD_READ
#define FD_WRITE           WS_FD_WRITE
#define FD_OOB             WS_FD_OOB
#define FD_ACCEPT          WS_FD_ACCEPT
#define FD_CONNECT         WS_FD_CONNECT
#define FD_CLOSE           WS_FD_CLOSE
#define WS_FD_READ         0x0001
#define WS_FD_WRITE        0x0002
#define WS_FD_OOB          0x0004
#define WS_FD_ACCEPT       0x0008
#define WS_FD_CONNECT      0x0010
#define WS_FD_CLOSE        0x0020

#define WS_FD_LISTENING	   0x10000000	/* internal per-socket flags */
#define WS_FD_NONBLOCKING  0x20000000
#define WS_FD_CONNECTED	   0x40000000
#define WS_FD_RAW	   0x80000000
#define WS_FD_SERVEVENT	   0x01000000
#define WS_FD_INTERNAL	   0xFFFF0000

/*
 * All Windows Sockets error constants are biased by WSABASEERR from
 * the "normal"
 */
#define WSABASEERR              10000
/*
 * Windows Sockets definitions of regular Microsoft C error constants
 */
#define WSAEINTR                (WSABASEERR+4)
#define WSAEBADF                (WSABASEERR+9)
#define WSAEACCES               (WSABASEERR+13)
#define WSAEFAULT               (WSABASEERR+14)
#define WSAEINVAL               (WSABASEERR+22)
#define WSAEMFILE               (WSABASEERR+24)

/*
 * Windows Sockets definitions of regular Berkeley error constants
 */
#define WSAEWOULDBLOCK          (WSABASEERR+35)
#define WSAEINPROGRESS          (WSABASEERR+36)
#define WSAEALREADY             (WSABASEERR+37)
#define WSAENOTSOCK             (WSABASEERR+38)
#define WSAEDESTADDRREQ         (WSABASEERR+39)
#define WSAEMSGSIZE             (WSABASEERR+40)
#define WSAEPROTOTYPE           (WSABASEERR+41)
#define WSAENOPROTOOPT          (WSABASEERR+42)
#define WSAEPROTONOSUPPORT      (WSABASEERR+43)
#define WSAESOCKTNOSUPPORT      (WSABASEERR+44)
#define WSAEOPNOTSUPP           (WSABASEERR+45)
#define WSAEPFNOSUPPORT         (WSABASEERR+46)
#define WSAEAFNOSUPPORT         (WSABASEERR+47)
#define WSAEADDRINUSE           (WSABASEERR+48)
#define WSAEADDRNOTAVAIL        (WSABASEERR+49)
#define WSAENETDOWN             (WSABASEERR+50)
#define WSAENETUNREACH          (WSABASEERR+51)
#define WSAENETRESET            (WSABASEERR+52)
#define WSAECONNABORTED         (WSABASEERR+53)
#define WSAECONNRESET           (WSABASEERR+54)
#define WSAENOBUFS              (WSABASEERR+55)
#define WSAEISCONN              (WSABASEERR+56)
#define WSAENOTCONN             (WSABASEERR+57)
#define WSAESHUTDOWN            (WSABASEERR+58)
#define WSAETOOMANYREFS         (WSABASEERR+59)
#define WSAETIMEDOUT            (WSABASEERR+60)
#define WSAECONNREFUSED         (WSABASEERR+61)
#define WSAELOOP                (WSABASEERR+62)
#define WSAENAMETOOLONG         (WSABASEERR+63)
#define WSAEHOSTDOWN            (WSABASEERR+64)
#define WSAEHOSTUNREACH         (WSABASEERR+65)
#define WSAENOTEMPTY            (WSABASEERR+66)
#define WSAEPROCLIM             (WSABASEERR+67)
#define WSAEUSERS               (WSABASEERR+68)
#define WSAEDQUOT               (WSABASEERR+69)
#define WSAESTALE               (WSABASEERR+70)
#define WSAEREMOTE              (WSABASEERR+71)

/*
 * Extended Windows Sockets error constant definitions
 */
#define WSASYSNOTREADY          (WSABASEERR+91)
#define WSAVERNOTSUPPORTED      (WSABASEERR+92)
#define WSANOTINITIALISED       (WSABASEERR+93)

/*
 * Error return codes from gethostbyname() and gethostbyaddr()
 * (when using the resolver). Note that these errors are
 * retrieved via WSAGetLastError() and must therefore follow
 * the rules for avoiding clashes with error numbers from
 * specific implementations or language run-time systems.
 * For this reason the codes are based at WSABASEERR+1001.
 * Note also that [WSA]NO_ADDRESS is defined only for
 * compatibility purposes.
 */

/* #define h_errno         WSAGetLastError() */

/* Authoritative Answer: Host not found */
#define WSAHOST_NOT_FOUND       (WSABASEERR+1001)

/* Non-Authoritative: Host not found, or SERVERFAIL */
#define WSATRY_AGAIN            (WSABASEERR+1002)

/* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
#define WSANO_RECOVERY          (WSABASEERR+1003)

/* Valid name, no data record of requested type */
#define WSANO_DATA              (WSABASEERR+1004)

/* no address, look for MX record */
#define WSANO_ADDRESS           WSANO_DATA

/* Socket function prototypes */

#ifdef __cplusplus
extern "C" {
#endif

/* Microsoft Windows Extension function prototypes */

INT     WINAPI WSAStartup(UINT wVersionRequired, LPWSADATA lpWSAData);
void      WINAPI WSASetLastError(INT iError);
INT     WINAPI WSACleanup(void);
INT     WINAPI WSAGetLastError(void);
BOOL    WINAPI WSAIsBlocking(void);
INT     WINAPI WSACancelBlockingCall(void);
INT     WINAPI WSAUnhookBlockingHook(void);
FARPROC WINAPI WSASetBlockingHook(FARPROC lpBlockFunc);
HANDLE  WINAPI WSAAsyncGetServByName(HWND hWnd, UINT uMsg, LPCSTR name, LPCSTR proto,
					 LPSTR sbuf, INT buflen);
HANDLE  WINAPI WSAAsyncGetServByPort(HWND hWnd, UINT uMsg, INT port,
					 LPCSTR proto, LPSTR sbuf, INT buflen);
HANDLE  WINAPI WSAAsyncGetProtoByName(HWND hWnd, UINT uMsg,
					  LPCSTR name, LPSTR sbuf, INT buflen);
HANDLE  WINAPI WSAAsyncGetProtoByNumber(HWND hWnd, UINT uMsg,
					    INT number, LPSTR sbuf, INT buflen);
HANDLE  WINAPI WSAAsyncGetHostByName(HWND hWnd, UINT uMsg,
					 LPCSTR name, LPSTR sbuf, INT buflen);
HANDLE  WINAPI WSAAsyncGetHostByAddr(HWND hWnd, UINT uMsg, LPCSTR addr,
			      INT len, INT type, LPSTR sbuf, INT buflen);
INT     WINAPI WSACancelAsyncRequest(HANDLE hAsyncTaskHandle);
INT     WINAPI WSAAsyncSelect(SOCKET s, HWND hWnd, UINT uMsg, LONG lEvent);
INT     WINAPI   WSARecvEx(SOCKET s, char *buf, INT len, INT *flags);

/*
 * Address families
 */
#define WS_AF_UNSPEC       0               /* unspecified */
#define WS_AF_UNIX         1               /* local to host (pipes, portals) */
#define WS_AF_INET         2               /* internetwork: UDP, TCP, etc. */
#define WS_AF_IMPLINK      3               /* arpanet imp addresses */
#define WS_AF_PUP          4               /* pup protocols: e.g. BSP */
#define WS_AF_CHAOS        5               /* mit CHAOS protocols */
#define WS_AF_NS           6               /* XEROX NS protocols */
#define WS_AF_IPX          WS_AF_NS        /* IPX protocols: IPX, SPX, etc. */
#define WS_AF_ISO          7               /* ISO protocols */
#define WS_AF_OSI          AF_ISO          /* OSI is ISO */
#define WS_AF_ECMA         8               /* european computer manufacturers */
#define WS_AF_DATAKIT      9               /* datakit protocols */
#define WS_AF_CCITT        10              /* CCITT protocols, X.25 etc */
#define WS_AF_SNA          11              /* IBM SNA */
#define WS_AF_DECnet       12              /* DECnet */
#define WS_AF_DLI          13              /* Direct data link interface */
#define WS_AF_LAT          14              /* LAT */
#define WS_AF_HYLINK       15              /* NSC Hyperchannel */
#define WS_AF_APPLETALK    16              /* AppleTalk */
#define WS_AF_NETBIOS      17              /* NetBios-style addresses */
#define WS_AF_VOICEVIEW    18              /* VoiceView */
#define WS_AF_FIREFOX      19              /* Protocols from Firefox */
#define WS_AF_UNKNOWN1     20              /* Somebody is using this! */
#define WS_AF_BAN          21              /* Banyan */
#define WS_AF_ATM          22              /* Native ATM Services */
#define WS_AF_INET6        23              /* Internetwork Version 6 */
#define WS_AF_CLUSTER      24              /* Microsoft Wolfpack */
#define WS_AF_12844        25              /* IEEE 1284.4 WG AF */
#define WS_AF_IRDA         26              /* IrDA */

#define WS_AF_MAX          27

#include "pshpack1.h"

struct ws_sockaddr_ipx
{
	SHORT		sipx_family;
	UINT		sipx_network;
	CHAR		sipx_node[6];
	WORD		sipx_port;
};

#include "poppack.h"

#ifdef __cplusplus
}
#endif

/* Microsoft Windows Extended data types */
typedef struct sockaddr SOCKADDR, *PSOCKADDR, *LPSOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN, *PSOCKADDR_IN, *LPSOCKADDR_IN;
typedef struct linger LINGER, *PLINGER, *LPLINGER;
typedef struct in_addr IN_ADDR, *PIN_ADDR, *LPIN_ADDR;
typedef struct ws_fd_set32_struct FD_SET, *PFD_SET, *LPFD_SET;
typedef struct hostent HOSTENT, *PHOSTENT, *LPHOSTENT;
typedef struct servent SERVENT, *PSERVENT, *LPSERVENT;
typedef struct protoent PROTOENT, *PPROTOENT, *LPPROTOENT;
typedef struct timeval TIMEVAL, *PTIMEVAL, *LPTIMEVAL;

/*
 * Windows message parameter composition and decomposition
 * macros.
 *
 * WSAMAKEASYNCREPLY is intended for use by the Windows Sockets implementation
 * when constructing the response to a WSAAsyncGetXByY() routine.
 */
#define WSAMAKEASYNCREPLY(buflen,error)     MAKELONG(buflen,error)
/*
 * WSAMAKESELECTREPLY is intended for use by the Windows Sockets implementation
 * when constructing the response to WSAAsyncSelect().
 */
#define WSAMAKESELECTREPLY(event,error)     MAKELONG(event,error)
/*
 * WSAGETASYNCBUFLEN is intended for use by the Windows Sockets application
 * to extract the buffer length from the lParam in the response
 * to a WSAGetXByY().
 */
#define WSAGETASYNCBUFLEN(lParam)           LOWORD(lParam)
/*
 * WSAGETASYNCERROR is intended for use by the Windows Sockets application
 * to extract the error code from the lParam in the response
 * to a WSAGetXByY().
 */
#define WSAGETASYNCERROR(lParam)            HIWORD(lParam)
/*
 * WSAGETSELECTEVENT is intended for use by the Windows Sockets application
 * to extract the event code from the lParam in the response
 * to a WSAAsyncSelect().
 */
#define WSAGETSELECTEVENT(lParam)           LOWORD(lParam)
/*
 * WSAGETSELECTERROR is intended for use by the Windows Sockets application
 * to extract the error code from the lParam in the response
 * to a WSAAsyncSelect().
 */
#define WSAGETSELECTERROR(lParam)           HIWORD(lParam)

#ifdef __cplusplus
} /* extern "C" */
#endif /* defined(__cplusplus) */

#endif  /* _WINSOCKAPI_ */

