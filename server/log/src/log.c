#include "../../include/myhead.h"

/*登录时传来的信息与数据库中的信息进行比较，即读数据库*/
int server_log(struct online *s)
{
    int i;
    int rc;
    int temp;
    int nrow;
    int ncloumn;
    
    char **result;

    rc = sqlite3_open("msg.db",&db); //打开数据库
    
    if(rc)
    {
        printf("sqlite open error!");
	exit(1);
    }

    sqlite3_get_table(db,"select * from user_msg",&result,&nrow,&ncloumn,&errmsg);
                                                        //显示表格中的所有信息
    temp = s->ID;
   
    //printf("aaaaaaaaaaaa%ld\n",temp);

    for(i = 1; i <= nrow; i++)
    {
        //printf("dddddddddddddd%s\n",result[i * ncloumn + 0]);

        /*i:代表第几行，0和2代表第几个*/
        if(temp == atoi(result[i * ncloumn + 0]))       //比较传来的信息与数据库的信息（id
	{
	    if(my_strcmp(s->passwd,result[i * ncloumn + 2]) == 0)//比较密码
	    { 
	        if(temp == 10000)
		{
		   my_strcpy(s->name,result[i * ncloumn + 1]);
		   return admin_log_ok;
		}
		my_strcpy(s->name,result[i * ncloumn + 1]);     //把名字返回给客户端，客户登录时只输入了id和密码，不知道名字

		//printf("lllllll%skkkkkkk%s\n",s->name,result[i * ncloumn + 1]);

	        return log_ok;
	    }

	    return passwd_error;
	}

    }
    
    return ID_error;
}
