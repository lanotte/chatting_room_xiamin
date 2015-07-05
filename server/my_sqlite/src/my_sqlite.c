#include "../../include/myhead.h"

/*注册时的信息保存在数据库：直接比较表格中的id,name,passwd*/
int my_sqlite(struct online *p)
{
    int rc;
    int ID;

    char passwd[20];
    char *errmsg;
    char name[20];
    char sql[1024];

    
    ID = p->ID;                //提取结构体中的ID,name,passwd
    strcpy(name,p->name);
    strcpy(passwd,p->passwd);

    rc = sqlite3_open("msg.db",&db);   //打开数据库，返回0才是成功

    if(rc)
    {
        printf("sqlite open fail!\n");
	exit(1);
    }

    sprintf(sql,"insert into user_msg(ID,name,passwd) values(%d,'%s','%s')",ID,name,passwd);
                                                            //规定形式，存放在缓存区

    sqlite3_exec(db,"create table user_msg(ID integer primary key,name text,passwd text)",NULL,NULL,&errmsg);                                               //创建一个表，准备存放数据

    sqlite3_exec(db,sql,NULL,NULL,&errmsg);                 //把缓存区sql里面的信息存放在表格中

    sqlite3_close(db);

    return 0;
}
