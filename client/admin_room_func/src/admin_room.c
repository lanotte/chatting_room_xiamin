#include "../../include/myhead.h"

/*管理员的功能*/
void admin_room()
{
    char cmd[20];
    char input_msg[100];
    //char name[20];

    system("reset");
    admin_screen();   //管理员的特权界面
    
    struct message p;

    while(flag == 2 || flag == 10)
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
	    
	    my_time(&p);
	    
	    write(sockfd,&p,sizeof(p));
	}
	
	else if(strcmp("say_all",cmd) == 0)
	{
	    printf("message:\n");
	    getchar();
	    gets(input_msg);
            
	    strcpy(p.msg,input_msg);
	    
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
                
	}
	
	else if(strcmp("send_face",cmd) == 0)
	{
	    printf("toname:");
	    scanf("%s",p.toname);

	    int temp = my_face(); //表情界面
	    
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
	    admin_screen();
	}
	
	else if(strcmp("change",cmd) == 0)
	{
	    my_change();
	    
	    msg.action = change;

	    write(sockfd,&msg,sizeof(msg));
	}
        
        else if(strcmp("ban",cmd) == 0)
	{
	    printf("please input the banned name:");
	    scanf("%s",p.toname);
            
	    p.action = ban;
	    
	    my_time(&p);
	    
	    write(sockfd,&p,sizeof(p));
	}

	else if(strcmp("solve_ban",cmd) == 0)
	{
	    printf("please input the solve_baned name:");
	    scanf("%s",p.toname);

	    p.action = solve_ban;
	    
	    my_time(&p);
	    
	    write(sockfd,&p,sizeof(p));
	}

	else if(strcmp("kick",cmd) == 0)
	{
	    printf("please input the kicked name:");
	    scanf("%s",p.toname);

            //printf("ggggggggggg%s\n",p.toname);

	    p.action = kick;       //错误：p和msg的问题
	    
	    my_time(&p);
	    
	    my_strcpy(p.name,seder_name);
	    
	    write(sockfd,&p,sizeof(p));
	}

	else if(strcmp("see_record",cmd) == 0)
	{
	     msg.action = see_record;

	     my_strcpy(msg.name,seder_name);

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
	    
	    printf("No Func! Please input correctly!\n");
	}
    }
}


