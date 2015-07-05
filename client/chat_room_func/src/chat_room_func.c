#include "../../include/myhead.h"

void chat_room()
{
    char cmd[20];
    char input_msg[100];

    system("reset");
    screen();
    
    struct message p;

    while(flag == 2)
    {
	scanf("%s",cmd);

	if(strcmp("say",cmd) == 0)
	{
	    printf("toname:");
	    scanf("%s",p.toname);
	    printf("message:\n");
	  
	    getchar();              //解决缓冲问题
	    gets(input_msg);
	    
	    strcpy(p.msg,input_msg);
	    strcpy(p.name,seder_name);
	    
	    memset(input_msg,0,sizeof(input_msg));
	    
	    p.action = say;
	    
	    my_time(&p);                //调用时间函数，全部存放在msg中，然后发送给服务器
	    
	    write(sockfd,&p,sizeof(p));
	}
	
	else if(strcmp("say_all",cmd) == 0)
	{
	    printf("message:\n");
	    getchar();
	    gets(input_msg);

	    my_strcpy(p.name,seder_name);
	    my_strcpy(p.msg,input_msg);
	    
	    memset(input_msg,0,sizeof(input_msg));
	    
	    p.action = say_all;
	    
	    my_time(&p);
	    
	    write(sockfd,&p,sizeof(p));
	}
	
	else if(0 == strcmp("show",cmd))
	{
	    msg.action = show;
	    
	    write(sockfd,&msg,sizeof(msg));
	}
	
	else if(0 == strcmp("send_file",cmd))
	{
             /*还未实现*/   
	}
	
	else if(strcmp("send_face",cmd) == 0)
	{
	    printf("toname:");
	    scanf("%s",p.toname);

	    int temp = my_face();
	 
	    if(temp == -1)
	    {
	        break;
	    }

	    my_strcpy(p.msg,my_expression);
	    
	    memset(my_expression,0,sizeof(my_expression));
	    
	    strcpy(p.name,seder_name);
            
	    p.action = send_face;

	    my_time(&p);
	    
	    write(sockfd,&p,sizeof(p));

	    system("reset");
	    screen();
	}
	
	else if(strcmp("change",cmd) == 0)
	{
	    my_change();
	    
	    msg.action = change;

            //printf("bbbbbbbbbb%ldbbbbbbbb%sbbbbb%s\n",msg.ID,msg.name,msg.passwd);

	    write(sockfd,&msg,sizeof(msg));
	}

	else if(strcmp("see_record",cmd) == 0)
	{
	    msg.action = see_record;

            //printf("bbbbbbbbbbbbbbbbbbbb\n");

            strcpy(msg.name,seder_name);

	    write(sockfd,&msg,sizeof(msg));
	}

	else if(strcmp("quit",cmd) == 0)
	{
	    msg.action = quit;
	    
	    write(sockfd,&msg,sizeof(msg));
	}

	else
	{
	    system("reset");
	    screen();
	    
	    printf("No Work! Please input correctly!\n");
	}
    }
}


