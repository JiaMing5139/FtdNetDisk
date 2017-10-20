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
#include <mysql/mysql.h>
#include <sys/mman.h>
#define FILENAME "file"
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
    int workpath;
	char usr[20];
	char route[100];
	int num_file;
}user,*puser;
typedef struct{
	char pname[20];
	char type[5];
	char time[50];
}ls_list;
void make_child(pchild p,int num);
int recv_msg(int sfd);
void send_msg(int sfd,char *tmpbuf);
int send_file(int new_fd,char *name,user u);
int insert(int id,char *log);
int insert_usr(char *account,char *salt,char *cryp);
void ls(char *);
int select_salt(char *account,char *salt);
int select_crypt(char *account,char *crypt);
int insert_dir(char *user,int ppre,int pcurrent,char *name);
int select_cd(char *pname,int workplace,char  *pcurrent);
int select_num(char *pname);
void init_usr(user *u,char *account);
int select_ppre(char *pname,int workplace,char *ppre); //48row
void backdir(char *dir,char *pdir);
int select_ls(int workplace,char *lslist,char *account); //48row
int insert_file(char *account,int ppre,int pcurrent,char *name,char *md5);
int iffileexist(char *md5);
int abletocd(int ppre,char *pname,char * account);
int select_md5(int pcurrent,char *name,char *md5,char *account); //48row
int mmap_send(int new_fd,char *md5_dpoint,off_t start,off_t lengths);
int select_rm(char *pname,int workplace); //48row
int ifaccountexist(char *account);
//int send_n(int sfd,char* p,int len);
//int recv_n(int sfd,char* p,int len);
//void send_fd(int fdw,int fd);
//void send_fd(int fdw,int *fd);

