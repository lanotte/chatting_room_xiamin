#include "../../include/myhead.h"

/*利用数据库存放消息记录*/
int reserve_chat_msg(struct message *p)
{
    int rc;
   
    char sql[1024];

    rc = sqlite3_open("msg.db",&db);   

    if(rc)
    {
        printf("sqlite open fail!\n");
	exit(1);
    }

    printf("aaaaaaaaaaaaaaaaaaaaa%saaaaaaaaaaa%s",p->toname,p->msg);
    sprintf(sql,"insert into chat_msg(toname,name,msg,action,year,mon,day,hor,min,sec) values('%s','%s','%s',%d,%d,%d,%d,%d,%d,%d)",p->toname,p->name,p->msg,p->action,p->year,p->mon,p->day,p->hor,p->min,p->sec);
                                                            //规定形式，存放在缓存区

    sqlite3_exec(db,"create table chat_msg(toname text,name text,msg text,action integer,year integer,mon integer,day integer,hor integer,min integer,sec integer)",NULL,NULL,&errmsg);                                               //创建一个表，准备存放数据

    sqlite3_exec(db,sql,NULL,NULL,&errmsg);                 //把缓存区sql里面的信息存放在表格中

    sqlite3_close(db);

    return 0;
}
