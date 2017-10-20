#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
int insert(int id,char *log)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="netdisk";
	char query[200];
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Connected...\n");
	}
	log[strlen(log)]='\0';
		memset(query,0,sizeof(query));
		sprintf(query,"%s%d%s%s%s","insert into log(id,log) values(",id,",'",log,"')");
		puts(query);
		t=mysql_query(conn,query);
		if(t)
		{
			printf("Error making query:%s\n",mysql_error(conn));
			return -1;
		}else{
			printf("insert success\n");
		}
	mysql_close(conn);
	return 0;
}

int insert_usr(char *account,char *salt,char *cryp)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="netdisk";
	char query[200];
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Connected...\n");
	}
	account[strlen(account)]='\0';
	salt[strlen(salt)]='\0';
	cryp[strlen(cryp)]='\0';
		memset(query,0,sizeof(query));
		sprintf(query,"%s%s%s%s%s%s%s","insert into user(account,salt,crypt) values('",account,"','",salt,"','",cryp,"')");
		puts(query);
		t=mysql_query(conn,query);
		if(t)
		{
			printf("Error making query:%s\n",mysql_error(conn));
			return -1;
		}else{
			printf("insert success\n");
		}
	mysql_close(conn);
	return 0;
}
int insert_dir(char *account,int ppre,int pcurrent,char *name)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="netdisk";
	char query[200];
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Connected...\n");
	}
		memset(query,0,sizeof(query));
		sprintf(query,"%s%s%s%d%s%d%s%s%s","insert into filesystem(account,ppre,pcurrent,pname,type) values('",account,"',",ppre,",",pcurrent,",'",name,"','d')");
		puts(query);
		t=mysql_query(conn,query);
		if(t)
		{
			printf("Error making query:%s\n",mysql_error(conn));
			return -1;
		}else{
			printf("insert success\n");
		}
	mysql_close(conn);
	return 0;
}
int insert_file(char *account,int ppre,int pcurrent,char *name,char *md5)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="netdisk";
	char query[200];
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Connected...\n");
	}
		memset(query,0,sizeof(query));
		sprintf(query,"%s%s%s%d%s%d%s%s%s%s%s","insert into filesystem(account,ppre,pcurrent,pname,type,md5) values('",account,"',",ppre,",",pcurrent,",'",name,"','f','",md5,"')");
		printf("query:%s\n",query);
		puts(query);
		t=mysql_query(conn,query);
		if(t)
		{
			printf("Error making query:%s\n",mysql_error(conn));
			return -1;
		}else{
			printf("insert success\n");
		}
	mysql_close(conn);
	return 0;
}
