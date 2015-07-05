#include "../../include/myhead.h"

int find_ban(int fd)
{
    struct online *temp = ban_user;

    while(temp != NULL)
    {
        if(fd == temp->fd)
	{
	    return ban;
	}
	temp = temp->next;
    }

    return -1;
}
