#include"func.h"

void generatestr(char *salt)
{
		char c[62];
		memset(c,0,sizeof(c));
		int i;
		int j=0;
		for(i=48;i<=57;i++)
				c[j++]=i;
		for(i=65;i<=90;i++)
				c[j++]=i;
		for(i=97;i<=122;i++)	
				c[j++]=i;
		printf("%s\n",c);
		for(j=0;j<8;j++)
		{	
				salt[j]=c[rand()%63];
				//	printf("satl[%d]=%c",j,salt[j]);
		}
		salt[8]=0;
		//printf("%s",salt);
}

int registerusr(int sfd)
{
		char content[20];
		memset(content,0,20);
		char account[20]={0};
		char password[20]={0};
		char salt[12]={0};
    	printf("\n\t\t\t\t\t\t\t              请输入账号:");  
		scanf("%s",account);
		printf("\n\t\t\t\t\t\t\t              请输入密码:");
		scanf("%s",password);
		printf("接受到的账号和密为:%s %s\n",account,password);
		generatestr(salt);
		printf("cryp:%s\n",crypt(password,salt));
		send_usrinfo(sfd,account,salt,crypt(password,salt));
		recv_msg(sfd);
		return 0;
}

int login(int sfd)
{
		int flag=-1;
		char account[20]={0};
		char password[20]={0};
		char salt[9]={0};
		system("clear");
    	printf("\n\t\t\t\t\t\t\t              请输入账号:");  
		scanf("%s",account);
		printf("\n\t\t\t\t\t\t\t              请输入密码:");
		scanf("%s",password);
		printf("接受到的账号和秘密为:%s %s\n",account,password);
		train t;
		memset(&t,0,sizeof(t));
		t.ctl=8;
		sprintf(t.buf,"%s",account);
		t.len=strlen(t.buf);
		printf("用户信息打包完成:t.len=%d t.ctl=%d t.buf=%s\n",t.len,t.ctl,t.buf);
		send_n(sfd,(char *)&t,8+t.len);
		printf("等待服务器的salt\n");
		recv_n(sfd,salt,8);
		printf("从服务器收到的salt:%s\n",salt);
		if(0==strcmp("erroerro",salt))
		{
		return -1;
		}
		send_n(sfd,crypt(password,salt),14);
		recv_n(sfd,(char *)&flag,4);
		return flag;
		
}



void login_view(int sfd)
{
		int i;
		int ret=0;
		int flag=1;
		system("clear");
    printf("\n\n\n\n\n\n");  
    printf("\t\t\t\t\033[47;34m\t\t\t\t                                                    \033[0m\n");  
    printf("\t\033[47;34m\t\t\t\t\t\t\t                    Netdisk                         \033[0m\n");    
    printf("\t\t\t\t\033[47;34m\t\t\t\t                                           __V1.0.0 \033[0m\n");  
    printf("\n");   
    printf("\t\t\t\t\033[47;34m\t\t\t\t                                                    \033[0m\n");   
    printf("\t\033[47;34m\t\t\t\t\t\t\t           Welcome to Baidu Netdisk                 \033[0m\n");  
    printf("\t\t\t\t\033[47;34m\t\t\t\t                                                    \033[0m\n");  
    printf("\t\033[47;34m\t\t\t\t\t\t\t                     1:注册                         \033[5m\n");    
    printf("\t\t\t\t\033[47;34m\t\t\t\t                                                    \033[0m\n");  
    printf("\t\033[47;34m\t\t\t\t\t\t\t                     2.登陆                         \033[5m\n");    
    printf("\t\t\t\t\033[47;34m\t\t\t\t                                                    \033[0m\n");   
    printf("\t\033[47;34m\t\t\t\t\t\t\t                     3.退出                         \033[5m\n");   
    printf("\t\t\t\t\033[47;34m\t\t\t\t                                                    \033[0m\n");  
		while(flag)
		{
				printf("-------------------------------清选择一个数字--------------------------------------------\n");
				scanf("%d",&i);
				printf("%d",i);
				switch(i)
				{
						case 1:{
									   registerusr(sfd);
							   };break;
						case 2:
							   {
									   printf("登陆\n");
									   ret=login(sfd);
									   if(0==ret)
									   {
												system("clear");
											   printf("验证成功 进入网盘\n");
											   flag=0;
									   }
										else (printf("账号或密码错误\n"));
							   };break;
						default :
								{printf("输入格式错误\n");
								//while(getch());
								fflush(stdin);
								fflush(stdout);
								};break;
				}
		}
}
