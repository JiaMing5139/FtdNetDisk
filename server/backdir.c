#include"func.h"
void backdir(char *dir,char *pdir)
{
		memset(pdir,0,100);
		char cpy[50]={0};
		strcpy(cpy,dir);
		char *delim="/";
		char *p;
		int i=0;
		strtok(dir,delim);
		while((p=strtok(NULL, delim)))
		{
		i=strlen(p);
		}
		int len;
		len=strlen(cpy)-i;
		memcpy(pdir,cpy,len);
}
int main()
{
char route[100]={"/home/"};
char ndir[100];
backdir(route,ndir);
printf("ndir=%s\n",ndir);
}
