#include <stdio.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <sl/arg.h>

char *argv0;
static int af = AF_INET ;

void
usage(void)
{
	fprintf(stderr, "usage: %s [-n|-b|-6]\n", argv0);
}

int
main(int argc, char **argv)
{
	struct ifaddrs *ifabuf, *ifa;
	char buf[32] = { 0 };
	struct sockaddr_in *sa;
	char *ipstr;

	argv0 = argv[0] ;
	ARGBEGIN {
	case 'n' :
		af = AF_INET ;
		break;
	case '6' :
		af = AF_INET6 ;
		break;
	default:
		usage();
	} ARGEND ;

	if( getifaddrs(&ifabuf) == -1 ){
		perror("getifaddrs");
		exit(1);
	}

	for(ifa = ifabuf ; ifa ; ifa = ifa->ifa_next){
		if(!ifa->ifa_addr ||
				ifa->ifa_addr->sa_family != af )
			continue;
		sa = (struct sockaddr_in *)ifa->ifa_addr ;
		ipstr = inet_ntoa(sa->sin_addr) ;
		printf("%s %s\n", ifa->ifa_name, ipstr);
	}

	return 0 ;
}

