#include "func.h"

void send_msg(int new_fd,char *ctl)
{
	train t;
	int ret;
	memset(&t,0,sizeof(t));
	strcpy(t.buf,ctl);
	t.len=strlen(t.buf);
	t.clt=1;	
	ret=send(new_fd,&t,sizeof(t),0);
	if(-1==ret)
	{
		perror("send");
		return;
	}
}
