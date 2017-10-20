#include "func.h"
int select_salt(char *account,char *salt)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="netdisk";
	char query[200];
	sprintf(query,"%s%s%s","select salt from user where account='",account,"'");
	printf("query=%s\n",query);
	
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Query made...\n");
		res=mysql_use_result(conn);
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL)
			{	
				//printf("num=%d\n",mysql_num_fields(res));//鍒楁暟
				for(t=0;t<mysql_num_fields(res);t++)
					{
					printf("%d:%8s ",t,row[t]);
					strcpy(salt,row[t]);
					}
				printf("\n");
			}
		}
		else { return -1;}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}
int select_crypt(char *account,char *crypt)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="netdisk";
	char query[200];
	sprintf(query,"%s%s%s","select crypt from user where account='",account,"'");
	printf("query=%s\n",query);
	
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		printf("Query made...\n");
		res=mysql_use_result(conn);
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL)
			{	
				//printf("num=%d\n",mysql_num_fields(res));//鍒楁暟
				for(t=0;t<mysql_num_fields(res);t++)
					{
					printf("%d:%8s ",t,row[t]);
					strcpy(crypt,row[t]);
					}
				printf("\n");
			}
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}

int select_cd(char *pname,int workplace,char *pcurrent) //48row
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="netdisk";
	char query[200];
	sprintf(query,"%s%s%s%d","select pcurrent from filesystem where pname='",pname,"' and ppre=",workplace);
	printf("query=%s\n",query);
	
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Query made...\n");
		res=mysql_use_result(conn);
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL)
			{	
				//printf("num=%d\n",mysql_num_fields(res));//鍒楁暟
				for(t=0;t<mysql_num_fields(res);t++)
					{
					printf("%d:%8s ",t,row[t]);
					strcpy(pcurrent,row[t]);
					}
				printf("\n");
			}
		}
		else { return -1;}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}
int select_num(char *account)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="netdisk";
	char query[200];
	sprintf(query,"%s%s%s","select pcurrent from filesystem where account='",account,"'");
	printf("\nquery=%s\n",query);
	
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	//printf("t=%d",t);
	int sum=0;
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Query made...\n");
		res=mysql_use_result(conn);
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL)
			{	
			printf("%d:%8s ",t,row[t]);
			sum++;
			}
		}
		else { return -1;}
		mysql_free_result(res);
	}
	printf("sum=%d\n",sum);
	mysql_close(conn);
	return sum;
}
int select_ppre(char *account,int workplace,char *ppre) //48row
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="netdisk";
	char query[200];
	sprintf(query,"%s%s%s%d","select ppre from filesystem where  account='",account,"' and  pcurrent=",workplace);
	printf("query=%s\n",query);
	
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Query made...\n");
		res=mysql_use_result(conn);
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL)
			{	
				//printf("num=%d\n",mysql_num_fields(res));//鍒楁暟
				for(t=0;t<mysql_num_fields(res);t++)
					{
					printf("%d:%8s ",t,row[t]);
					strcpy(ppre,row[t]);
					}
				printf("\n");
			}
		}
		else { return -1;}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}
int select_ls(int workplace,char *lslist,char *account) //48row
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="netdisk";
	char query[200];
	sprintf(query,"%s%s%s%d","select pname,type,time from filesystem where account='",account,"'and  ppre=",workplace);
	printf("query=%s\n",query);
	int j;
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Query made...\n");
		res=mysql_use_result(conn);
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL)
			{	
				//printf("num=%d\n",mysql_num_fields(res));//鍒楁暟
				for(t=0;t<mysql_num_fields(res);t++)
					{
					printf("%d:%8s ",t,row[t]);
					strcat(lslist,row[t]);
					for(j=0;j<20-strlen(row[t]);j++)
					strcat(lslist," ");
					}
				printf("\n");
				strcat(lslist,"\n");
			}
		}
		else { return -1;}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}
int iffileexist(char *md5)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="netdisk";
	char query[200];
	sprintf(query,"%s%s%s","select pcurrent from filesystem where md5='",md5,"'");
	printf("query=%s\n",query);
	
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	//printf("t=%d",t);
	int sum=0;
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Query made...\n");
		res=mysql_use_result(conn);
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL)
			{	
				//printf("num=%d\n",mysql_num_fields(res));//鍒楁暟
			sum++;
			}
		}
		else { return -1;}
		mysql_free_result(res);
	}
	printf("sum=%d\n",sum);
	mysql_close(conn);
	if(0==sum)	return -1;
	else return 1;
}
int abletocd(int ppre,char *pname,char *account)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="netdisk";
	char query[200];
	sprintf(query,"%s%s%s%s%s%d","select  * from filesystem where account='",account,"' and  pname='",pname,"' and type='d' and ppre=",ppre);
	printf("query=%s\n",query);
	
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	//printf("t=%d",t);
	int sum=0;
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Query made...\n");
		res=mysql_use_result(conn);
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL)
			{	
				//printf("num=%d\n",mysql_num_fields(res));//鍒楁暟
			sum++;
			}
		}
		else { return -1;}
		mysql_free_result(res);
	}
	printf("sum=%d\n",sum);
	mysql_close(conn);
	if(0==sum)	return 0;
	else return 1;
}
int select_md5(int pcurrent,char *name,char *md5,char *account) //48row
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="netdisk";
	char query[200];
	sprintf(query,"%s%d%s%s%s%s%s","select md5 from filesystem where ppre=",pcurrent," and pname='",name,"' and account='",account,"'");
	printf("query=%s\n",query);
	
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Query made...\n");
		res=mysql_use_result(conn);
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL)
			{	
				//printf("num=%d\n",mysql_num_fields(res));//鍒楁暟
				for(t=0;t<mysql_num_fields(res);t++)
					{
					printf("%d:%8s ",t,row[t]);
					strcpy(md5,row[t]);
					}
				printf("\n");
			}
		}
		else { return -1;}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}
int select_rm(char *pname,int workplace) //48row
{
	MYSQL *conn;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="netdisk";
	char query[200];
	sprintf(query,"%s%s%s%d","delete from filesystem where pname='",pname,"' and ppre=",workplace);
	printf("query=%s\n",query);
	
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Query made...\n");
		}
	mysql_close(conn);
	return 0;
}
int ifaccountexist(char *account)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="123";
	char* database="netdisk";
	char query[200];
	sprintf(query,"%s%s%s","select account from filesystem where account='",account,"'");
	printf("query=%s\n",query);
	
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	//printf("t=%d",t);
	int sum=0;
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
		return -1;
	}else{
		printf("Query made...\n");
		res=mysql_use_result(conn);
		if(res)
		{
			while((row=mysql_fetch_row(res))!=NULL)
			{	
				//printf("num=%d\n",mysql_num_fields(res));//鍒楁暟
			sum++;
			}
		}
		else { return -1;}
		mysql_free_result(res);
	}
	printf("sum=%d\n",sum);
	mysql_close(conn);
	if(0==sum)	return -1;
	else return 1;
}
//int main()
//{
//char lslist[1000];
//memset(lslist,0,sizeof(lslist));
//select_ls(0,lslist);
//printf("%s",lslist);
////char salt[9]={0};
////char crypt[14]={0};
////select_salt("pjm",salt);
////select_crypt("pjm",crypt);
////printf("crypt:%s\n",crypt);
////printf("return salt:%s\n",salt);
//return 0;
//}
