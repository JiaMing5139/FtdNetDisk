#include "func.h"
int rip[2];

void sig(int signum)
{
printf("bb\n");
int flag=1;
write(rip[1],&flag,1);
//exit(0);
}

int main(int argc,char* argv[])
{
	signal(SIGINT,sig);
	pipe(rip);
	//printf("rip:%d %d\n",rip[0],rip[1]);
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret;
	ret=connect(sfd,(struct sockaddr*)&ser,sizeof(ser));
	if(-1==ret)
	{
		perror("connect");
		return -1;
	}
	login_view(sfd);
    int epfd=epoll_create(1);
	struct epoll_event event,evs[4];
	memset(&event,0,sizeof(event));
    memset(&evs,0,sizeof(evs));
	event.events=EPOLLIN;
	event.data.fd=sfd;
	epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
    event.events=EPOLLIN;
	event.data.fd=0;
	epoll_ctl(epfd,EPOLL_CTL_ADD,0,&event);
    event.events=EPOLLIN;
	event.data.fd=rip[0];
	epoll_ctl(epfd,EPOLL_CTL_ADD,rip[0],&event);
	int ret1;
	int i;
	char client_msg[20]={0};
	char server_msg[20]={0};
	char tmpbuf[30];
	//printf("rip:%d %d\n",rip[0],rip[1]);
	while(1)
	{
		memset(evs,0,sizeof(evs));
		ret1=epoll_wait(epfd,evs,4,-1);
		for(i=0;i<ret1;i++)
		{
	//	printf("evs[%d]:%d\n",i,evs[i].data.fd);
		if(evs[i].data.fd==0)
			{
				memset(tmpbuf,0,sizeof(tmpbuf));
				read(0,tmpbuf,sizeof(tmpbuf));
				send_msg(sfd,tmpbuf);
			}	
		if(evs[i].data.fd==sfd)
			{
				ret=recv_msg(sfd);
			}
			//else break;
		//printf("evs[0]:%d===rip[0]:%d\n",evs[i].data.fd,rip[0]);
		if(evs[i].data.fd==rip[0])
			{
			short flag;
			//read(rip[0],(char *)&flag,1);
			printf("收到中断新号哈哈哈\n");
			send_msg(sfd,"int");
			close(sfd);
			close(rip);
			exit(0);
			}

		}
	}


//	int len;
//	char buf[1000]={0};
//	int fd;
//	recv_n(sfd,(char *)&len,sizeof(len));
//	recv_n(sfd,buf,len);
//	fd=open(buf,O_CREAT|O_WRONLY,0666);
//	if(-1==fd)
//	{
//		perror("open");
//		return -1;
//	}
//	while(1)
//	{
//		recv_n(sfd,(char *)&len,sizeof(len));//接火车头
//		if(len>0)
//		{
//			memset(buf,0,sizeof(buf));
//			recv_n(sfd,buf,len);
//			write(fd,buf,len);
//		}else{
//			break;
//		}
//	}
//	close(fd);
//	close(sfd);
}
