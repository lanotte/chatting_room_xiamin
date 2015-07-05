#include "../../include/myhead.h"

/*删除结点，当退出时，链表中显示用户在线的这个人就没了*/
int delete_online(struct online *p)
{
    //struct online *ptr = head;
    if(head == NULL)
    {
        return 0;
    }
    
    if(p->fd == head->fd)
    {
        head = head->next;
	return 0;
	//return delete_ok;
    }

    struct online *ptr = head;
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
