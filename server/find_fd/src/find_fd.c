#include "../../include/myhead.h"

int find_fd(char *toname)
{
    if(head == NULL)
    {
        return -1;
    }

    struct online *temp = head;

    while(temp != NULL)
    {
        if(strcmp(temp->name,toname) == 0)
	{
	    return temp->fd;
	}
	
	temp = temp->next;
    }
    
    return -1;
}

