#include "../../include/myhead.h"

/*利用数据库存放离线消息*/
int reserve_unlog_msg(struct message *p)
{
    int rc;
   
    char sql[1024];

    rc = sqlite3_open("msg.db",&db);   

    if(rc)
    {
        printf("sqlite open fail!\n");
	exit(1);
    }

    sprintf(sql,"insert into unlog_msg(toname,name,msg,year,mon,day,hor,min,sec) values('%s','%s','%s',%d,%d,%d,%d,%d,%d)",p->toname,p->name,p->msg,p->year,p->mon,p->day,p->hor,p->min,p->sec);
                                                            //规定形式，存放在缓存区

    sqlite3_exec(db,"create table unlog_msg(toname text,name text,msg text,year integer,mon integer,day integer,hor integer,min integer,sec integer)",NULL,NULL,&errmsg);                                               //创建一个表，准备存放数据

    sqlite3_exec(db,sql,NULL,NULL,&errmsg);                 //把缓存区sql里面的信息存放在表格中

    sqlite3_close(db);

    return 0;
}
