#include "../../include/myhead.h"

/*登录*/
void user_log()
{
    char *tmp;

    msg.action = log;
    
    flag = 1;            //标志位，1：登录    2：执行登录后的命令

    while(flag == 1)
    {
        char count;      //读的返回值

	char str[20];
  
	//struct message temp;

	printf("please input your ID:");
	scanf("%s",str);

        msg.ID = atoi(str);   //将字符串型转换成整型，因为ID的范围超出int型了

	//printf("please input your passwd:");
	//scanf("%s",msg.passwd);
	tmp = getpass("please input your passwd:");
	strcpy(msg.passwd,tmp);

	write(sockfd,&msg,sizeof(msg));//传送给服务器，让服务器判断ID和密码是否正确

	printf("log...\n");

	sleep(3);

	while(flag == 2)      //普通用户，标志位2，进去普通界面
	{
	    chat_room();
	}

	while(flag == 10)     //超级用户，标志位10，进入超级界面
	{
	    admin_room();
	}
    }
}
	 
	       
