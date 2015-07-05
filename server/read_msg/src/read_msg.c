#include "../../include/myhead.h"

void read_message(void *arg)
{
    int fd = *((int *)arg);
    int to_fd;
    int count;
    int result;  
    int temp;

    struct message msg;
    struct online *p;
    struct online *q;
    struct online *m;

    while(1)
    {
         if((count = read(fd,&msg,sizeof(msg))) != 0)  //读取客户端传来的信息
	 {
             //printf("aaaaaaaaaaaaa%d\n",msg.action);
	     if(msg.action == log)
	     {
	         p = (struct online*)malloc(sizeof(struct online));
		 p->fd = fd;
		 p->ID = msg.ID;
		 strcpy(p->passwd,msg.passwd);
		
		 if(find_id(msg.ID) == 0)       //找到已经登录的ID号，返回have_log，防止重复登录
		 {
		     msg.action = have_log;

		     write(fd,&msg,sizeof(msg));
		 }
                 else
		 {
	             result = server_log(p);  //去数据库中核实登录信息和注册信息是否一致
                 
                 //printf("bbbbbbbbbbbbb%d\n",result);

                     strcpy(msg.name,p->name);

		     if(result == log_ok)
		     {
		         msg.action = log_ok;

		         insert_online(p);    //登录成功后，插入链表，用来显示在线的用户

		         write(fd,&msg,sizeof(msg));

		         sleep(8);

		         read_unlog_msg(msg.name,fd);    //读保存在服务器里的离线消息
		     }

		     if(result == admin_log_ok)
		     {
		         msg.action = admin_log_ok;

		         insert_online(p);
		         write(fd,&msg,sizeof(msg));

		         sleep(8);
		     
		         read_unlog_msg(msg.name,fd);
		     }

		 
		 
		     if(result == passwd_error)
		     {
		         msg.action = passwd_error;
       		         write(fd,&msg,sizeof(msg));
		     }
		     
		     if(result == ID_error)
		     {
		         msg.action = ID_error;
	                 write(fd,&msg,sizeof(msg));
		     }
		 
                 }
             }

	     if(msg.action == reg)
	     {
	         p = (struct online*)malloc(sizeof(struct online)); //给结构体p分配空间

                 p->fd = fd;                                        //为写入数据库作准备
		 strcpy(p->name,msg.name);
		 strcpy(p->passwd,msg.passwd);

		 //result = insert_online(p);

		 //if(result == insert_ok)
                 srand(time(0));  //防止随机数重复
		 temp = rand();   //生成随机数
		 p->ID = temp;
		 msg.ID = p->ID;         //返回给客户端的ID和reg_ok
		 msg.action = reg_ok;    //通知客户端“注册成功”的标志
            
		 my_sqlite(p);         //注册时的信息写入数据库
		 write(fd,&msg,sizeof(msg));//把生成的id号传给客户端
	     }

	     if(msg.action == say)
	     {
                 if(find_ban(fd) == ban)
		 {
		     msg.action = ban;
		     write(fd,&msg,sizeof(msg));

		     msg.action = -2;                  //防止和谁聊天，谁被禁言
		 }
	        
		 else
		 {
	             to_fd = find_fd(msg.toname);//聊天通过寻找对方的fd，找不到返回－1，找到返回对方的fd
		 
		     if(to_fd == -1)
		     {
		         msg.action = to_fd;

                         reserve_unlog_msg(&msg);

			 reserve_chat_msg(&msg);

		         write(fd,&msg,sizeof(msg));//没找到客户2，就返回客户1的fd
		     }
		     else
		     {
		         
			 reserve_chat_msg(&msg);
			 
			 write(to_fd,&msg,sizeof(msg));//找到了客户2，就返回客户2的fd
		     }
		 }
	     }
	     
	     if(msg.action == say_all)
	     {
                 if(find_ban(fd) == ban)
		 {
		     msg.action = ban;
		     write(fd,&msg,sizeof(msg));

		     msg.action = -2;
		 }
	         else
		 {
	             struct online *temp = head;     //遍历链表，传送每一个fd
		 
	             reserve_chat_msg(&msg);
		     
		     while(temp != NULL)
		     {    
			 write(temp->fd,&msg,sizeof(msg));
		         temp = temp->next;
		     }
		 }
	     }

	     if(msg.action == send_face)
	     {
                 if(find_ban(fd) == ban)
		 {
		     msg.action = ban;
		     write(fd,&msg,sizeof(msg));

		     msg.action = -2;                  //防止和谁聊天，谁被禁言
		 }
		 else
		 {
                     to_fd = find_fd(msg.toname);
		 
		     if(to_fd == -1)
		     {
		         msg.action = to_fd;        

		         write(fd,&msg,sizeof(msg));
		     }
		     else
		     {   
			 write(to_fd,&msg,sizeof(msg));
		     }
		 }
	     }

	     if(msg.action == change)
	     {   
	         struct online *temp = head;           //通过查找ID，替换昵称和密码
	         
		 q = (struct online*)malloc(sizeof(struct online));
		 
		 while(temp->fd == fd)
		 {   
		     q->ID = msg.ID;
		     strcpy(q->passwd,msg.passwd);
		     strcpy(q->name,msg.name);

		     //printf("aaaaaaaaaa%ldaaaaaaa%saaaaaaa%s\n",q->ID,q->passwd,q->name);
		 
	             result = server_change(q);
                      
                     //printf("cccccccccccccccckui zi shi sha bi!\n");

		     if(result == change_ok)
		     {
		         msg.action = change_ok;
                         write(fd,&msg,sizeof(msg));
			 break;
		     }

		     else
		     {
		         msg.action = change_error;
		         write(fd,&msg,sizeof(msg));
			 break;
		     }

		     temp = temp->next;
		 }
	     }

	     if(msg.action == show)
	     {      
	         struct online *temp = head;     //遍历链表，传送每一个fd
		 while(temp != NULL)
		 {
		     msg.ID = temp->ID;             //错误：这两句话要加，不然信息是同一个人的
		     my_strcpy(msg.name,temp->name);
		     write(fd,&msg,sizeof(msg)); //错误：这里是fd，是在发过来的客户的界面显示
		     temp = temp->next;
		 }
	     }

	     if(msg.action == quit)
	     {
		 //printf("aaaaaaaaaaaaa%ld\n",msg.ID);
	         m = (struct online*)malloc(sizeof(struct online));
		 m->fd = fd;
		 //m->ID = msg.ID;
		 //my_strcpy(m->passwd,msg.passwd);
		 //my_strcpy(m->name,msg.name);
		 
		 //printf("aaaaaaaaaaaaa%ld\n",msg.ID);

	         delete_online(m);      //链表中不显示该用户
		 
		 msg.action = quit_ok;
		 
		 write(fd,&msg,sizeof(msg));

                 /*
		 if(result == delete_error)
		 {
		     msg.action = quit_error;
		     write(fd,&msg,sizeof(msg));
		 }
		 */
	     }

	     if(msg.action == kick)
	     {	
		 to_fd = find_fd(msg.toname);
	         //fd = find_fd(msg.name);
                 if(to_fd == -1 || my_strcmp(msg.name,msg.toname) == 0)
		 {
		     msg.action = -1;

		     write(fd,&msg,sizeof(msg));
		 }
		 
		 else
		 {
		     m = (struct online*)malloc(sizeof(struct online));
		 
		     m->fd = to_fd;
	         
		     delete_online(m);      //链表中不显示该用户
		 
		     msg.action = kick_ok;
		  
		     write(fd,&msg,sizeof(msg));
		 
		     write(to_fd,&msg,sizeof(msg));
		 }
	     }

             if(msg.action == ban)
	     {
	         //printf("nnnnnnn%s\n",msg.toname);

	         to_fd = find_fd(msg.toname);

		 struct online *temp;
		 struct online *str = head;

		 temp = (struct online*)malloc(sizeof(struct online));

		 while(str != NULL)
		 {
                     msg.action = ban_tell_all;  //不能写在后面，找到了就要发过去

                     write(str->fd,&msg,sizeof(msg));

		     if(str->fd == to_fd)
		     {
		         temp->fd = to_fd;
			 temp->ID = str->ID;
			 my_strcpy(temp->name,str->name);

			 //insert_online(temp);   错误：不能插入head中，那是显示在线链表的
			 insert_ban(temp);   //建立一个禁言链表
		     }
		     
		     str = str->next;        
		 }
	     }

	     if(msg.action == solve_ban)
	     {
	        
		 to_fd = find_fd(msg.toname);

	     
		 if((find_ban(to_fd)) == -1)
		 {
	        //printf("aaaaaaaaaaaaaaaaaa\n"); 
		     msg.action = solve_error;

		     write(fd,&msg,sizeof(msg));
	        //printf("aaaaaaaaaaaaaaaaaa\n"); 
		 }
	         
		 else
		 {
		     m = (struct online*)malloc(sizeof(struct online));
		 
		     m->fd = to_fd;
	         
		     delete_ban(m);  //删除禁言链表中该用户名字

		     msg.action = solve_ban;

		     struct online *temp = head;

		     while(temp != NULL)          //通知所有人，该用户被解禁了
                     {
		         write(temp->fd,&msg,sizeof(msg));
		         temp = temp->next;
		     }
		 }
	     }

	     if(msg.action == see_record)
	     {

	         //printf("cccccccccccccccccccccccccc\n");
		 read_chat_msg(msg.name,fd);

		 write(fd,&msg,sizeof(msg));
	     }
	 }

	 else              //客户端ctrl+c之后，将在线的用户删除掉，show的时候少掉这个异常退出的用户
	 {
             struct online *m = (struct online*)malloc(sizeof(struct online));
		 
	     m->fd = fd;
	         
	     delete_online(m);   
	 }
    }
}
