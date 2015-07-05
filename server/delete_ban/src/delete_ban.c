#include "../../include/myhead.h"

/*删除结点，把禁言链表中的人踢出来，恢复权限*/
int delete_ban(struct online *p)
{
    //struct online *ptr = head;
    
    if(p->fd == ban_user->fd)
    {
        ban_user = ban_user->next;     //ban_user是禁言链表的头
	return 0;
	//return delete_ok;
    }

    struct online *ptr = ban_user;
    struct online *temp = ptr->next;

    while(temp != NULL)
    {
        if(temp->fd == p->fd)
	{
	    ptr->next = temp->next;
	    free(temp);
	    temp = NULL;
	    return 0;
	    //return delete_ok;
	}

	ptr = temp;
	temp = temp->next;
    }

    //return delete_error;

}
