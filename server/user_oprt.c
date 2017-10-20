#include"func.h"

void init_usr(user *u,char *account)
{
u->workpath=0;
strcpy(u->usr,account);
memset(u->route,0,sizeof(u->route));
u->num_file=select_num(account);
}
void backdir(char *dir,char *pdir)
{
		memset(pdir,0,100);
		char cpy[50]={0};
		strcpy(cpy,dir);
		char *delim="/";
		char *p;
		int i=0;
		int len;
		char tmp[10]={0};
		strcpy(tmp,strtok(dir,delim));
		printf("第一个:%s",tmp);
		i=strlen(tmp);
		while((p=strtok(NULL, delim)))
		{
		i=strlen(p);
		}
		printf("删除末尾%d\n",i+1);
		len=strlen(cpy)-i-1;
		
		memcpy(pdir,cpy,len);
}
