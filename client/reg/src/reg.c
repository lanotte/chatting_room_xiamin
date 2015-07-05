#include "../../include/myhead.h"

/*注册*/
void user_reg()
{
    msg.action = reg;    //通过标志位action，把指令传达给通知服务器

    char *comf_passwd;//确认密码
    char *tmp;

    printf("please input your chatting_name:");
    scanf("%s",msg.name);

    while(1)
    {
        memset(msg.passwd,0,strlen(msg.passwd));                //每次输入密码时，将变量中内容清空
        //printf("please input your password(within 20):");     //不把这个放在下面，会输出两次
	tmp = getpass("please input your passwd(within 20):");  //获得隐藏密码，必须指针来接
	my_strcpy(msg.passwd,tmp);
	
	if(strlen(msg.passwd) > 20)
	{
	    printf("your passwd is too long , please input again!\n");
	    continue;
	}
	
	else
	{
	    
	    memset(comf_passwd,0,strlen(comf_passwd));
	    //printf("please comfirm your password:");
	    //scanf("%s",comf_passwd);
	    comf_passwd = getpass("please comfirm your password:");
	}
	
	if(my_strcmp(msg.passwd,comf_passwd) == 0)//用变量来确认两次输入的密码是否一致
	{
            //write(sockfd,&msg,sizeof(msg));                 注意：生成新ID应该在服务器里面
	    //printf("reg success!\n");                             所以，这段代码应该放在服务器中
	    //msg.ID = 0;                
	    //srand(time(0));       
	    //msg.ID = rand();         
	    //printf("your ID is:%ld\n",msg.ID);
	    //printf("please remember your ID!\n");
	    break;                               //密码一致的话就跳出循环，通过write通知服务器
	}

	else
	{
	    printf("the first passwd is unequal to the second,please comfirm!\n");
	}
    }
    
    write(sockfd,&msg,sizeof(msg)); //写给服务器
    sleep(3);
}
