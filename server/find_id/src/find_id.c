#include "../../include/myhead.h"
/*寻找对应的id，找到返回0，找不到返回－1*/
int find_id(int id)
{
    if(head == NULL)
    {
        return -1;
    }

    struct online *temp = head;

    while(temp != NULL)
    {
        if(temp->ID == id)
	{
	    return 0;
	}
	
	temp = temp->next;
    }
    
    return -1;
}

