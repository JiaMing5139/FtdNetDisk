#include"func.h"

void send_msg(int sfd,char *tmpbuf)
{
		train t;
		off_t ex;
		int ret;
		char b[10];
		char buf[30];
		memset(&t,0,sizeof(t));
		//printf("t.len=%d\n",t.len);
		memset(b,0,sizeof(b));
		memset(buf,0,sizeof(buf));
		sscanf(tmpbuf,"%s %s",b,buf);
		printf("命令:%s内容:%s\n",b,buf);
		if(0==strcmp(b,"cd"))
				t.ctl=1;
		else if(0==strcmp(b,"pwd"))
				t.ctl=2;
		else if(0==strcmp(b,"ls"))
				t.ctl=3;
		else if(0==strcmp(b,"remove"))
				t.ctl=4;
		else if(0==strcmp(b,"gets"))
				t.ctl=5;
		else if(0==strcmp(b,"puts"))
				{t.ctl=6;
				send_file(sfd,tmpbuf);
				return;
				}
		else if(0==strcmp(b,"mkdir"))
				t.ctl=9;
		else if(0==strcmp(b,"int"))
				t.ctl=99;
		else {
				printf("输入命令有误，请重新输入\n");
				return; 
		}
		strcpy(t.buf,buf);
		t.len=strlen(t.buf);	
		if(t.ctl==5)
    	{
		struct stat s;
		ret=stat(t.buf,&s);
		if(-1==ret) ex=0;
			else ex=s.st_size;
		}
//		(long int)*(&t+t.len+4)=ex;
//		printf("额外发送文件存在大小:%ld\n",(long int)*(t+t.len+4));	
//		printf("打包完成:t.len=%d t.ctl=%d t.buf=%s\n",t.len,t.ctl,t.buf);
//		send_n(sfd,&t,16+t.len);
//		}
//		else
//	{	

		printf("打包完成:t.len=%d t.ctl=%d t.buf=%s\n",t.len,t.ctl,t.buf);	
		send_n(sfd,(char *)&t,8+t.len);
		if(t.ctl==5)
		{
		send_n(sfd,(char *)&ex,8);
		}
		
//	}
	
}
int send_usrinfo(int sfd,char *account,char *salt,char *cryp)
{
train t;
memset(&t,0,sizeof(t));
t.ctl=7;
sprintf(t.buf,"%s %s %s",account,salt,cryp);
t.len=strlen(t.buf);
printf("用户信息打包完成:t.len=%d t.ctl=%d t.buf=%s\n",t.len,t.ctl,t.buf);
send_n(sfd,(char *)&t,8+t.len);
return 0;
}

int recv_msg(int sfd)
{
		int ret;
		char content[1000];
		memset(content,0,sizeof(content));
		int len=0;
		int ctl=0;
		int fd;
		printf("收到数据包的到来\n");
		recv_n(sfd,(char *)&len,4);
		printf("recv_msg:len=%d\n",len);
		recv_n(sfd,(char *)&ctl,4);
		printf("recv_msg:ctl=%d\n",ctl);
		if(-1!=ctl)
		{
				switch(ctl)
				{
						case 1:{
									   memset(content,0,sizeof(content));
									   recv_n(sfd,content,len);
										if(!strlen(content)) printf("目录为空\n");
									  else  printf("从服务器收到:\n%s\n",content);

							   };break;
						case 2:{
											
									   off_t fsize;
									   memset(content,0,sizeof(content));
									   recv_n(sfd,content,len);
									   printf("从服务器收到:\n%s\n",content);
									   int fd1,fd2;
									   int total=0;	
									   fd1=open(content,O_CREAT|O_WRONLY,0666);
									   fd2=open(content,O_WRONLY,0666);
									   printf("文件创建成功\n");
										recv_n(sfd,(char *)&fsize,8);
										printf("文件大小为%ld\n",fsize);
										char md5[33]={0};
										recv_n(sfd,md5,32);
										printf("文件的md5码为:%s",md5);
										off_t start =fsize/2;
										int sfd1,sfd2;
										char ipadress[20]="127.0.0.1";
										int port=3001;
										sfd1=sfd_generate(ipadress,port);										
										printf("msghadle:sfd=%d\n",sfd1);

										printf("start=%ld fsize-start=%ld\n",start, fsize-start);
							    		send_signal(sfd,0,start,md5);
										send_signal(sfd1,start,fsize-start,md5);


                                        int epfd=epoll_create(1);
                                    	struct epoll_event event,evs[4];
                                    	memset(&event,0,sizeof(event));
                                        memset(&evs,0,sizeof(evs));
                                    	event.events=EPOLLIN;
                                    	event.data.fd=sfd;
                                    	epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
                                        event.events=EPOLLIN;
                                    	event.data.fd=sfd1;
										epoll_ctl(epfd,EPOLL_CTL_ADD,sfd1,&event);
										printf("注册成功\n");
										lseek(fd2,start,SEEK_SET);
										int ret1=0;
										int i=0;
                                      	while(1)
                                      	{
                                      		memset(evs,0,sizeof(evs));
										//	printf("等待数据...\n");
                                      		ret1=epoll_wait(epfd,evs,2,-1);
											if(total>=2) break;
                                      		for(i=0;i<ret1;i++)
                                      		{
                                      		if(evs[i].data.fd==sfd)
                                      			{
												printf("sfd get\n");
											   recv_n(sfd,(char *)&len,4);
											   recv_n(sfd,(char *)&ctl,4);
											   if(ctl>0)
											   {
													   memset(content,0,sizeof(content));
													   recv_n(sfd,content,len);
													//	printf("sfd写入%s\n",content);
													   write(fd1,content,len);
												}
												else{
                                    					event.events=EPOLLIN;
                                    					event.data.fd=sfd;
                                    					epoll_ctl(epfd,EPOLL_CTL_DEL,sfd,&event);
														close(sfd);	
														 total++;
													}
                                      			}	
                                      		if(evs[i].data.fd==sfd1)
                                      			{
												 printf("sfd1 get\n");
											   recv_n(sfd1,(char *)&len,4);
											   recv_n(sfd1,(char *)&ctl,4);
											   if(ctl>=0)
											   {
													   memset(content,0,sizeof(content));
													   recv_n(sfd1,content,len);
													//	printf("sfd1写入%s\n",content);
													   write(fd2,content,len);
												}
												else{
                                        				event.events=EPOLLIN;
                                    					event.data.fd=sfd1;
														epoll_ctl(epfd,EPOLL_CTL_DEL,sfd1,&event);
														close(sfd1);
														 total++;
													}
                                      			}
                                      		}
                                      	}
										
										



						//				printf("发送信号成功\n");
							//			send_signal(sfd2,0,50);
							//		    time_t now,check;
							//			time(&now);
							//			check=now;
							//			off_t ex;
							//			struct stat s;
							//			ret=stat(content,&s);
							//			if(-1==ret) ex=0;
							//			else ex=s.st_size;
							//			long l=ex;
									//   while(1)
									//   {
									//		   //printf("正在接受文件\n");
									//		   recv_n(sfd,(char *)&len,4);
									//			l=l+len;
									//		   recv_n(sfd,(char *)&ctl,4);
									//			//printf("len=%d,ctl=%d",len,ctl);	
									//		   if(ctl>0)
									//		   {
									//				   memset(content,0,sizeof(content));
									//				   recv_n(sfd,content,len);
									//				   write(fd,content,len);
									//					time(&now);
									//					if(now>=check+1)
									//					{
									//							printf("Now Data %5.2f%s\r",(double)l*100/fsize,"%");
									//							fflush(stdout);
									//							check=now;
									//					}
									//		   }else{
									//					printf("Now Data %5.2f%s\n",(double)l*100/fsize,"%");
									//					printf("down  load  success\n");
									//				   break;
									//		   }
									//    }


							   };break;

				}

		}
		return 0;

}


 			int send_file(int new_fd,char *tmpbuf)
         {
				int flag;
				char tmp[50];
				char md5[33];
				char b[10];
				char name[30];
                train t;
                memset(&t,0,sizeof(t));
				memset(md5,0,33);
				memset(b,0,10);
				memset(name,0,30);
				memset(tmp,0,sizeof(tmp));
				
                 int ret;
				 sscanf(tmpbuf,"%s %s",b,name);
				 ret=Compute_file_md5(name,md5);	
				if(-1==ret)
				{
					printf("无此文件\n");
					return -1;
				}
				sprintf(tmp,"%s %s",md5,name);
                 strcpy(t.buf,tmp);
                 t.len=strlen(t.buf);
                 t.ctl=6;
                 printf("打包完成:t.len=%d t.ctl=%d t.buf=%s\n",t.len,t.ctl,t.buf);
                 ret=send_n(new_fd,(char *)&t,8+t.len);
                 if(-1==ret)
                 {
                         perror("send");
                         return -1;
                 }
				recv_n(new_fd,(char *)&flag,4);
				if(1==flag) 
				{
				printf("服务器已经存在该文件\n");
				return 0;
				}
                 int fd;
                 fd=open(name,O_RDONLY);
                 if(-1==fd)
                 {
                         perror("open");
                         return -1;
                 }
                 while(memset(&t,0,sizeof(t)),(t.len=read(fd,t.buf,sizeof(t.buf)))>0)
                 {
                         t.ctl=6;
                         send_n(new_fd,(char *)&t,8+t.len);
                 }
                 t.len=0;
                 t.ctl=-1;
                 send_n(new_fd,(char *)&t,8+t.len);
						
         }
int send_signal(int sfd,off_t start,off_t length,char *md5)
{
train t;
memset(&t,0,sizeof(t));
t.ctl=36;
char tmp[100];
memset(tmp,0,sizeof(tmp));
sprintf(tmp,"%d %d %s",start,length,md5);
printf("tmp:%s\n",tmp);
strcpy(t.buf,tmp);
t.len=strlen(t.buf);
printf("sfd=%d用户信息打包完成:t.len=%d t.ctl=%d t.buf=%s\n",sfd,t.len,t.ctl,t.buf);
send_n(sfd,(char *)&t,8+t.len);
}


