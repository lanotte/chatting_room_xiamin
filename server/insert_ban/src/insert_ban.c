#include "../../include/myhead.h"

/*禁言的名单插入链表*/
int insert_ban(struct online *p)
{
     p->next = ban_user;
     ban_user = p;

     return insert_ok;
} 
