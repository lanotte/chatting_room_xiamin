#include "../../include/myhead.h"

/*读从服务器来的消息*/
void read_message(void *arg)
{
    int fd = *((int *)arg);
    int count;          //读服务器的返回值，不等于0则接受成功
      
    while(1)
    {
	 if((count = read(fd,&msg,sizeof(msg))) != 0)
         {
	     
	    // printf("ccccccccccccc%d\n",msg.action);            // 测试信息！！！！
             
	     /*该用户已经登录*/ 
	     if(msg.action == have_log)
	     {
	         printf("this ID has been loged!\n");
		 
		 flag = 0;
	     }
	     
	     /*普通用户登录成功*/
	     if(msg.action == log_ok)
	     {
	         sleep(2);
		 
		 printf("log success!\n");
		 strcpy(seder_name,msg.name);
		 
		 flag = 2;
	     }
             
	     /*超级用户登录成功*/
	     if(msg.action == admin_log_ok)
	     {
	         sleep(2);
		 
		 printf("admin log success!\n");
		 strcpy(seder_name,msg.name);
		 
		 flag = 10;
	     }

             /*登录密码错误*/
	     if(msg.action == passwd_error)
	     {
	         printf("passwd error!\n");
		 
		 flag = 0;
	     }

             /*登录ID错误*/
	     if(msg.action == ID_error)
	     {
	         printf("this ID has not been reged!\n");
		 
		 flag = 0;
	     }
             
	     /*用户未登录*/
	     if(msg.action == -1)
	     {
	         if(my_strcmp(msg.toname,seder_name) == 0)
		 {
		     printf("you can not kick yourself!\n");
		 }
		 else
		 {
	              printf("%s has not loged!\n",msg.toname);    
	         }
	     }
             
	     /*私聊成功*/
             if(msg.action == say)
	     {
	         printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
	         printf("%s silently say to you:%s\n",msg.name,msg.msg);
	     }

             /*接受离线消息成功*/
             if(msg.action == unonline_msg)
	     {
	         printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
	         printf("%s silently say to you:%s\n",msg.toname,msg.msg);
	     }
	     
	     /*群聊成功*/
	     if(msg.action == say_all)
	     {
	         if(my_strcmp(msg.name,seder_name) != 0)         //保证群聊时不发送给自己
		 
		 {
	             printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
		     printf("%s say to all:%s\n",msg.name,msg.msg);
		 }
	     }

	     /*发送表情成功*/
	     if(msg.action == send_face)
	     {
	         printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
	         printf("%s send a expression to you:%s\n",msg.name,msg.msg);
	     }

	     /*显示在线用户信息成功*/
	     if(msg.action == show)
	     {
	         
	         printf("ID:%ld  name:%s\n",msg.ID,msg.name);
		 
	     }

             /*修改信息成功*/
	     if(msg.action == change_ok)
	     {
	         printf("change success!please check!\n");
		 printf("\n");
		 printf("please quit now and log again!\n");
	     }

             /*修改信息失败*/
	     if(msg.action == change_error)
	     {
	         printf("sorry,did not find your message!\n");
	     }

	     if(msg.action == see_record)
	     {
	         if(msg.action1 == say)
		 {
		     if(strcmp(msg.name,seder_name) == 0)
		     {
	                 printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
			 //printf(".......\n");
	                 printf("you sliently say to %s:%s\n",msg.toname,msg.msg);
			 //printf(".......\n");
		     }
		     else if(strcmp(msg.toname,seder_name) == 0)
		     {

	                 printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
	                 printf("%s sliently say to you:%s\n",msg.name,msg.msg);
		     }
		 }
		 else if(msg.action1 == say_all)
		 {
		     if(strcmp(msg.name,seder_name) == 0)
		     {
	                 printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
		         printf("you say to all:%s\n",msg.msg); 
		     }
		     
		     else if(strcmp(msg.toname,seder_name) == 0)
		     {
	                 printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
		         printf("%s say to all:%s\n",msg.name,msg.msg); 
		     }
		 }
	     }

             /*退出*/
	     if(msg.action == quit_ok)
	     {
		 printf("quit...\n");
		 sleep(3);
	         
		 printf("quit success!\n");
		 sleep(1);
		 
		 user_out();
		 
		 exit(0);
	     }

             /*踢除成功*/
	     if(msg.action == kick_ok)
	     {
	         if(my_strcmp(msg.toname,seder_name) == 0)
		 {
	             printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
		     printf("you have been kicked by admin!\n");
		     sleep(2);
		     exit(0);
		 }

		 if(my_strcmp(msg.name,seder_name) == 0)  //开始要把name传过去，不然打印不来
		 {
	             printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
		     printf("%s have been kicked by you!\n",msg.toname);
		 }
	     }
             
	     /*禁言成功*/         
	     if(msg.action == ban)    //当被禁言的人私聊或者群聊的时候，显示这个
	     {
	         printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
	         printf("you have been banned by admin!\n");
	     }

             /*通知所有的人某某被禁言了*/
	     if(msg.action == ban_tell_all)
	     {
	         if(my_strcmp(msg.toname,seder_name) == 0)  //发给被禁言的人
		 {
	             printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
		     printf("you have been banned by admin!\n");
		 }
		 else 
		 {
		     
		     if(my_strcmp(msg.name,seder_name) == 0) //发给管理员
		     {
	                 printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
		         printf("%s have been banned by you!\n",msg.toname);
	             }
		     
		     else                                     //发给其他人
		     {
	                 printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
		         printf("%s have been banned by admin!\n",msg.toname);
		     }
		 }
	     }
 
             /*解禁成功*/
	     if(msg.action == solve_ban)
	     {
	         if(strcmp(msg.toname,seder_name) == 0)
		 {
	             printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
		     printf("you have been relieve by admin!\n");
		 }
		 else
		 {
		     if(strcmp(msg.name,seder_name) == 0)
		     {
	                  printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
		          printf("%s have been relieve by you!\n",msg.toname);
		     }
		     else
		     {
	                 printf("%d/%d/%d %d:%d:%d\n",msg.year,msg.mon,msg.day,msg.hor,msg.min,msg.sec);
		         printf("%s have been relieve by admin!\n",msg.toname);
		     }
		 }
	     }

	     if(msg.action == solve_error)
	     {
                 
	         printf("%s have not been banned by you!\n",msg.toname);
		 
	     }
             /*
	     if(msg.action == quit_error)
	     {
	         printf("sorry,you can not quit,please try again!");
	     }
	     */

             /*注册成功*/
	     if(msg.action == reg_ok)
	     {
	         printf("reg success!\n");
		 printf("ID:  %ld\n",msg.ID);
		 printf("please remember your ID!\n");
		 sleep(5);
	     }
         }

	 else      //读不到服务器传来的信息，即服务器退出了！
	 {
	     printf("server have quited uncommonly!\n");
	     exit(1);
	 }
    }

}
