#include "../../include/myhead.h"

/*客户端的模板*/
int main(int argc, char *argv[]) 
{   
	struct sockaddr_in server_addr; 
	struct hostent *host; 
        
	int nbytes; 

	if(argc!=2) 
	{ 
		fprintf(stderr,"Usage:%s hostname \a\n",argv[0]); 
		exit(1); 
	} 

	if((host=gethostbyname(argv[1]))==NULL) 
	{ 
	
		fprintf(stderr,"Gethostname error\n"); 
		exit(1); 
	} 

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:Internet;SOCK_STREAM:TCP
	{ 
		fprintf(stderr,"Socket Error:%s\a\n",strerror(errno)); 
		exit(1); 
	} 

	bzero(&server_addr,sizeof(server_addr)); 
	server_addr.sin_family=AF_INET;          // IPV4
	server_addr.sin_port=htons(portnumber);  
	//server_addr.sin_addr=*((struct in_addr *)host->h_addr); // 
	server_addr.sin_addr.s_addr=inet_addr(argv[1]); 
	
	if(connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{ 
		fprintf(stderr,"Connect Error:%s\a\n",strerror(errno)); 
		exit(1); 
	} 

        pthread_t id;
	pthread_create(&id,NULL,(void *)read_message,(void *)&sockfd);   //创建读的线程，read_message才有效                    注意：要在Makefile里面连接库Libs

        int cmd;
	char input[100];

	//system("reset");
	//menu();

        while(1)
	{
	   system("reset");
	   menu();

	   printf("please choose the function:");
	   cmd = function();
	   switch(cmd)
	   {
	       case reg: 
	               {
	                   user_reg();
		           break;
	               }
	       case log: 
	               {
	                   user_log();
			   //chat_room();   放在这里的话，登录失败后也会进入第二个界面
			   break;
		       }
	       case out: 
	               {
		           user_out();
			   break;
		       }
	       default:
	              {
		          system("reset");
			  menu();
			  
			  printf("there is not this function!\n");//此处不加break，直接循环，重新输入命令
		      }
	   }
        }
	
	close(sockfd);
	exit(0);
} 
