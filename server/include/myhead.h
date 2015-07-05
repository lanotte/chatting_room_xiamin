#ifndef _MYHEAD_H_
#define _MYHEAD_H_

#include <stdlib.h> 
#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <netdb.h>
#include<arpa/inet.h>
#include<ctype.h>
#include<sqlite3.h>
#include<netdb.h>
#include<time.h>


#define portnumber 3333

struct message      //客户端和服务器要保持一致
{
    int action;
    int action1;
    long int ID;

    char name[20];
    char toname[20];
    char msg[100];
    char passwd[20];

    int sec;
    int min;
    int hor;
    int day;
    int mon;
    int year;

    struct message *next;
};

struct online
{
    int fd;
    int ID;
    char name[20];
    char passwd[20];

    struct online *next;
};

extern struct online *head;       //显示在线用户链表的头

extern struct online *ban_user;   //禁言链表的头

sqlite3 *db;

char *errmsg;

enum             //客户端和服务器要保持一致
{
    reg,
    log,
    out,
    log_ok,
    admin_log_ok,
    log_error,
    have_log,
    reg_ok,
    passwd_error,
    ID_error,
    change_ok,
    change_error,
    say,
    say_all,
    show,
    send_face,
    change,
    see_record,
    quit,
    quit_ok,
    ban,
    ban_tell_all,
    solve_ban,
    solve_error,
    kick,
    kick_ok,
    unonline_msg,
    insert_ok,
    delete_ok
};

#endif
