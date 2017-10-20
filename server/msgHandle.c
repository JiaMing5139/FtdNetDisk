#include "func.h"
void ordergenerate(char *a,char *b,char *order);
int recv_msg(int sfd)
{		char order[50];
		memset(order,0,sizeof(order));
		char b[5];
		char buf[30];
		memset(b,0,sizeof(b));
		int ret=0;
		memset(buf,0,sizeof(buf));
		char content[1000];
		memset(content,0,sizeof(content));
		int len;
		int ctl;
		user u;
		memset(&u,0,sizeof(u));
		int num_file=1;
		while(1)
		{
				len=0;
				ctl=0;
				printf("等待数据包到来...\n");
				recv_n(sfd,(char *)&len,4);
				printf("recv_msg:len=%d\n",len);
				recv_n(sfd,(char *)&ctl,4);
				printf("recv_msg:ctl=%d\n",ctl);
				if(-1!=ctl)
				{
						switch(ctl)
						{
								case 36:{
										printf("多点下载线程专用\n");
											   memset(content,0,sizeof(content));
											   recv_n(sfd,content,len);
											   printf("content:%s\n",content);
												char starts[10];
												char lengths[10];
												off_t start;
												off_t length;
												char md5[33];
												memset(md5,0,33);
												memset(starts,0,10);
												memset(lengths,0,10);
												sscanf(content,"%s %s %s",starts,lengths,md5);
												printf("str:%s %s %s\n",starts,lengths,md5);
												start=atoi(starts);
												length=atoi(lengths);
												printf("start %ld  length %ld\n",start,length);
												mmap_send(sfd,md5,start,length);	
												//return -1;	
										
										};break;
								case 99:{
											printf("客户端已经关闭\n");
											return -1;
										}
								case 1:{printf("cd received\n");    //cd
											   memset(order,0,sizeof(order));
											   strcpy(order,"cd");
											   strcat(order," ");
											   memset(content,0,sizeof(content));
											   recv_n(sfd,content,len);

											   strcat(order,content);
											   printf("要存入数据库的日志为:%s\n",order);
											   insert(1,order);
											   printf("要进入的目录%s\n",content);

											   char  pcurrent[4];
											   char  ppre[4];
											   char  pname[50];
											   memset(pname,0,sizeof(pname));
											   memset(ppre,0,sizeof(ppre));
											   memset(pcurrent,0,sizeof(pcurrent));
											   if(0==strcmp(content,".."))
											   {
													   if(u.workpath==0)
													   {printf("已经是根目录\n");
														 send_msg(sfd,"已经是根目录");
														break;
													   }
													   select_ppre(u.usr,u.workpath,ppre);
													   u.workpath=atoi(ppre);
													   printf("当前的工作目录为%d\n",u.workpath);
													   char tmp[100]={0};
															   strcpy(tmp,u.route);
															   backdir(tmp,u.route);
															   printf("current route=%s",u.route);
													}

													   else {
															if(!abletocd(u.workpath,content,u.usr))
															{
															printf("无法进入");
											    			send_msg(sfd,"没有该目录");
															break;
															}
															   select_cd(content,u.workpath,pcurrent);
															   u.workpath=atoi(pcurrent);
															   printf("当前的工作目录为%d\n",u.workpath);
															   strcat(u.route,"/");
															   strcat(u.route,content);											
															   printf("current route=%s",u.route);
													   }


													   // ret=chdir(content);
													   // if(-1==ret)
													   //  	   perror("chdir");
													   // else printf("进入成功\n");
											   };break;
											   case 2:
											   {printf("pwd  received\n");
													   memset(content,0,sizeof(content));
													   recv_n(sfd,content,len);
													   memset(buf,0,sizeof(buf));
													   strcpy(buf,u.route);
													   ordergenerate("pwd",content,order);
													   printf("要存入数据库的日志为:%s\n",order);
													   insert(1,order);	
													   printf("当前目录：%s\n",buf);
													   send_msg(sfd,buf);

											   };break;
											   case 3:
											   {printf("ls received\n");
													   memset(content,0,sizeof(content));
													   recv_n(sfd,content,len);
													   char lsdir[1000];
													   memset(lsdir,0,sizeof(lsdir));
													   select_ls(u.workpath,lsdir,u.usr);
													   ordergenerate("ls",content,order);
													   printf("要存入数据库的日志为:%s\n",order);
													   insert(1,order);	
													   printf("%s",lsdir);
													   send_msg(sfd,lsdir);
											   };break;
											   case 4:
											   {printf("rm received\n");
													   memset(content,0,sizeof(content));
													   recv_n(sfd,content,len);
													   ordergenerate("rm",content,order);
													   printf("要存入数据库的日志为:%s\n",order);
													   insert(1,order);	
													   printf("要删除的目录%s\n",content);
														select_rm(content,u.workpath);	
											   };break;
											   case 5:
											   {printf("gets received\n");
													   memset(content,0,sizeof(content));
													   recv_n(sfd,content,len);
													   ordergenerate("gets",content,order);
													   printf("要存入数据库的日志为:%s\n",order);
													   insert(1,order);	
													   printf("客户端想下载:%s",content);
													   ret=send_file(sfd,content,u);
													   if(-1==ret) printf("无此文件\n");

											   };break;
											   case 6:
											   {
														char md5[33];
														char name[20];
														memset(name,0,sizeof(name));
														memset(md5,0,33);
													   printf("puts received\n");
													   memset(content,0,sizeof(content));
													   recv_n(sfd,content,len);
													   ordergenerate("puts",buf,order);
													   printf("要存入数据库的日志为:%s\n",order);
													   insert(1,order);	
													   printf("从客户端收到:\n%s\n",content);
														sscanf(content,"%s %s\n",md5,name);
														printf("文件名为:%s  md5:%s\n",name,md5);
														int flag=iffileexist(md5);
														printf("iffileexitst的返回值:%d",flag);
														if(1==flag)
														{
															send_n(sfd,(char *)&flag,4);
															printf("文件已经存在\n");
															u.num_file++;	
															printf("workpath:%d\n",u.workpath);
															insert_file(u.usr,u.workpath,u.num_file,name,md5);
															break;
											
														}
														send_n(sfd,(char *)&flag,4);
													   int  fd=open(md5,O_CREAT|O_WRONLY,0666);
													   //strcpy(md5,content);
													   printf("文件创建成功\n");
														printf("文件名为:%s  md5:%s\n",name,md5);
													   while(1)
													   {
															   printf("正在接受文件\n");
															   recv_n(sfd,(char *)&len,4);
															   recv_n(sfd,&ctl,4);
															   printf("len=%d,ctl=%d",len,ctl);
															   if(ctl>0)
															   {
																	   memset(content,0,sizeof(content));
																	   recv_n(sfd,content,len);
																	   write(fd,content,len);
															   }else{
															 			u.num_file++;	
																		printf("workpath:%d\n",u.workpath);
															  			insert_file(u.usr,u.workpath,u.num_file,name,md5);
																	   	break;
															   }
													   }

											   };break;
											   case 7:{
															  printf("用户信息注册\n");
															  memset(content,0,sizeof(content));
															  recv_n(sfd,content,len);
															  char account[20]={0};
															  char salt[9]={0};
															  char cryp[14]={0};
															  sscanf(content,"%s %s %s",account,salt,cryp);
															  printf("想要注册的信息为%s %s %s\n",account,salt,cryp);
																if(1==ifaccountexist(account)) 
																{
																	printf("用户已经存在\n");
																	send_msg(sfd,"用户名重复");
																	break;
																}
															  send_msg(sfd,"注册成功");
															  insert_usr(account,salt,cryp);
													  };break;
											   case 8:
													  {
															  int flag;
															  printf("用户登陆\n");
															  memset(content,0,sizeof(content));
															  recv_n(sfd,content,len);
															  printf("用户的登陆名为:%s\n",content);
															  char account[20];
															  char salt[9];
															  char cryp[14];
															  char crypc[14];
															  memset(account,0,sizeof(account));
															  memset(crypc,0,sizeof(crypc));
															  memset(salt,0,sizeof(salt));
															  memset(cryp,0,sizeof(cryp));
															  strcpy(account,content);
															  ret=select_salt(content,salt);
															  if(-1==ret)
															  {
																	  printf("ret没有此用户\n");
																	  flag=-1;
																	  send_n(sfd,(char *)&flag,4);
															  }
															  if(0==strlen(salt))
															  {
																	  printf("null没有此用户\n");
																	  send_n(sfd,"erroerro",8);
																	  break;
															  }


															  select_crypt(content,cryp);
															  printf("搜索到的salt为%s 转交给客户端验证\n",salt);
															  send_n(sfd,salt,8);
															  recv_n(sfd,crypc,14);
															  printf("从客户端收到的crypt为%s\n",crypc);
															  if(0==strcmp(cryp,crypc))
															  {
																	  flag=0;
																	  send_n(sfd,(char *)&flag,4);
																	  printf("密码正确\n");
																	  strcpy(u.usr,account);
																	  u.workpath=0;
																	  printf("开始维护一个用户%s,当前目录为%d",account,u.workpath);
																	  init_usr(&u,account);
																	  printf("初始化结果：workplace:%d  usr:%s route:%s num_file%d",u.workpath,u.usr,u.route,u.num_file);
																	  if(u.num_file==0)
																	  {
																			  u.num_file++;
																			  insert_dir(u.usr,u.workpath,u.num_file,u.usr);
																	  }	
															  }
															  else{
																	  flag=-1;
																	  send_n(sfd,(char *)&flag,4);
																	  printf("密码错误\n");
															  }



													  };break;
											   case 9:
													  {
															  printf("收到mkdir命令\n");
															  memset(content,0,sizeof(content));
															  recv_n(sfd,content,len);
															  u.num_file++;	
															  insert_dir(u.usr,u.workpath,u.num_file,content);
													  };break;
									   }
						}



				}
		}
		void send_msg(int sfd,char *tmpbuf)
		{
				train t;
				memset(&t,0,sizeof(t));
				t.ctl=1;
				//memset(buf,0,sizeof(buf));
				//处理tmpbuf 将数据填入到buf中//
				strcpy(t.buf,tmpbuf);
				t.len=strlen(t.buf);
				printf("打包完成:t.len=%d t.ctl=%d t.buf=%s\n",t.len,t.ctl,t.buf);	
				send_n(sfd,&t,8+t.len);
		}
		int send_file(int new_fd,char *name,user u)
		{
				//char md5[33];
				char md5_dpoint[33];
				int ret;
				off_t done;
				recv_n(new_fd,(char *)&done,8);//接受客户端已下载大小
				printf("已经下载：%ld\n",done);	
				//获取md5码
				memset(md5_dpoint,0,33);
				select_md5(u.workpath,name,md5_dpoint,u.usr);
				off_t ex;
				struct stat s;//发送文件大小给客户端
				ret=stat(md5_dpoint,&s);
				if(-1==ret) ex=0;
				else ex=s.st_size;
				printf("文件大小:%ld\n",ex);
		//	    int fd;
				printf("打开md5:%s",md5_dpoint);
		//		fd=open(md5,O_RDONLY);
		//		if(-1==fd)
		//		{
		//				perror("open");
		//				return -1;
		//		}

				train t;
				memset(&t,0,sizeof(t));
				strcpy(t.buf,name);
				t.len=strlen(t.buf);
				t.ctl=2;
				printf("打包完成:t.len=%d t.ctl=%d t.buf=%s\n",t.len,t.ctl,t.buf);
				ret=send_n(new_fd,&t,8+t.len);
				if(-1==ret)
				{
						perror("send");
						return -1;
				}

				send_n(new_fd,(char *)&ex,8);
				send_n(new_fd,md5_dpoint,32);
				
//				lseek(fd,done,SEEK_SET);
//						if(ex>102400)                               
//						{
//							int ret=mmap_send(new_fd,md5,done);
//							if(-1==ret)
//							{
//									printf("错误\n");
//									t.len=0;
//									t.ctl=-1;
//									send_n(new_fd,&t,8+t.len);	
//									send_msg(new_fd,"下载失败\n");
//							}
//				
//						}
//					else {	
//				while(memset(&t,0,sizeof(t)),(t.len=read(fd,t.buf,sizeof(t.buf)))>0)
//				{
//						t.ctl=2;
//						send_n(new_fd,&t,8+t.len);
//				}
//				}
//				t.len=0;
//				t.ctl=-1;
//				send_n(new_fd,&t,8+t.len);	
		}
		void ordergenerate(char *a,char *b,char *order)
		{
				memset(order,0,sizeof(order));
				strcpy(order,a);
				strcat(order," ");
				strcat(order,b);		
		}
