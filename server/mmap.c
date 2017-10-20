#include"func.h"
int mmap_send(int new_fd,char *md5,off_t start,off_t lengths)
{
		train t;
		int ret;
		struct stat buf;
		char cmd[100];
		memset(cmd,0,100);
		sprintf(cmd,"%s",md5);
		printf("即将下载filepool里的文件 :%s",cmd);
		ret=stat(cmd,&buf);
		int fd=open(cmd,O_RDWR);
		if(fd==-1)
		{
				printf("文件打开失败\n");
				return -1;
		}
		char *p;
		off_t n,m,seek;
		int k;
		n=lengths/1000;
		m=lengths%1000;
		printf("n=%ld m=%ld\n",n,m);
		//		off_t length=buf.st_size-done;
		//		if(length==0)
		//		{
		//		printf("本地客户端以后该文件\n");
		//		return 0;
		//		}
		p=(char *)mmap(NULL,lengths,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
		if(p==(char *)-1)
		{
				perror("mmap");
				printf("映射失败%p\n",p);
				return -1;
		}	
		printf("映射成功%p\n",p);
		seek=start;
		for(k=0;k<n;k++)
		{
				memset(&t,0,sizeof(t));
				t.ctl=2;
				//printf("填装\n");
				memcpy(t.buf,p+seek,1000);
				t.len=1000;
				printf("seek=%ld 打包完成:t.len=%d t.ctl=%d\n",seek,t.len,t.ctl);
				seek=seek+1000;
				send_n(new_fd,&t,8+t.len);
		}
		memset(&t,0,sizeof(t));
		t.ctl=2;
		memcpy(t.buf,p+seek,m);
		t.len=m;
		printf("new_fd %d seek=%ld 打包完成:t.len=%d t.ctl=%d t.buf=%s\n",new_fd,seek,t.len,t.ctl,t.buf);
		send_n(new_fd,&t,8+t.len);
		t.len=0;
		t.ctl=-1;
		send_n(new_fd,&t,8+t.len);	
		munmap(p,start+lengths);
		return 0;
}
//int main()
//{
//char md5[33]={"a191314314108a9268bdfe79a152aac9"};
//off_t done=136;
//mmap_send(md5,done);
//
//
//return 0;
//}
