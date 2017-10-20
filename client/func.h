#include <strings.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#define _XOPEN_SOURCE
typedef struct{
char ipadress[20];
int port;
off_t startplace;
off_t num;
}dd;
typedef struct{
	pid_t pid;//子进程的pid
	int tfds;//通过该管道传递内核控制信息
	short busy;//标示进程是否忙碌
}child,*pchild;
typedef struct{
	int len;	
	int ctl;
	char buf[1000];
}train,*ptrain;

typedef struct{
	int len;	
	int ctl;
	off_t dl;
	off_t wl;
	char buf[1000];
}trainf,*ptrainf;
int send_n(int sfd,char* p,int len);
int recv_n(int sfd,char* p,int len);
void send_msg(int sfd,char *tmpbuf);
int recv_msg(int sfd);
int send_file(int new_fd,char *name);
void login_view(int sfd);
int send_usrinfo(int sfd,char *account,char *salt,char *cryp);
int md5get(char *fname,char *md5); 
int Compute_file_md5(const char *file_path, char *value);  
int send_signal(int sfd,off_t start,off_t lengthi,char *md5);


