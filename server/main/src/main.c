#include "../../include/myhead.h"

struct online *head = NULL;

struct online *ban_user = NULL;

extern void read_message(void *arg);

int main(int argc, char *argv[]) 
{    
	int sockfd,new_fd; 
	struct sockaddr_in server_addr; 
	struct sockaddr_in client_addr; 
	int sin_size; 
	char msg[1024]; 
	

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) // AF_INET:IPV4;SOCK_STREAM:TCP
	{ 
		fprintf(stderr,"Socket error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 
        
	bzero(&server_addr,sizeof(struct sockaddr_in)); // ≥ı ºªØ,÷√0
	server_addr.sin_family=AF_INET;                 // Internet
	server_addr.sin_addr.s_addr=inet_addr("192.168.1.1");
	server_addr.sin_port=htons(portnumber); 
	
	if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1) 
	{ 
		fprintf(stderr,"Bind error:%s\n\a",strerror(errno)); 
		exit(1); 
	} 


	if(listen(sockfd,5)==-1) 
	{ 
		fprintf(stderr,"Listen error:%s\n\a",strerror(errno)); 
		exit(1); 
	}


	int count;
	pthread_t id;

	while(1) 
	{ 
		sin_size=sizeof(struct sockaddr_in); 
		if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1) 
		{ 
			fprintf(stderr,"Accept error:%s\n\a",strerror(errno)); 
			exit(1); 
		} 
		printf("accpet!\n");
		fprintf(stderr,"Server get connection from %s\n",inet_ntoa(client_addr.sin_addr));
		
                pthread_create(&id,NULL,(void *)read_message,(void*)&new_fd);
		
	} 

	close(sockfd); 
	return 0; 
} 
