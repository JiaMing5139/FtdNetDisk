#include"func.h"
int md5get(char *fname,char *md5) 
{ 
char cmd[20];
sprintf(cmd,"md5sum %s > md5r",fname);
printf("cmd=%s\n",cmd);
system(cmd);
int fd=0;
fd=open("md5r",O_RDONLY);
printf("fd:%d\n",fd);
if(fd<0)
return -1;
memset(md5,0,33);
read(fd,md5,32);
printf("md5:%s\n",md5);
return 0;
}
