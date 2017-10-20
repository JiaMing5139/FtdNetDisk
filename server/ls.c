#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
void changeMod(int x,char mod[])
{
memset(mod,'-',10);
if(x&0x8000) mod[0]='-';
if(x&0x4000) mod[0]='d';
if(x&0x0100) mod[1]='r';
if(x&0x0080) mod[2]='w';
if(x&0x0040) mod[3]='x';
if(x&0x0020) mod[4]='r';
if(x&0x0010) mod[5]='w';
if(x&0x0008) mod[6]='x';
if(x&0x0004) mod[7]='r';
if(x&0x0002) mod[8]='w';
if(x&0x0001) mod[9]='x';
mod[10]='\0';
//printf("%s ",mod);

}

void changeTime(char obstr[],char time[])
{
//printf("%s\n",time);
memset(obstr,0,15);
int h,m,s,year;
sscanf(time,"%d:%d:%d %d",&h,&m,&s,&year);
sprintf(obstr,"%d:%d",h,m);
}


int ls(char *lsdir)
{
long int off[30];
DIR *dir;
dir=opendir(".");
if(NULL==dir)
{
  perror("open fail");
  return -1;
}
int ret;
struct stat buf;
struct dirent *p;
char path[512];
char tmp[100];
while((p=readdir(dir))!=NULL)
{

if(p->d_name[0]!='.')
{
memset(&buf,0,sizeof(buf));
memset(path,0,sizeof(path));
sprintf(path,"%s%s%s",".","/",p->d_name);
//printf("path:%s\n",path);
//printf("name:%s\n",p->d_name);

ret=stat(path,&buf);
if(ret!=0)
{
perror("stat");

}

//printf("mod:%x\n",buf.st_mode);
//printf("%s ",changeMod(buf.st_mode));

char mod[11];
char obstr[50];
changeMod(buf.st_mode,mod);
changeTime(obstr,ctime(&buf.st_mtime)+12);
//printf("%s %ld %s %s %ld %s %s\n",mod,buf.st_nlink,getpwuid(buf.st_uid)->pw_name,getgrgid(buf.st_gid)->gr_name,buf.st_size,obstr,p->d_name);
sprintf(tmp,"%s %ld %s %s %15.5ld %-s %-s\n",mod,buf.st_nlink,getpwuid(buf.st_uid)->pw_name,getgrgid(buf.st_gid)->gr_name,buf.st_size,obstr,p->d_name);
strcat(lsdir,tmp);

}
}
printf("%s\n",lsdir);

return 0;
}




