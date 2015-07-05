#include "../../include/myhead.h"

/*登录的客户的信息插入链表*/
int insert_online(struct online *p)
{
     p->next = head;
     head = p;

     return insert_ok;
} 
