#include "../../include/myhead.h"

/*读离线消息*/
int read_unlog_msg(char *my_name,int fd)  //传参：发送的对象和fd(为了在这里写给客户端)
{
    int i;
    int rc;
    int temp;
    int nrow;
    int ncloumn;

    struct message s;

    char sql[1024];
    char **result;

    rc = sqlite3_open("msg.db",&db); //打开数据库
    
    if(rc)
    {
        printf("sqlite open error!");
	exit(1);
    }

    sqlite3_get_table(db,"select * from unlog_msg",&result,&nrow,&ncloumn,&errmsg);
                                                        //显示表格中的所有信息

	        //printf("lllllllllllllllll%s\n",my_name);
    for(i = 1; i <= nrow; i++)
    {
        if(my_strcmp(my_name,result[i * ncloumn + 0]) == 0)       
	{
	        //printf("lllllllllllllllll%s\n",my_name);
		my_strcpy(s.toname,result[i * ncloumn + 1]);  
		my_strcpy(s.msg,result[i * ncloumn + 2]);
                s.year = atoi(result[i * ncloumn + 3]);  //要把字符串转化成整型
                s.mon = atoi(result[i * ncloumn + 4]);
                s.day = atoi(result[i * ncloumn + 5]);
                s.hor = atoi(result[i * ncloumn + 6]);
                s.min = atoi(result[i * ncloumn + 7]);
                s.sec = atoi(result[i * ncloumn + 8]);

                s.action = unonline_msg;

		write(fd,&s,sizeof(s));		        //直到读完所有写给自己的所有信息后跳出
        }
    }
    
    sprintf(sql,"delete from unlog_msg where toname = '%s'",my_name);//读完后全部删除，为了新的信息
   
    sqlite3_exec(db,sql,NULL,NULL,&errmsg);  
    
    return -2;
}
