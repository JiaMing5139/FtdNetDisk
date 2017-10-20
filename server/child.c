#include "func.h"

void child_handle(int fdr)
{
		char content[20];
		char flag=1;
		int new_fd;
		int ret;
		int len;
		int ctl;
		train t;
		memset(&t,0,sizeof(t));
		while(1)
		{
				
				recv_fd(fdr,&new_fd);//从父进程接收任
				//user u;	
				//recv(new_fd,&t,sizeof(t),0);
				//printf("len%d ctl%d buf%s\n",t.len,t.ctl,t.buf);
				printf("link success new fd get\n");
				chdir("filepool");
				while(1)
				{
			
					ret=recv_msg(new_fd);
					if(-1==ret)
					break;
						//printf("ctl=%d len=%d content=%s\n",ctl,len,content);
				}
		printf("通知父进程，完成发送任务\n");
		write(fdr,&flag,sizeof(flag));//通知父进程，完成发送任务

		}
}
void sig(int sigsum)
{
printf("i am sigpipe\n");
}
void make_child(pchild p,int num)
{
		int i;
		int fds[2];
		pid_t pid;
		for(i=0;i<num;i++)//创建多个子进程
		{
				socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
				pid=fork();
				if(0==pid)
				{
						signal(SIGPIPE,sig);
						close(fds[1]);
						child_handle(fds[0]);
				}
				close(fds[0]);
				p[i].pid=pid;//子进程的pid
				p[i].tfds=fds[1];//拿到管道的一端
				p[i].busy=0;//子进程处于空闲状态
		}
}
