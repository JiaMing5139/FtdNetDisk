#include"func.h"
int sfd_generate(char *ipadress,int port)
{
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("socket");
		return -1;
	}
	printf("ip=%s id=%d\n",ipadress,port);
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(port);
	ser.sin_addr.s_addr=inet_addr(ipadress);
	int ret;
	ret=connect(sfd,(struct sockaddr*)&ser,sizeof(ser));
	return sfd;
}
